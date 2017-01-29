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

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "hal/DigitalOutMock.h"
#include "hal/DigitalInMock.h"
#include "uinput/UInputFactoryMock.h"
#include "app/ControlBlock.h"
#include "config/ControlBlockConfigurationMock.h"
#include "gamepads/GamepadFactoryMock.h"
#include "gamepads/InputDeviceMock.h"

using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::NiceMock;

TEST(ControlBlockTest, Constructor)
{
    DigitalOutMock doMock;
    DigitalInMock diMock;
    UInputFactoryMock uiFactory;
    ControlBlockConfigurationMock configMock;
    GamepadFactoryMock gpadFactoryMock;
    InputDeviceMock* inputDeviceMock= new InputDeviceMock();

    SingleConfiguration config_board0(true, 0u, "snes", true, false);
    SingleConfiguration config_board1(false, 0u, "snes", true, false);

    // configuration expectations
    EXPECT_CALL(configMock, loadConfiguration());
    EXPECT_CALL(configMock, getConfiguration(0)).WillRepeatedly(ReturnRef(config_board0));
    EXPECT_CALL(configMock, getConfiguration(1)).WillRepeatedly(ReturnRef(config_board1));

    // power switch expectations
    EXPECT_CALL(doMock, configureDevice(IDigitalOut::DO_DEVICE_POWERSWITCH));
    EXPECT_CALL(diMock, configureDevice(IDigitalIn::DI_DEVICE_POWERSWITCH));
    EXPECT_CALL(doMock, setLevel(IDigitalOut::DO_CHANNEL_TOPOWERSWITCH, IDigitalOut::DO_LEVEL_HIGH, IDigitalOut::BOARD_0));

    // gamepad expectations
    EXPECT_CALL(gpadFactoryMock, createGamepadProxy(InputDevice::GAMEPAD_SNES)).WillRepeatedly(Return(inputDeviceMock));
    EXPECT_CALL(*inputDeviceMock, initialize(InputDevice::CHANNEL_1));

    ControlBlock controlBlock{uiFactory, diMock, doMock, configMock, gpadFactoryMock};
}