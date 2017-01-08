#include "UInputGamepadSNES.h"
#include <assert.h>

UInputGamepadSNES::UInputGamepadSNES()
{
    m_fileDescriptor = getHandle();

    struct uinput_user_dev uinp;
    memset(&uinp, 0, sizeof(uinp));
    strncpy(uinp.name, "ControlBlock SNES Gamepad", strlen("ControlBlock SNES Gamepad"));
    uinp.id.version = 4;
    uinp.id.bustype = BUS_USB;
    uinp.id.product = 1;
    uinp.id.vendor = 1;

    // Setup the uinput device
    ioctl(m_fileDescriptor, UI_SET_EVBIT, EV_KEY);
    ioctl(m_fileDescriptor, UI_SET_EVBIT, EV_REL);

    // gamepad, buttons
    ioctl(m_fileDescriptor, UI_SET_KEYBIT, BTN_A);
    ioctl(m_fileDescriptor, UI_SET_KEYBIT, BTN_B);
    ioctl(m_fileDescriptor, UI_SET_KEYBIT, BTN_X);
    ioctl(m_fileDescriptor, UI_SET_KEYBIT, BTN_Y);
    ioctl(m_fileDescriptor, UI_SET_KEYBIT, BTN_TL);
    ioctl(m_fileDescriptor, UI_SET_KEYBIT, BTN_TR);
    ioctl(m_fileDescriptor, UI_SET_KEYBIT, BTN_START);
    ioctl(m_fileDescriptor, UI_SET_KEYBIT, BTN_SELECT);

    // Add Absolute (D-pad) type
    ioctl(m_fileDescriptor, UI_SET_EVBIT, EV_ABS);

    ioctl(m_fileDescriptor, UI_SET_ABSBIT, ABS_X);
    ioctl(m_fileDescriptor, UI_SET_ABSBIT, ABS_Y);

    // AXIS_MIN for left/up, AXIS_MAX for right/down
    ioctl(m_fileDescriptor, UI_SET_EVBIT, EV_ABS);
    ioctl(m_fileDescriptor, UI_SET_ABSBIT, ABS_X);
    ioctl(m_fileDescriptor, UI_SET_ABSBIT, ABS_Y);
    uinp.absmin[ABS_X] = 0;
    uinp.absmax[ABS_X] = 4;
    uinp.absmin[ABS_Y] = 0;
    uinp.absmax[ABS_Y] = 4;

    /* Create input device into input sub-system */
    write(m_fileDescriptor, &uinp, sizeof(uinp));
    if (ioctl(m_fileDescriptor, UI_DEV_CREATE))
    {
        printf("[SNESGamepad] Unable to create UINPUT device.");
        // throw -1;
    }

    setKeyState(ABS_X, 2, EV_ABS);
    setKeyState(ABS_Y, 2, EV_ABS);
    sync();
}

UInputGamepadSNES::~UInputGamepadSNES()
{
}
