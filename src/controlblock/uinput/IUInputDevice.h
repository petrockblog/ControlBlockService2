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

#ifndef CONTROLBLOCKSERVICE2_IUINPUTDEVICE_H
#define CONTROLBLOCKSERVICE2_IUINPUTDEVICE_H

#include "UInputEventCodes.h"

class IUInputDevice {
public:
    enum DeviceType
    {
      TYPE_GAMEPAD_ARCADE = 0,
      TYPE_GAMEPAD_SNES,
      TYPE_GAMEPAD_NES,
      TYPE_GAMEPAD_GENESIS,
      TYPE_KEYBOARD
    };

    /**
     * Constructor
     */
    IUInputDevice() = default;

    /**
     * Destructor
     */
    virtual ~IUInputDevice() =  default;

    /**
     * Sets the state of a key. To let the changes have an effect the method \ref sync() needs to be called.
     * @param keycode - The keycode
     * @param keyvalue
     * @param evtype
     */
    virtual void setKeyState(uint16_t keycode, int16_t keyvalue, uint16_t evtype) = 0;

    /**
     * Sends all recent key state changes via \ref setKeyState() to the uinput device.
     */
    virtual void sync() = 0;
};

#endif //CONTROLBLOCKSERVICE2_IUINPUTDEVICE_H
