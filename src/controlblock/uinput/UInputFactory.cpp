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

#include "UInputFactory.h"

#include "UInputGamepadArcade.h"
#include "UInputKeyboard.h"
#include "UInputGamepadSNES.h"
#include "UInputGamepadNES.h"
#include "UInputGamepadGenesis.h"
#include "UInputGamepadSaturn.h"

IUInputDevice* UInputFactory::getUInputDevice(IUInputDevice::DeviceType type)
{
    switch (type) {
    case IUInputDevice::TYPE_GAMEPAD_ARCADE:
        return new UInputGamepadArcade();
    case IUInputDevice::TYPE_GAMEPAD_SNES:
        return new UInputGamepadSNES();
    case IUInputDevice::TYPE_GAMEPAD_NES:
        return new UInputGamepadNES();
    case IUInputDevice::TYPE_GAMEPAD_GENESIS:
        return new UInputGamepadGenesis();
    case IUInputDevice::TYPE_GAMEPAD_SATURN:
        return new UInputGamepadSaturn();        
    case IUInputDevice::TYPE_KEYBOARD:
        return new UInputKeyboard();
    default:
        throw std::runtime_error("Unknown type.");
    }
}
