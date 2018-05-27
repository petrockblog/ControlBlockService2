/**
 * (c) Copyright 2017  Florian Müller (contact@petrockblock.com)
 * https://github.com/petrockblog/ControlBlock2
 *
 * Permission to use, copy, modify and distribute the program in both binary and
 * source form, for non-commercial purposes, is hereby granted without fee,
 * providing that this license information and copyright notice appear with
 * all copies and any derived work.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event shall the authors be held liable for any damages
 * arising from the use of this software.
 *
 * This program is freeware for PERSONAL USE only. Commercial users must
 * seek permission of the copyright holders first. Commercial use includes
 * charging money for the program or software derived from the program.
 *
 * The copyright holders request that bug fixes and improvements to the code
 * should be forwarded to them so everyone can benefit from the modifications
 * in future versions.
 */

#include "UInputGamepadNES.h"

UInputGamepadNES::UInputGamepadNES()
{
    m_fileDescriptor = getHandle();

    struct uinput_user_dev uinp;
    memset(&uinp, 0, sizeof(uinp));
    strncpy(uinp.name, "ControlBlock NES Gamepad", strlen("ControlBlock NES Gamepad"));
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
        printf("[UInputGamepadNES] Unable to create UINPUT device.");
        // throw -1;
    }

    setKeyState(ABS_X, 2, EV_ABS);
    setKeyState(ABS_Y, 2, EV_ABS);
    sync();
}

UInputGamepadNES::~UInputGamepadNES()
{
}
