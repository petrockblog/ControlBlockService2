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

#ifndef CONTROLBLOCKSERVICE2_SINGLECONFIGURATIONMOCK_H
#define CONTROLBLOCKSERVICE2_SINGLECONFIGURATIONMOCK_H

#include "gmock/gmock.h"  // Brings in Google Mock.
#include "config/ISingleConfiguration.h"

class SingleConfigurationMock: public ISingleConfiguration
{
public:
    MOCK_METHOD0(isEnabled, bool());
    MOCK_METHOD0(getDeviceAddress, uint8_t());
    MOCK_METHOD0(getGamepadType, GamepadType_e());
    MOCK_METHOD0(isPowerSwitchEnabled, bool());
    MOCK_METHOD0(isPowerSwitchMomentary, bool());
    MOCK_METHOD0(isOnlyOneGamepadEnabled, bool());
};

#endif //CONTROLBLOCKSERVICE2_SINGLECONFIGURATIONMOCK_H
