#ifndef ISINGLECONFIGURATION_H
#define ISINGLECONFIGURATION_H

#include <stdint.h>

class ISingleConfiguration
{
public:
    enum GamepadType_e
    {
        GAMEPAD_ARCADE = 0,
        GAMEPAD_MAME,
        GAMEPAD_SNES,
        GAMEPAD_NONE
    };

    ISingleConfiguration() = default;
    virtual ~ISingleConfiguration() = default;

    virtual bool isEnabled() = 0;
    virtual uint8_t getDeviceAddress() = 0;
    virtual GamepadType_e getGamepadType() = 0;
    virtual bool isPowerSwitchEnabled() = 0;
    virtual bool isOnlyOneGamepadEnabled() = 0;

};

#endif
