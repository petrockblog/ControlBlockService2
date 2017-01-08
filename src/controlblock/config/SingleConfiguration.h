#ifndef SINGLECONFIGURATION_H
#define SINGLECONFIGURATION_H

#include <string>
#include "ISingleConfiguration.h"

class SingleConfiguration: public ISingleConfiguration
{
public:
    SingleConfiguration(bool enabled, uint8_t address, std::string type, bool pwrSwitch, bool oneGp);
    virtual ~SingleConfiguration();

    virtual bool isEnabled();
    virtual uint8_t getDeviceAddress();
    virtual GamepadType_e getGamepadType();
    virtual bool isPowerSwitchEnabled();
    virtual bool isOnlyOneGamepadEnabled();

private:
    bool isEnabledValue;
    uint8_t deviceAddress;
    GamepadType_e padType;
    bool isPowerSwitchEnabledValue;
    bool isOnlyOneGamepadEnabledValue;
};

#endif
