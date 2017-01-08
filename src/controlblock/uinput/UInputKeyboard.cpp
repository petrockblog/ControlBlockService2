#include "UInputKeyboard.h"
#include <assert.h>

UInputKeyboard::UInputKeyboard()
{
    m_fileDescriptor = getHandle();

    struct uinput_user_dev uinp;
    memset(&uinp, 0, sizeof(uinp));
    strncpy(uinp.name, "ControlBlock Keyboard Device", strlen("ControlBlock Keyboard Device"));
    uinp.id.version = 4;
    uinp.id.bustype = BUS_USB;
    uinp.id.product = 1;
    uinp.id.vendor = 1;

    // Setup the uinput keyboard device
    ioctl(m_fileDescriptor, UI_SET_EVBIT, EV_KEY);
    ioctl(m_fileDescriptor, UI_SET_EVBIT, EV_REL);
    for (uint32_t index = 0u; index < 256u; index++)
    {
        ioctl(m_fileDescriptor, UI_SET_KEYBIT, index);
    }

    /* Create input device into input sub-system */
    write(m_fileDescriptor, &uinp, sizeof(uinp));
    if (ioctl(m_fileDescriptor, UI_DEV_CREATE))
    {
        printf("[ControlBlockService] Unable to create UINPUT device.");
        throw -1;
    }
}

UInputKeyboard::~UInputKeyboard()
{
}
