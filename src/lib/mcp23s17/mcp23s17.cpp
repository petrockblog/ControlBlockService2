#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <dirent.h>
#include "mcp23s17.h"


static const uint8_t spi_mode = 0;
static const uint8_t spi_bpw = 8; // bits per word
static const uint32_t spi_speed = 3900000; // 10MHz
static const uint16_t spi_delay = 0;

// Auto-detect SPI bus numbers at runtime (for RPi 5 compatibility)
static int spi_bus_numbers[2] = {-1, -1};
static char spidev_paths[2][2][32] = {{{0}}};

// Auto-detect available SPI devices (handles RPi 5's spi10 vs older RPi's spi0)
static void detect_spi_devices(void)
{
    static int detected = 0;
    if (detected) return;
    detected = 1;

    DIR *dir = opendir("/dev");
    if (!dir) {
        fprintf(stderr, "detect_spi_devices: Failed to open /dev directory\n");
        return;
    }

    struct dirent *entry;
    int bus_index = 0;

    while ((entry = readdir(dir)) != NULL && bus_index < 2) {
        // Look for spidevX.0 devices
        if (strncmp(entry->d_name, "spidev", 6) == 0) {
            int bus_num, chip_sel;
            if (sscanf(entry->d_name, "spidev%d.%d", &bus_num, &chip_sel) == 2) {
                if (chip_sel == 0) {
                    // Found a bus with chip select 0
                    spi_bus_numbers[bus_index] = bus_num;
                    snprintf(spidev_paths[bus_index][0], sizeof(spidev_paths[bus_index][0]),
                             "/dev/spidev%d.0", bus_num);
                    snprintf(spidev_paths[bus_index][1], sizeof(spidev_paths[bus_index][1]),
                             "/dev/spidev%d.1", bus_num);
                    fprintf(stderr, "detect_spi_devices: Found SPI bus %d at %s\n",
                            bus_index, spidev_paths[bus_index][0]);
                    bus_index++;
                }
            }
        }
    }
    closedir(dir);

    if (bus_index == 0) {
        fprintf(stderr, "detect_spi_devices: WARNING - No SPI devices found\n");
    }
}

// epoll related vars
// static int epoll_is_initialised = 0;
static int gpio_pin_fd = -1;
static int epoll_fd = -1;
static struct epoll_event epoll_ctl_events;
static struct epoll_event mcp23s17_epoll_events;


// prototypes
static uint8_t get_spi_control_byte(uint8_t rw_cmd, uint8_t hw_addr);
static int init_epoll(void);


int mcp23s17_open(int bus, int chip_select)
{
    int fd;

    // Auto-detect SPI devices on first call
    detect_spi_devices();

    // Validate bus and chip_select
    if (bus < 0 || bus >= 2 || chip_select < 0 || chip_select >= 2) {
        fprintf(stderr,
                "mcp23s17_open: ERROR Invalid bus (%d) or chip_select (%d).\n",
                bus, chip_select);
        return -1;
    }

    if (spidev_paths[bus][chip_select][0] == '\0') {
        fprintf(stderr,
                "mcp23s17_open: ERROR No SPI device found for bus %d chip_select %d.\n",
                bus, chip_select);
        return -1;
    }

    // open
    if ((fd = open(spidev_paths[bus][chip_select], O_RDWR)) < 0) {
        fprintf(stderr,
                "mcp23s17_open: ERROR Could not open SPI device (%s).\n",
                spidev_paths[bus][chip_select]);
        return -1;
    }

    // initialise
    if (ioctl(fd, SPI_IOC_WR_MODE, &spi_mode) < 0) {
        fprintf(stderr, "mcp23s17_open: ERROR Could not set SPI mode.\n");
	close(fd);
        return -1;
    }
    if (ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &spi_bpw) < 0) {
        fprintf(stderr,
                "mcp23s17_open: ERROR Could not set SPI bits per word.\n");
	close(fd);
        return -1;
    }
    if (ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &spi_speed) < 0) {
        fprintf(stderr, "mcp23s17_open: ERROR Could not set SPI speed.\n");
	close(fd);
        return -1;
    }

    return fd;
}

uint8_t mcp23s17_read_reg(uint8_t reg, uint8_t hw_addr, int fd)
{
    uint8_t control_byte = get_spi_control_byte(READ_CMD, hw_addr);
    uint8_t tx_buf[3] = {control_byte, reg, 0};
    uint8_t rx_buf[sizeof tx_buf];

    struct spi_ioc_transfer spi;
    memset (&spi, 0, sizeof(spi));
    spi.tx_buf = (unsigned long) tx_buf;
    spi.rx_buf = (unsigned long) rx_buf;
    spi.len = sizeof tx_buf;
    spi.delay_usecs = spi_delay;
    spi.speed_hz = spi_speed;
    spi.bits_per_word = spi_bpw;

    // do the SPI transaction
    if ((ioctl(fd, SPI_IOC_MESSAGE(1), &spi) < 0)) {
        fprintf(stderr,
                "mcp23s17_read_reg: There was a error during the SPI "
                "transaction.\n");
        return -1;
    }

    // return the data
    return rx_buf[2];
}

void mcp23s17_write_reg(uint8_t data, uint8_t reg, uint8_t hw_addr, int fd)
{
    uint8_t control_byte = get_spi_control_byte(WRITE_CMD, hw_addr);
    uint8_t tx_buf[3] = {control_byte, reg, data};
    uint8_t rx_buf[sizeof tx_buf];

    struct spi_ioc_transfer spi;
    memset (&spi, 0, sizeof(spi));
    spi.tx_buf = (unsigned long) tx_buf;
    spi.rx_buf = (unsigned long) rx_buf;
    spi.len = sizeof tx_buf;
    spi.delay_usecs = spi_delay;
    spi.speed_hz = spi_speed;
    spi.bits_per_word = spi_bpw;

    // do the SPI transaction
    if ((ioctl(fd, SPI_IOC_MESSAGE(1), &spi) < 0)) {
        fprintf(stderr,
                "mcp23s17_write_reg: There was a error during the SPI "
                "transaction.\n");
    }
}

uint8_t mcp23s17_read_bit(uint8_t bit_num,
                          uint8_t reg,
                          uint8_t hw_addr,
                          int fd)
{
    return (mcp23s17_read_reg(reg, hw_addr, fd) >> bit_num) & 1;
}

void mcp23s17_write_bit(uint8_t data,
                        uint8_t bit_num,
                        uint8_t reg,
                        uint8_t hw_addr,
                        int fd)
{
    uint8_t reg_data = mcp23s17_read_reg(reg, hw_addr, fd);
    if (data) {
        reg_data |= 1 << bit_num; // set
    } else {
        reg_data &= 0xff ^ (1 << bit_num); // clear
    }
    return mcp23s17_write_reg(reg_data, reg, hw_addr, fd);
}




int mcp23s17_enable_interrupts()
{
    int fd, len;
    char str_gpio[3];
    char str_filenm[33];

    if ((fd = open("/sys/class/gpio/export", O_WRONLY)) < 0)
        return -1;

    len = snprintf(str_gpio, sizeof(str_gpio), "%d", GPIO_INTERRUPT_PIN);
    write(fd, str_gpio, len);
    close(fd);

    snprintf(str_filenm, sizeof(str_filenm), "/sys/class/gpio/gpio%d/direction", GPIO_INTERRUPT_PIN);
    if ((fd = open(str_filenm, O_WRONLY)) < 0)
        return -1;

    write(fd, "in", 3);
    close(fd);

    snprintf(str_filenm, sizeof(str_filenm), "/sys/class/gpio/gpio%d/edge", GPIO_INTERRUPT_PIN);
    if ((fd = open(str_filenm, O_WRONLY)) < 0)
        return -1;

    write(fd, "falling", 8);
    close(fd);

    return 0;
}

int mcp23s17_disable_interrupts()
{
    int fd, len;
    char str_gpio[3];

    if ((fd = open("/sys/class/gpio/unexport", O_WRONLY)) < 0)
        return -1;

    len = snprintf(str_gpio, sizeof(str_gpio), "%d", GPIO_INTERRUPT_PIN);
    write(fd, str_gpio, len);
    close(fd);

    return 0;
}

int mcp23s17_wait_for_interrupt(int timeout)
{
    int num_fds = -1;

    if (epoll_fd <= 0) {
        if (init_epoll() != 0) {
            return -1;
        }
    }

    // Wait for user event
    num_fds = epoll_wait(epoll_fd, &mcp23s17_epoll_events, 1, timeout);

    return num_fds;
}

static int init_epoll(void)
{
    // calculate the GPIO pin's path
    char gpio_pin_filename[33];
    snprintf(gpio_pin_filename,
             sizeof(gpio_pin_filename),
             "/sys/class/gpio/gpio%d/value",
             GPIO_INTERRUPT_PIN);

    // if we haven't already, create the epoll and the GPIO pin fd's
    if(epoll_fd <= 0) {
        epoll_fd = epoll_create(1);
        if (epoll_fd <= 0) {
            fprintf(stderr,
                    "mcp23s17_wait_for_interrupt: There was a error during "
                    "the epoll_create.\n"
                    "Error is %s (errno=%d)\n",
                    strerror(errno),
                    errno);
            return -1;
        }
        gpio_pin_fd = open(gpio_pin_filename, O_RDONLY | O_NONBLOCK);
    }

    if(gpio_pin_fd <= 0) {
        // we haven't successfully opened the GPIO pin fd
        fprintf(stderr,
                "mcp23s17_wait_for_interrupt: Can't open fd <%s> <%d>.\n"
                "Error is %s (errno=%d)\n",
                gpio_pin_filename,
                gpio_pin_fd,
                strerror(errno),
                errno);
        return -1;
    } else {
        epoll_ctl_events.events = EPOLLIN | EPOLLET;
        epoll_ctl_events.data.fd = gpio_pin_fd;

        if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, gpio_pin_fd, &epoll_ctl_events) != 0) {
            fprintf(stderr,
                    "mcp23s17_wait_for_interrupt: There was a error "
                    "during the epoll_ctl EPOLL_CTL_ADD.\n");
            fprintf(stderr,
                    "Error is %s (errno=%d)\n",
                    strerror(errno),
                    errno);
        }
        // Ignore GPIO Initial Event
        epoll_wait(epoll_fd, &mcp23s17_epoll_events, 1, 10);
        return 0;
    }
}


/**
 * Returns an SPI control byte.
 *
 * The MCP23S17 is a slave SPI device. The slave address contains four
 * fixed bits (0b0100) and three user-defined hardware address bits
 * (if enabled via IOCON.HAEN; pins A2, A1 and A0) with the
 * read/write command bit filling out the rest of the control byte::
 *
 *     +--------------------+
 *     |0|1|0|0|A2|A1|A0|R/W|
 *     +--------------------+
 *     |fixed  |hw_addr |R/W|
 *     +--------------------+
 *     |7|6|5|4|3 |2 |1 | 0 |
 *     +--------------------+
 *
 */
static uint8_t get_spi_control_byte(uint8_t rw_cmd, uint8_t hw_addr)
{
    hw_addr = (hw_addr << 1) & 0xE;
    rw_cmd &= 1; // just 1 bit long
    return 0x40 | hw_addr | rw_cmd;
}