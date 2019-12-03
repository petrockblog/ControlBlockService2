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

#include "UInputGamepadArcade.h"

UInputGamepadArcade::UInputGamepadArcade()
{
    m_fileDescriptor = getHandle();

    struct uinput_user_dev uinp;
    memset(&uinp, 0, sizeof(uinp));
    strncpy(uinp.name, "ControlBlock Arcade Gamepad", strlen("ControlBlock Arcade Gamepad"));
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
    ioctl(m_fileDescriptor, UI_SET_KEYBIT, BTN_C);
    ioctl(m_fileDescriptor, UI_SET_KEYBIT, BTN_X);
    ioctl(m_fileDescriptor, UI_SET_KEYBIT, BTN_Y);
    ioctl(m_fileDescriptor, UI_SET_KEYBIT, BTN_Z);
    ioctl(m_fileDescriptor, UI_SET_KEYBIT, BTN_TL);
    ioctl(m_fileDescriptor, UI_SET_KEYBIT, BTN_TR);
    ioctl(m_fileDescriptor, UI_SET_KEYBIT, BTN_TL2);
    ioctl(m_fileDescriptor, UI_SET_KEYBIT, BTN_TR2);
    ioctl(m_fileDescriptor, UI_SET_KEYBIT, BTN_START);
    ioctl(m_fileDescriptor, UI_SET_KEYBIT, BTN_SELECT);

    // gamepad, directions
    ioctl(m_fileDescriptor, UI_SET_EVBIT, EV_ABS);
    ioctl(m_fileDescriptor, UI_SET_ABSBIT, ABS_X);
    ioctl(m_fileDescriptor, UI_SET_ABSBIT, ABS_Y);
    uinp.absmin[ABS_X] = 0;
    uinp.absmax[ABS_X] = 4;
    uinp.absmin[ABS_Y] = 0;
    uinp.absmax[ABS_Y] = 4;

    /* Create input device into input sub-system */
    write(m_fileDescriptor, &uinp, sizeof(uinp));
    if (ioctl(m_fileDescriptor, UI_DEV_CREATE)) {
        printf("[ArcadeGamepad] Unable to create UINPUT device.");
        throw std::runtime_error("Unable to create UINPUT device.");
    }

    setKeyState(ABS_X, 2, EV_ABS);
    setKeyState(ABS_Y, 2, EV_ABS);
    sync();
}

UInputGamepadArcade::~UInputGamepadArcade() = default;
