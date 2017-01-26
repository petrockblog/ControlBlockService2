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
        padType = GAMEPAD_ARCADE;
    }
    else if (pType.compare("mame") == 0)
    {
        padType = GAMEPAD_MAME;
    }
    else if (pType.compare("snes") == 0)
    {
        padType = GAMEPAD_SNES;
    }
    else if (pType.compare("none") == 0)
    {
        padType = GAMEPAD_NONE;
    }
    else if (pType.compare("genesis") == 0)
    {
        padType = GAMEPAD_GENESIS;
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

ISingleConfiguration::GamepadType_e SingleConfiguration::getGamepadType()
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
