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

#include <chrono>
#include <thread>
#include <assert.h>
#include <iostream>
#include "NESGamepad.h"

NESGamepad::NESGamepad(IUInputFactory& uiFactoryRef, IDigitalIO& digitalIORef) :
        uiFactory(uiFactoryRef),
        digitalIO(digitalIORef),
        isInitialized(false),
        channel(InputDevice::CHANNEL_UNDEFINED)
{
    gamepad = uiFactory.getUInputDevice(IUInputDevice::TYPE_GAMEPAD_NES);
    keyboard = uiFactory.getUInputDevice(IUInputDevice::TYPE_KEYBOARD);
}

void NESGamepad::initialize(InputDevice::Channel_e channel)
{
    assert(digitalIn != NULL);
    assert(digitalOut != NULL);

    this->channel = channel;

    if (channel == InputDevice::CHANNEL_1) {
        digitalIO.setLevel(DIO_CHANNEL_P1P2_STROBE, IDigitalIO::DIO_LEVEL_LOW);  // player 1,2 strobe/latch
        digitalIO.setLevel(DIO_CHANNEL_P1P2_CLOCK, IDigitalIO::DIO_LEVEL_LOW);  // player 1,2 clock
        digitalIO.setLevel(DIO_CHANNEL_P1_VCC, IDigitalIO::DIO_LEVEL_HIGH);  // player 1 VCC
    }
    else {
        digitalIO.setLevel(DIO_CHANNEL_P2_VCC, IDigitalIO::DIO_LEVEL_HIGH);  // player 2 VCC
        // strobe and clock were already initialized with player 1 initialization.
    }

    isInitialized = true;    
}

void NESGamepad::update()
{
    assert(isInitialized);

    uint16_t state = getNESControllerState();

    if (channel == InputDevice::CHANNEL_1) {
        IDigitalIO::DIO_Level_e levelButton1 = digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_B);
        if (levelButton1 == IDigitalIO::DIO_LEVEL_HIGH)
        {
            state |= GPAD_NES_SELECT;
            state |= GPAD_NES_START;
            keyboard->setKeyState(KEY_ESC, 0, EV_KEY);
        }
        else
        {
            keyboard->setKeyState(KEY_ESC, 1, EV_KEY);
        }

        IDigitalIO::DIO_Level_e levelButton2 = digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_A);
        if (levelButton2 == IDigitalIO::DIO_LEVEL_HIGH)
        {
            state |= GPAD_NES_SELECT;
            state |= GPAD_NES_B;
            keyboard->setKeyState(KEY_F1, 0, EV_KEY);
        }
        else
        {
            keyboard->setKeyState(KEY_F1, 1, EV_KEY);
        }
        keyboard->sync();
    }

    // left-right axis
    if ((state & GPAD_NES_LEFT) == GPAD_NES_LEFT) {
        gamepad->setKeyState(ABS_X, 0, EV_ABS);
    }
    else if ((state & GPAD_NES_RIGHT) == GPAD_NES_RIGHT) {
        gamepad->setKeyState(ABS_X, 4, EV_ABS);
    }
    else {
        gamepad->setKeyState(ABS_X, 2, EV_ABS);
    }

    // up-down axis
    if ((state & GPAD_NES_UP) == GPAD_NES_UP) {
        gamepad->setKeyState(ABS_Y, 0, EV_ABS);
    }
    else if ((state & GPAD_NES_DOWN) == GPAD_NES_DOWN) {
        gamepad->setKeyState(ABS_Y, 4, EV_ABS);
    }
    else {
        gamepad->setKeyState(ABS_Y, 2, EV_ABS);
    }

    // buttons
    gamepad->setKeyState(BTN_B, (state & GPAD_NES_B) == GPAD_NES_B ? 1 : 0, EV_KEY);
    gamepad->setKeyState(BTN_A, (state & GPAD_NES_A) == GPAD_NES_A ? 1 : 0, EV_KEY);
    gamepad->setKeyState(BTN_START, (state & GPAD_NES_START) == GPAD_NES_START ? 1 : 0, EV_KEY);
    gamepad->setKeyState(BTN_SELECT, (state & GPAD_NES_SELECT) == GPAD_NES_SELECT ? 1 : 0, EV_KEY);
    gamepad->sync();
}

uint16_t NESGamepad::getNESControllerState()
{
    const std::chrono::microseconds dura(STROBEDELAY_US);
    uint16_t state = 0u;

    digitalIO.setLevel(DIO_CHANNEL_P1P2_STROBE, IDigitalIO::DIO_LEVEL_HIGH);
    std::this_thread::sleep_for(2 * dura);
    digitalIO.setLevel(DIO_CHANNEL_P1P2_STROBE, IDigitalIO::DIO_LEVEL_LOW);
    std::this_thread::sleep_for(2 * dura);

    for (uint8_t i = 0u; i < NUMBER_OF_BUTTONS; i++) {
        IDigitalIO::DIO_Level_e curpin;
        if (channel == InputDevice::CHANNEL_1) {
            curpin = digitalIO.getLevel(DIO_CHANNEL_P1_DATA);
        }
        else {
            curpin = digitalIO.getLevel(DIO_CHANNEL_P2_DATA);
        }

        if (curpin == IDigitalIO::DIO_LEVEL_HIGH) {
            state |= (1u << i);
        }

        digitalIO.setLevel(DIO_CHANNEL_P1P2_CLOCK, IDigitalIO::DIO_LEVEL_HIGH);
        std::this_thread::sleep_for(dura);
        digitalIO.setLevel(DIO_CHANNEL_P1P2_CLOCK, IDigitalIO::DIO_LEVEL_LOW);
        std::this_thread::sleep_for(dura);
    }

    return state;
}
