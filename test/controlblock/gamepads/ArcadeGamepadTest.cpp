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
#include "gamepads/ArcadeGamepad.h"

using ::testing::Return;
using ::testing::NiceMock;

TEST(ArcadeGamepadTest, Constructor)
{
    UInputFactoryMock uiFactory;
    DigitalInMock di;

    EXPECT_CALL(uiFactory, getUInputDeviceProxy(IUInputDevice::TYPE_GAMEPAD_ARCADE));
    ArcadeGamepad gamepad(uiFactory, di);
}

TEST(ArcadeGamepadTest, initialize)
{
    NiceMock<UInputFactoryMock> uiFactory;
    DigitalInMock di;
    ArcadeGamepad gamepad(uiFactory, di);

    EXPECT_CALL(di, configureDevice(IDigitalIn::DI_DEVICE_ALLIN));
    gamepad.initialize(InputDevice::CHANNEL_1);
}

TEST(ArcadeGamepadTest, updateLeftUpAndAllButtonsPressed)
{
    NiceMock<UInputFactoryMock> uiFactory;
    DigitalInMock di;
    UInputDeviceMock* gamepadMock = new UInputDeviceMock();

    EXPECT_CALL(uiFactory, getUInputDeviceProxy(IUInputDevice::TYPE_GAMEPAD_ARCADE)).WillOnce(Return(gamepadMock));
    EXPECT_CALL(di, configureDevice(IDigitalIn::DI_DEVICE_ALLIN));
    ArcadeGamepad gamepad(uiFactory, di);
    gamepad.initialize(InputDevice::CHANNEL_1);

    // axes
    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_LEFT, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_HIGH));
    EXPECT_CALL(*gamepadMock, setKeyState(ABS_Y, 0, EV_ABS));

    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_UP, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_HIGH));
    EXPECT_CALL(*gamepadMock, setKeyState(ABS_X, 4, EV_ABS));

    // buttons
    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_SW1, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_HIGH));
    EXPECT_CALL((*gamepadMock), setKeyState(BTN_A, 1, EV_KEY));

    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_SW2, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_HIGH));
    EXPECT_CALL(*gamepadMock, setKeyState(BTN_B, 1, EV_KEY));

    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_SW3, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_HIGH));
    EXPECT_CALL(*gamepadMock, setKeyState(BTN_C, 1, EV_KEY));

    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_SW4, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_HIGH));
    EXPECT_CALL(*gamepadMock, setKeyState(BTN_X, 1, EV_KEY));

    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_SW5, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_HIGH));
    EXPECT_CALL(*gamepadMock, setKeyState(BTN_Y, 1, EV_KEY));

    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_SW6, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_HIGH));
    EXPECT_CALL(*gamepadMock, setKeyState(BTN_Z, 1, EV_KEY));

    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_SW7, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_HIGH));
    EXPECT_CALL(*gamepadMock, setKeyState(BTN_TL, 1, EV_KEY));

    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_SW8, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_HIGH));
    EXPECT_CALL(*gamepadMock, setKeyState(BTN_TR, 1, EV_KEY));

    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_START, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_HIGH));
    EXPECT_CALL(*gamepadMock, setKeyState(BTN_START, 1, EV_KEY));

    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_COIN, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_HIGH));
    EXPECT_CALL(*gamepadMock, setKeyState(BTN_SELECT, 1, EV_KEY));

    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_A, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_HIGH));
    EXPECT_CALL(*gamepadMock, setKeyState(BTN_TL2, 1, EV_KEY));

    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_B, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_HIGH));
    EXPECT_CALL(*gamepadMock, setKeyState(BTN_TR2, 1, EV_KEY));

    EXPECT_CALL(*gamepadMock, sync());
    gamepad.update();
}

TEST(ArcadeGamepadTest, updateRightDownAndAllButtonsReleased)
{
    NiceMock<UInputFactoryMock> uiFactory;
    DigitalInMock di;
    UInputDeviceMock* gamepadMock = new UInputDeviceMock();

    EXPECT_CALL(uiFactory, getUInputDeviceProxy(IUInputDevice::TYPE_GAMEPAD_ARCADE)).WillOnce(Return(gamepadMock));
    EXPECT_CALL(di, configureDevice(IDigitalIn::DI_DEVICE_ALLIN));
    ArcadeGamepad gamepad(uiFactory, di);
    gamepad.initialize(InputDevice::CHANNEL_1);

    // axes
    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_LEFT, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_LOW));
    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_RIGHT, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_HIGH));
    EXPECT_CALL(*gamepadMock, setKeyState(ABS_Y, 4, EV_ABS));

    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_UP, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_LOW));
    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_DOWN, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_HIGH));
    EXPECT_CALL(*gamepadMock, setKeyState(ABS_X, 0, EV_ABS));

    // buttons
    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_SW1, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_LOW));
    EXPECT_CALL((*gamepadMock), setKeyState(BTN_A, 0, EV_KEY));

    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_SW2, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_LOW));
    EXPECT_CALL(*gamepadMock, setKeyState(BTN_B, 0, EV_KEY));

    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_SW3, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_LOW));
    EXPECT_CALL(*gamepadMock, setKeyState(BTN_C, 0, EV_KEY));

    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_SW4, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_LOW));
    EXPECT_CALL(*gamepadMock, setKeyState(BTN_X, 0, EV_KEY));

    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_SW5, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_LOW));
    EXPECT_CALL(*gamepadMock, setKeyState(BTN_Y, 0, EV_KEY));

    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_SW6, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_LOW));
    EXPECT_CALL(*gamepadMock, setKeyState(BTN_Z, 0, EV_KEY));

    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_SW7, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_LOW));
    EXPECT_CALL(*gamepadMock, setKeyState(BTN_TL, 0, EV_KEY));

    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_SW8, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_LOW));
    EXPECT_CALL(*gamepadMock, setKeyState(BTN_TR, 0, EV_KEY));

    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_START, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_LOW));
    EXPECT_CALL(*gamepadMock, setKeyState(BTN_START, 0, EV_KEY));

    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_COIN, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_LOW));
    EXPECT_CALL(*gamepadMock, setKeyState(BTN_SELECT, 0, EV_KEY));

    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_A, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_LOW));
    EXPECT_CALL(*gamepadMock, setKeyState(BTN_TL2, 0, EV_KEY));

    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_B, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_LOW));
    EXPECT_CALL(*gamepadMock, setKeyState(BTN_TR2, 0, EV_KEY));

    EXPECT_CALL(*gamepadMock, sync());
    gamepad.update();
}