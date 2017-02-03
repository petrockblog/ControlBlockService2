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

#include "UInputKeyboard.h"

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
