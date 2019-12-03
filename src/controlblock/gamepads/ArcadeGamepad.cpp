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

#include "ArcadeGamepad.h"

ArcadeGamepad::ArcadeGamepad(IUInputFactory& uiFactory, IDigitalIO& digitalIORef) :
        channel(InputDevice::CHANNEL_UNDEFINED),
        digitalIO(digitalIORef),
        gamepad(uiFactory.getUInputDevice(IUInputDevice::TYPE_GAMEPAD_ARCADE))
{
}

void ArcadeGamepad::initialize(InputDevice::Channel_e channel)
{
    digitalIO.configureDevice(IDigitalIO::DIO_DEVICE_ALLIN);
    this->channel = channel;
}

void ArcadeGamepad::update()
{
    if ((channel == InputDevice::CHANNEL_1) || (channel == InputDevice::CHANNEL_3)) {
        // axes
        if (digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_LEFT) == IDigitalIO::DIO_LEVEL_HIGH) {
            gamepad->setKeyState(ABS_X, 0, EV_ABS);
        }
        else if (digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_RIGHT) == IDigitalIO::DIO_LEVEL_HIGH) {
            gamepad->setKeyState(ABS_X, 4, EV_ABS);
        }
        else {
            gamepad->setKeyState(ABS_X, 2, EV_ABS);
        }
        if (digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_UP) == IDigitalIO::DIO_LEVEL_HIGH) {
            gamepad->setKeyState(ABS_Y, 0, EV_ABS);
        }
        else if (digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_DOWN) == IDigitalIO::DIO_LEVEL_HIGH) {
            gamepad->setKeyState(ABS_Y, 4, EV_ABS);
        }
        else {
            gamepad->setKeyState(ABS_Y, 2, EV_ABS);
        }

        // buttons
        gamepad->setKeyState(BTN_A,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_SW1) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad->setKeyState(BTN_B,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_SW2) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad->setKeyState(BTN_C,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_SW3) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad->setKeyState(BTN_X,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_SW4) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad->setKeyState(BTN_Y,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_SW5) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad->setKeyState(BTN_Z,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_SW6) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad->setKeyState(BTN_TL,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_SW7) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad->setKeyState(BTN_TR,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_SW8) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad->setKeyState(BTN_START,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_START) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        gamepad->setKeyState(BTN_SELECT,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_COIN) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        gamepad->setKeyState(BTN_TL2,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_A) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad->setKeyState(BTN_TR2,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_B) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1, EV_KEY);

        gamepad->sync();
    }
    else if ((channel == InputDevice::CHANNEL_2) || (channel == InputDevice::CHANNEL_4)) {
        // axes
        if (digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_LEFT) == IDigitalIO::DIO_LEVEL_HIGH) {
            gamepad->setKeyState(ABS_X, 0, EV_ABS);
        }
        else if (digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_RIGHT) == IDigitalIO::DIO_LEVEL_HIGH) {
            gamepad->setKeyState(ABS_X, 4, EV_ABS);
        }
        else {
            gamepad->setKeyState(ABS_X, 2, EV_ABS);
        }

        if (digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_UP) == IDigitalIO::DIO_LEVEL_HIGH) {
            gamepad->setKeyState(ABS_Y, 0, EV_ABS);
        }
        else if (digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_DOWN) == IDigitalIO::DIO_LEVEL_HIGH) {
            gamepad->setKeyState(ABS_Y, 4, EV_ABS);
        }
        else {
            gamepad->setKeyState(ABS_Y, 2, EV_ABS);
        }

        // buttons
        gamepad->setKeyState(BTN_A,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_SW1) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad->setKeyState(BTN_B,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_SW2) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad->setKeyState(BTN_C,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_SW3) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad->setKeyState(BTN_X,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_SW4) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad->setKeyState(BTN_Y,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_SW5) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad->setKeyState(BTN_Z,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_SW6) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad->setKeyState(BTN_TL,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_SW7) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad->setKeyState(BTN_TR,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_SW8) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad->setKeyState(BTN_START,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_START) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        gamepad->setKeyState(BTN_SELECT,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_COIN) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        gamepad->setKeyState(BTN_TL2,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_A) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad->setKeyState(BTN_TR2,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_B) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1, EV_KEY);

        gamepad->sync();
    }
    else {
        throw std::runtime_error("Unknown channel.");
    }
}
