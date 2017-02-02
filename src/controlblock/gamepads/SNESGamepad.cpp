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
#include "SNESGamepad.h"

SNESGamepad::SNESGamepad(IUInputFactory& uiFactoryRef, IDigitalIn& digitalInRef, IDigitalOut& digitalOutRef) :
        uiFactory(&uiFactoryRef),
        digitalIn(&digitalInRef),
        digitalOut(&digitalOutRef),
        isInitialized(false),
        channel(InputDevice::CHANNEL_UNDEFINED)
{
    gamepad = uiFactory->getUInputDevice(IUInputDevice::TYPE_GAMEPAD_SNES);
    keyboard = uiFactory->getUInputDevice(IUInputDevice::TYPE_KEYVBOARD);
}

void SNESGamepad::initialize(InputDevice::Channel_e channel)
{
    IDigitalOut::BoardNumber_e boardOut;
    if ((channel == InputDevice::CHANNEL_1) || (channel == InputDevice::CHANNEL_2)) {
        boardOut = IDigitalOut::BOARD_0;
    }
    else {
        boardOut = IDigitalOut::BOARD_1;
    }

    digitalIn->configureDevice(IDigitalIn::DI_DEVICE_SNES);
    digitalOut->configureDevice(IDigitalOut::DO_DEVICE_SNES);

    this->channel = channel;

    if (channel == InputDevice::CHANNEL_1) {
        digitalOut->setLevel(IDigitalOut::DO_CHANNEL_P1P2_STROBE, IDigitalOut::DO_LEVEL_LOW, boardOut);
        digitalOut->setLevel(IDigitalOut::DO_CHANNEL_P1P2_CLOCK, IDigitalOut::DO_LEVEL_LOW, boardOut);
        digitalOut->setLevel(IDigitalOut::DO_CHANNEL_P1_VCC, IDigitalOut::DO_LEVEL_HIGH, boardOut);
    }
    else {
        digitalOut->setLevel(IDigitalOut::DO_CHANNEL_P2_VCC, IDigitalOut::DO_LEVEL_HIGH, boardOut);
        // strobe and clock were already initialized with player 1 initialization.
    }

    isInitialized = true;
}

void SNESGamepad::update()
{
    assert(isInitialized);

    uint16_t state = getSNESControllerState();

    // left-right axis
    if ((state & GPAD_SNES_LEFT) == GPAD_SNES_LEFT) {
        gamepad->setKeyState(ABS_X, 0, EV_ABS);
    }
    else if ((state & GPAD_SNES_RIGHT) == GPAD_SNES_RIGHT) {
        gamepad->setKeyState(ABS_X, 4, EV_ABS);
    }
    else {
        gamepad->setKeyState(ABS_X, 2, EV_ABS);
    }

    // up-down axis
    if ((state & GPAD_SNES_UP) == GPAD_SNES_UP) {
        gamepad->setKeyState(ABS_Y, 0, EV_ABS);
    }
    else if ((state & GPAD_SNES_DOWN) == GPAD_SNES_DOWN) {
        gamepad->setKeyState(ABS_Y, 4, EV_ABS);
    }
    else {
        gamepad->setKeyState(ABS_Y, 2, EV_ABS);
    }

    // buttons
    gamepad->setKeyState(BTN_A, (state & GPAD_SNES_A) == GPAD_SNES_A ? 1 : 0, EV_KEY);
    gamepad->setKeyState(BTN_B, (state & GPAD_SNES_B) == GPAD_SNES_B ? 1 : 0, EV_KEY);
    gamepad->setKeyState(BTN_X, (state & GPAD_SNES_X) == GPAD_SNES_X ? 1 : 0, EV_KEY);
    gamepad->setKeyState(BTN_Y, (state & GPAD_SNES_Y) == GPAD_SNES_Y ? 1 : 0, EV_KEY);
    gamepad->setKeyState(BTN_TL, (state & GPAD_SNES_L) == GPAD_SNES_L ? 1 : 0, EV_KEY);
    gamepad->setKeyState(BTN_TR, (state & GPAD_SNES_R) == GPAD_SNES_R ? 1 : 0, EV_KEY);
    gamepad->setKeyState(BTN_START, (state & GPAD_SNES_START) == GPAD_SNES_START ? 1 : 0, EV_KEY);
    gamepad->setKeyState(BTN_SELECT, (state & GPAD_SNES_SELECT) == GPAD_SNES_SELECT ? 1 : 0, EV_KEY);
    gamepad->sync();

    if (channel == InputDevice::CHANNEL_2) {
        IDigitalIn::DI_Level_e resetLevel = digitalIn->getLevel(IDigitalIn::DI_CHANNEL_P2_B, IDigitalIn::BOARD_0);
        keyboard->setKeyState(KEY_ESC, resetLevel == IDigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard->sync();
    }
}

uint16_t SNESGamepad::getSNESControllerState()
{
    const std::chrono::microseconds dura(STROBEDELAY);
    uint16_t state = 0u;

    IDigitalIn::BoardNumber_e boardIn = IDigitalIn::BOARD_0;
    IDigitalOut::BoardNumber_e boardOut = IDigitalOut::BOARD_0;
    if ((channel == InputDevice::CHANNEL_1) || (channel == InputDevice::CHANNEL_2)) {
        boardIn = IDigitalIn::BOARD_0;
        boardOut = IDigitalOut::BOARD_0;
    }
    else {
        boardIn = IDigitalIn::BOARD_1;
        boardOut = IDigitalOut::BOARD_1;
    }

    digitalOut->setLevel(IDigitalOut::DO_CHANNEL_P1P2_STROBE, IDigitalOut::DO_LEVEL_HIGH, boardOut);
    std::this_thread::sleep_for(2 * dura);
    digitalOut->setLevel(IDigitalOut::DO_CHANNEL_P1P2_STROBE, IDigitalOut::DO_LEVEL_LOW, boardOut);
    std::this_thread::sleep_for(dura);

    for (uint8_t i = 0u; i < NUMBER_OF_BUTTONS; i++) {
        IDigitalIn::DI_Level_e curpin;
        if (channel == InputDevice::CHANNEL_1) {
            curpin = digitalIn->getLevel(IDigitalIn::DI_CHANNEL_P1_DATA, boardIn);
        }
        else {
            curpin = digitalIn->getLevel(IDigitalIn::DI_CHANNEL_P2_DATA, boardIn);
        }

        if (curpin == IDigitalIn::DI_LEVEL_HIGH) {
            state |= (1u << i);
        }

        digitalOut->setLevel(IDigitalOut::DO_CHANNEL_P1P2_CLOCK, IDigitalOut::DO_LEVEL_HIGH, boardOut);
        std::this_thread::sleep_for(dura);
        digitalOut->setLevel(IDigitalOut::DO_CHANNEL_P1P2_CLOCK, IDigitalOut::DO_LEVEL_LOW, boardOut);
        std::this_thread::sleep_for(dura);
    }

    return state;
}
