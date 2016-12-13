#include "UInputDevice.h"

UInputDevice::UInputDevice()
{
}

UInputDevice::~UInputDevice()
{
    releaseHandle();
}

int32_t UInputDevice::getHandle()
{
    int32_t handle = open("/dev/uinput", O_WRONLY | O_NDELAY);
    if (handle == 0)
    {
        printf("Unable to open /dev/uinput\n");
        throw -1;
    }
    return handle;
}

void UInputDevice::releaseHandle()
{
    ioctl(m_fileDescriptor, UI_DEV_DESTROY);
    close(m_fileDescriptor);
}

void UInputDevice::setKeyState(uint16_t keycode, int16_t keyvalue, uint16_t evtype)
{
    struct input_event event;
    gettimeofday(&event.time, NULL);

    event.type = evtype;
    event.code = keycode;
    event.value = keyvalue;

    if (write(m_fileDescriptor, &event, sizeof(event)) < 0)
    {
        printf("[UInputGamepad] Simulate key error\n");
        throw -1;
    }
}

void UInputDevice::sync()
{
    struct input_event event;
    gettimeofday(&event.time, NULL);

    event.type = EV_SYN;
    event.code = SYN_REPORT;
    event.value = 0;

    if (write(m_fileDescriptor, &event, sizeof(event)) < 0)
    {
        printf("[UInputGamepad] Simulate key error\n");
        throw -1;
    }
}
