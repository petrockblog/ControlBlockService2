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
