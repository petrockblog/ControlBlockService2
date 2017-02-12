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
#include "hal/DigitalOutMock.h"
#include "gamepads/SNESGamepad.h"

using ::testing::Return;
using ::testing::NiceMock;

TEST(SNESGamepadTest, Constructor)
{
    UInputFactoryMock uiFactory;
    DigitalInMock diMock;
    DigitalOutMock doMock;

    EXPECT_CALL(uiFactory, getUInputDeviceProxy(IUInputDevice::TYPE_GAMEPAD_SNES));
    EXPECT_CALL(uiFactory, getUInputDeviceProxy(IUInputDevice::TYPE_KEYVBOARD));

    SNESGamepad gamepad(uiFactory, diMock, doMock);
}

TEST(SNESGamepadTest, initialize_channel1)
{
    NiceMock<UInputFactoryMock> uiFactory;
    DigitalInMock diMock;
    DigitalOutMock doMock;

    EXPECT_CALL(uiFactory, getUInputDeviceProxy(IUInputDevice::TYPE_GAMEPAD_SNES));
    EXPECT_CALL(uiFactory, getUInputDeviceProxy(IUInputDevice::TYPE_KEYVBOARD));

    SNESGamepad gamepad(uiFactory, diMock, doMock);

    EXPECT_CALL(diMock, configureDevice(IDigitalIn::DI_DEVICE_SNES));
    EXPECT_CALL(doMock, configureDevice(IDigitalOut::DO_DEVICE_SNES));

    EXPECT_CALL(doMock, setLevel(IDigitalOut::DO_CHANNEL_P1P2_STROBE, IDigitalOut::DO_LEVEL_LOW, IDigitalOut::BOARD_0));
    EXPECT_CALL(doMock, setLevel(IDigitalOut::DO_CHANNEL_P1P2_CLOCK, IDigitalOut::DO_LEVEL_LOW, IDigitalOut::BOARD_0));
    EXPECT_CALL(doMock, setLevel(IDigitalOut::DO_CHANNEL_P1_VCC, IDigitalOut::DO_LEVEL_HIGH, IDigitalOut::BOARD_0));

    gamepad.initialize(InputDevice::CHANNEL_1);
}

TEST(SNESGamepadTest, update)
{
    NiceMock<UInputFactoryMock> uiFactory;
    DigitalInMock diMock;
    DigitalOutMock doMock;
    UInputDeviceMock* gamepadMock = new UInputDeviceMock();
    UInputDeviceMock* keyboardMock = new UInputDeviceMock();

    EXPECT_CALL(uiFactory, getUInputDeviceProxy(IUInputDevice::TYPE_GAMEPAD_SNES)).WillOnce(Return(gamepadMock));
    EXPECT_CALL(uiFactory, getUInputDeviceProxy(IUInputDevice::TYPE_KEYVBOARD)).WillOnce(Return(keyboardMock));

    SNESGamepad gamepad(uiFactory, diMock, doMock);

    EXPECT_CALL(diMock, configureDevice(IDigitalIn::DI_DEVICE_SNES));
    EXPECT_CALL(doMock, configureDevice(IDigitalOut::DO_DEVICE_SNES));

    EXPECT_CALL(doMock, setLevel(IDigitalOut::DO_CHANNEL_P1P2_STROBE, IDigitalOut::DO_LEVEL_LOW, IDigitalOut::BOARD_0));
    EXPECT_CALL(doMock, setLevel(IDigitalOut::DO_CHANNEL_P1P2_CLOCK, IDigitalOut::DO_LEVEL_LOW, IDigitalOut::BOARD_0));
    EXPECT_CALL(doMock, setLevel(IDigitalOut::DO_CHANNEL_P1_VCC, IDigitalOut::DO_LEVEL_HIGH, IDigitalOut::BOARD_0));

    gamepad.initialize(InputDevice::CHANNEL_1);

    EXPECT_CALL(doMock,
            setLevel(IDigitalOut::DO_CHANNEL_P1P2_STROBE, IDigitalOut::DO_LEVEL_HIGH, IDigitalOut::BOARD_0));
    EXPECT_CALL(doMock, setLevel(IDigitalOut::DO_CHANNEL_P1P2_STROBE, IDigitalOut::DO_LEVEL_LOW, IDigitalOut::BOARD_0));

    EXPECT_CALL(diMock, getLevel(IDigitalIn::DI_CHANNEL_P1_DATA, IDigitalIn::BOARD_0)).Times(12);

    EXPECT_CALL(doMock,
            setLevel(IDigitalOut::DO_CHANNEL_P1P2_CLOCK, IDigitalOut::DO_LEVEL_HIGH, IDigitalOut::BOARD_0)).Times(12);
    EXPECT_CALL(doMock,
            setLevel(IDigitalOut::DO_CHANNEL_P1P2_CLOCK, IDigitalOut::DO_LEVEL_LOW, IDigitalOut::BOARD_0)).Times(12);

    EXPECT_CALL(*gamepadMock, setKeyState(ABS_X, 2, EV_ABS));
    EXPECT_CALL(*gamepadMock, setKeyState(ABS_Y, 2, EV_ABS));

    EXPECT_CALL(*gamepadMock, setKeyState(BTN_A, 0, EV_KEY));
    EXPECT_CALL(*gamepadMock, setKeyState(BTN_B, 0, EV_KEY));
    EXPECT_CALL(*gamepadMock, setKeyState(BTN_X, 0, EV_KEY));
    EXPECT_CALL(*gamepadMock, setKeyState(BTN_Y, 0, EV_KEY));
    EXPECT_CALL(*gamepadMock, setKeyState(BTN_TL, 0, EV_KEY));
    EXPECT_CALL(*gamepadMock, setKeyState(BTN_TR, 0, EV_KEY));
    EXPECT_CALL(*gamepadMock, setKeyState(BTN_START, 0, EV_KEY));
    EXPECT_CALL(*gamepadMock, setKeyState(BTN_SELECT, 0, EV_KEY));

    EXPECT_CALL(*gamepadMock, sync());

    gamepad.update();
}