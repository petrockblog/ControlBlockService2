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

#include "../app/Logger.h"
#include "fmt/format.h"
#include "SingleConfiguration.h"

SingleConfiguration::SingleConfiguration(bool enabled, uint8_t address, const std::string& pType, bool pwrSwitch,
        bool oneGp) :
                isEnabledValue(enabled),
                deviceAddress(address),
                isPowerSwitchEnabledValue(pwrSwitch),
                isOnlyOneGamepadEnabledValue(oneGp)
{
    if (pType == "arcade")
    {
        padType = InputDevice::GAMEPAD_ARCADE;
    }
    else if (pType == "mame")
    {
        padType = InputDevice::GAMEPAD_MAME;
    }
    else if (pType == "snes")
    {
        padType = InputDevice::GAMEPAD_SNES;
    }
    else if (pType == "nes")
    {
        padType = InputDevice::GAMEPAD_NES;
    }
    else if (pType == "none")
    {
        padType = InputDevice::GAMEPAD_NONE;
    }
    else if (pType == "genesis")
    {
        padType = InputDevice::GAMEPAD_GENESIS;
    }
    else if (pType == "saturn")
    {
        padType = InputDevice::GAMEPAD_SATURN;
    }
    const std::string configMessage = fmt::format("Created configuration. isEnabled: {}, address: {}, pad type: {}, power switch: {}, only one gamepad: {}", enabled, address, pType, pwrSwitch, oneGp);
    Logger::logMessage(configMessage);
}

SingleConfiguration::~SingleConfiguration()
= default;

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
