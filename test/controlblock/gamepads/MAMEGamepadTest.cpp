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

#include "uinput/UInputDeviceMock.h"
#include "uinput/UInputFactoryMock.h"
#include "hal/DigitalInMock.h"
#include "gamepads/MAMEGamepad.h"

using ::testing::Return;
using ::testing::NiceMock;

TEST(MAMEGamepadTest, Constructor)
{
    UInputFactoryMock uiFactory;
    DigitalInMock di;

    EXPECT_CALL(uiFactory, getUInputDeviceProxy(IUInputDevice::TYPE_KEYVBOARD));
    MAMEGamepad gamepad(uiFactory, di);
}

TEST(MAMEGamepadTest, initialize)
{
    NiceMock<UInputFactoryMock> uiFactory;
    DigitalInMock di;
    MAMEGamepad gamepad(uiFactory, di);

    EXPECT_CALL(di, configureDevice(IDigitalIn::DI_DEVICE_ALLIN));
    gamepad.initialize(InputDevice::CHANNEL_1);
}

TEST(MAMEGamepadTest, updateLeftUpAndAllButtonsPressed)
{
    NiceMock<UInputFactoryMock> uiFactory;
    DigitalInMock di;
    UInputDeviceMock* gamepadMock = new UInputDeviceMock();

    EXPECT_CALL(uiFactory, getUInputDeviceProxy(IUInputDevice::TYPE_KEYVBOARD)).WillOnce(Return(gamepadMock));
    EXPECT_CALL(di, configureDevice(IDigitalIn::DI_DEVICE_ALLIN));
    MAMEGamepad gamepad(uiFactory, di);
    gamepad.initialize(InputDevice::CHANNEL_1);

    // axes
    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_LEFT, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_HIGH));
    EXPECT_CALL(*gamepadMock, setKeyState(KEY_LEFT, 1, EV_KEY));

    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_RIGHT, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_HIGH));
    EXPECT_CALL(*gamepadMock, setKeyState(KEY_RIGHT, 1, EV_KEY));

    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_UP, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_HIGH));
    EXPECT_CALL(*gamepadMock, setKeyState(KEY_UP, 1, EV_KEY));

    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_DOWN, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_HIGH));
    EXPECT_CALL(*gamepadMock, setKeyState(KEY_DOWN, 1, EV_KEY));


    // buttons
    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_SW1, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_HIGH));
    EXPECT_CALL(*gamepadMock, setKeyState(KEY_LEFTCTRL, 1, EV_KEY));

    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_SW2, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_HIGH));
    EXPECT_CALL(*gamepadMock, setKeyState(KEY_LEFTALT, 1, EV_KEY));

    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_SW3, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_HIGH));
    EXPECT_CALL(*gamepadMock, setKeyState(KEY_SPACE, 1, EV_KEY));

    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_SW4, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_HIGH));
    EXPECT_CALL(*gamepadMock, setKeyState(KEY_LEFTSHIFT, 1, EV_KEY));

    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_SW5, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_HIGH));
    EXPECT_CALL(*gamepadMock, setKeyState(KEY_Z, 1, EV_KEY));

    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_SW6, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_HIGH));
    EXPECT_CALL(*gamepadMock, setKeyState(KEY_X, 1, EV_KEY));

    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_SW7, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_HIGH));
    EXPECT_CALL(*gamepadMock, setKeyState(KEY_C, 1, EV_KEY));

    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_SW8, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_HIGH));
    EXPECT_CALL(*gamepadMock, setKeyState(KEY_V, 1, EV_KEY));

    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_START, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_HIGH));
    EXPECT_CALL(*gamepadMock, setKeyState(KEY_1, 1, EV_KEY));

    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_COIN, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_HIGH));
    EXPECT_CALL(*gamepadMock, setKeyState(KEY_5, 1, EV_KEY));

    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_A, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_HIGH));
    EXPECT_CALL(*gamepadMock, setKeyState(KEY_P, 1, EV_KEY));

    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_B, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_HIGH));
    EXPECT_CALL(*gamepadMock, setKeyState(KEY_ENTER, 1, EV_KEY));

    EXPECT_CALL(*gamepadMock, sync());
    gamepad.update();
}
