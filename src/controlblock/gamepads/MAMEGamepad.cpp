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

#include "MAMEGamepad.h"

MAMEGamepad::MAMEGamepad(IUInputFactory& uiFactory, IDigitalIn& digitalInRef) :
        channel(CHANNEL_UNDEFINED),
        digitalIn(&digitalInRef)
{
    keyboard = uiFactory.getUInputDevice(IUInputDevice::TYPE_KEYVBOARD);
}

void MAMEGamepad::initialize(InputDevice::Channel_e channel)
{
    digitalIn->configureDevice(IDigitalIn::DI_DEVICE_ALLIN);

    this->channel = channel;
}

void MAMEGamepad::update()
{
    IDigitalIn::BoardNumber_e boardIn = IDigitalIn::BOARD_0;
    if ((channel == InputDevice::CHANNEL_1) || (channel == InputDevice::CHANNEL_2)) {
        boardIn = IDigitalIn::BOARD_0;
    }
    else {
        boardIn = IDigitalIn::BOARD_1;
    }

    if ((channel == InputDevice::CHANNEL_1) || (channel == InputDevice::CHANNEL_3)) {
        // axes
        keyboard->setKeyState(KEY_LEFT,
                digitalIn->getLevel(IDigitalIn::DI_CHANNEL_P1_LEFT, boardIn) == IDigitalIn::DI_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_RIGHT,
                digitalIn->getLevel(IDigitalIn::DI_CHANNEL_P1_RIGHT, boardIn) == IDigitalIn::DI_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_UP,
                digitalIn->getLevel(IDigitalIn::DI_CHANNEL_P1_UP, boardIn) == IDigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard->setKeyState(KEY_DOWN,
                digitalIn->getLevel(IDigitalIn::DI_CHANNEL_P1_DOWN, boardIn) == IDigitalIn::DI_LEVEL_LOW ? 0 : 1,
                EV_KEY);

        // buttons
        keyboard->setKeyState(KEY_LEFTCTRL,
                digitalIn->getLevel(IDigitalIn::DI_CHANNEL_P1_SW1, boardIn) == IDigitalIn::DI_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_LEFTALT,
                digitalIn->getLevel(IDigitalIn::DI_CHANNEL_P1_SW2, boardIn) == IDigitalIn::DI_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_SPACE,
                digitalIn->getLevel(IDigitalIn::DI_CHANNEL_P1_SW3, boardIn) == IDigitalIn::DI_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_LEFTSHIFT,
                digitalIn->getLevel(IDigitalIn::DI_CHANNEL_P1_SW4, boardIn) == IDigitalIn::DI_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_Z,
                digitalIn->getLevel(IDigitalIn::DI_CHANNEL_P1_SW5, boardIn) == IDigitalIn::DI_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_X,
                digitalIn->getLevel(IDigitalIn::DI_CHANNEL_P1_SW6, boardIn) == IDigitalIn::DI_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_C,
                digitalIn->getLevel(IDigitalIn::DI_CHANNEL_P1_SW7, boardIn) == IDigitalIn::DI_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_V,
                digitalIn->getLevel(IDigitalIn::DI_CHANNEL_P1_SW8, boardIn) == IDigitalIn::DI_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_1,
                digitalIn->getLevel(IDigitalIn::DI_CHANNEL_P1_START, boardIn) == IDigitalIn::DI_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_5,
                digitalIn->getLevel(IDigitalIn::DI_CHANNEL_P1_COIN, boardIn) == IDigitalIn::DI_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_P,
                digitalIn->getLevel(IDigitalIn::DI_CHANNEL_P1_A, boardIn) == IDigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard->setKeyState(KEY_ENTER,
                digitalIn->getLevel(IDigitalIn::DI_CHANNEL_P1_B, boardIn) == IDigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);

        keyboard->sync();
    }
    else if ((channel == InputDevice::CHANNEL_2) || (channel == InputDevice::CHANNEL_4)) {
        // axes
        keyboard->setKeyState(KEY_D,
                digitalIn->getLevel(IDigitalIn::DI_CHANNEL_P2_LEFT, boardIn) == IDigitalIn::DI_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_G,
                digitalIn->getLevel(IDigitalIn::DI_CHANNEL_P2_RIGHT, boardIn) == IDigitalIn::DI_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_R,
                digitalIn->getLevel(IDigitalIn::DI_CHANNEL_P2_UP, boardIn) == IDigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard->setKeyState(KEY_F,
                digitalIn->getLevel(IDigitalIn::DI_CHANNEL_P2_DOWN, boardIn) == IDigitalIn::DI_LEVEL_LOW ? 0 : 1,
                EV_KEY);

        // buttons
        keyboard->setKeyState(KEY_A,
                digitalIn->getLevel(IDigitalIn::DI_CHANNEL_P2_SW1, boardIn) == IDigitalIn::DI_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_S,
                digitalIn->getLevel(IDigitalIn::DI_CHANNEL_P2_SW2, boardIn) == IDigitalIn::DI_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_Q,
                digitalIn->getLevel(IDigitalIn::DI_CHANNEL_P2_SW3, boardIn) == IDigitalIn::DI_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_W,
                digitalIn->getLevel(IDigitalIn::DI_CHANNEL_P2_SW4, boardIn) == IDigitalIn::DI_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_I,
                digitalIn->getLevel(IDigitalIn::DI_CHANNEL_P2_SW5, boardIn) == IDigitalIn::DI_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_K,
                digitalIn->getLevel(IDigitalIn::DI_CHANNEL_P2_SW6, boardIn) == IDigitalIn::DI_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_J,
                digitalIn->getLevel(IDigitalIn::DI_CHANNEL_P2_SW7, boardIn) == IDigitalIn::DI_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_L,
                digitalIn->getLevel(IDigitalIn::DI_CHANNEL_P2_SW8, boardIn) == IDigitalIn::DI_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_2,
                digitalIn->getLevel(IDigitalIn::DI_CHANNEL_P2_START, boardIn) == IDigitalIn::DI_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_6,
                digitalIn->getLevel(IDigitalIn::DI_CHANNEL_P2_COIN, boardIn) == IDigitalIn::DI_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_TAB,
                digitalIn->getLevel(IDigitalIn::DI_CHANNEL_P2_A, boardIn) == IDigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard->setKeyState(KEY_ESC,
                digitalIn->getLevel(IDigitalIn::DI_CHANNEL_P2_B, boardIn) == IDigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);

        keyboard->sync();
    }
    else {
        throw 3;
    }
}

