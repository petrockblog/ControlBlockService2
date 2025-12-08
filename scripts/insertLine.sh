#!/bin/bash

function addSPIBcmModule() {
    echo -e "Making sure that SPI interface is enabled"

    # RPi 5 uses /boot/firmware/config.txt, older versions use /boot/config.txt
    if [ -f /boot/firmware/config.txt ]; then
        CONFIG_FILE="/boot/firmware/config.txt"
        echo "Detected Raspberry Pi 5 (using $CONFIG_FILE)"
    else
        CONFIG_FILE="/boot/config.txt"
        echo "Detected older Raspberry Pi model (using $CONFIG_FILE)"
    fi

    # Ensure dtparam=spi=on is in the config file
    if grep -qxF 'dtparam=spi=on' "$CONFIG_FILE"; then
        echo "SPI already enabled in $CONFIG_FILE"
    else
        echo "Adding dtparam=spi=on to $CONFIG_FILE"
        echo 'dtparam=spi=on' >> "$CONFIG_FILE"
    fi

    # Try to load kernel modules (older RPi models)
    # RPi 5 uses different drivers, so we suppress errors
    modprobe spi_bcm2835 2>/dev/null || true
    modprobe spidev 2>/dev/null || true
}

# enable spi kernel module
touch /etc/modprobe.d/raspi-blacklist.conf
sed -i -e "s|^blacklist spi-bcm2708|#blacklist spi-bcm2708|g" /etc/modprobe.d/raspi-blacklist.conf

# Add SPI configuration to boot config
addSPIBcmModule

# Enable SPI immediately (without reboot)
echo "Activating SPI interface..."
if dtparam spi=on 2>/dev/null; then
    echo "SPI interface activated successfully"
else
    echo "Note: dtparam command failed (may require reboot or may not be available on this system)"
fi

# Verify SPI devices are available
if [ -e /dev/spidev0.0 ]; then
    echo "SPI device /dev/spidev0.0 is available"
else
    echo "Warning: /dev/spidev0.0 not found - you may need to reboot for SPI changes to take effect"
fi

# install ControlBlockService files
install -m 0755 controlblock.service /etc/systemd/system/
systemctl enable --now controlblock.service
