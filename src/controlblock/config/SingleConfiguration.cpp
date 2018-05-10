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

#include <iostream>
#include "SingleConfiguration.h"

SingleConfiguration::SingleConfiguration(bool enabled, uint8_t address, std::string pType, bool pwrSwitch,
        bool oneGp) :
                isEnabledValue(enabled),
                deviceAddress(address),
                isPowerSwitchEnabledValue(pwrSwitch),
                isOnlyOneGamepadEnabledValue(oneGp)
{
    if (pType.compare("arcade") == 0)
    {
        padType = InputDevice::GAMEPAD_ARCADE;
    }
    else if (pType.compare("mame") == 0)
    {
        padType = InputDevice::GAMEPAD_MAME;
    }
    else if (pType.compare("snes") == 0)
    {
        padType = InputDevice::GAMEPAD_SNES;
    }
    else if (pType.compare("nes") == 0)
    {
        padType = InputDevice::GAMEPAD_NES;
    }
    else if (pType.compare("none") == 0)
    {
        padType = InputDevice::GAMEPAD_NONE;
    }
    else if (pType.compare("genesis") == 0)
    {
        padType = InputDevice::GAMEPAD_GENESIS;
    }

#ifndef NDEBUG
    std::cout << "Created configuration. isEnabled: " << enabled << ", address: " << static_cast<int>(address) << ", pad type: " << pType << ", power switch: " << pwrSwitch << ", only one gamepad: " << oneGp << std::endl;
#endif
}

SingleConfiguration::~SingleConfiguration()
{
}

bool SingleConfiguration::isEnabled()
{
    return isEnabledValue;
}

uint8_t SingleConfiguration::getDeviceAddress()
{
    return deviceAddress;
}

InputDevice::GamepadType_e SingleConfiguration::getGamepadType()
{
    return padType;
}

bool SingleConfiguration::isPowerSwitchEnabled()
{
    return isPowerSwitchEnabledValue;
}

bool SingleConfiguration::isOnlyOneGamepadEnabled()
{
    return isOnlyOneGamepadEnabledValue;
}
