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

MAMEGamepad::MAMEGamepad() :
                channel(CHANNEL_UNDEFINED),
                keyboard()
{
}

MAMEGamepad::~MAMEGamepad()
{
}

void MAMEGamepad::initialize(InputDevice::Channel_e channel)
{
    DigitalIn::getInstance().configureDevice(DigitalIn::DI_DEVICE_ALLIN);

    this->channel = channel;
}

void MAMEGamepad::update()
{
    DigitalIn di = DigitalIn::getInstance();

    DigitalIn::BoardNumber_e boardIn = DigitalIn::BOARD_0;
    if ((channel == InputDevice::CHANNEL_1) || (channel == InputDevice::CHANNEL_2))
    {
        boardIn = DigitalIn::BOARD_0;
    }
    else
    {
        boardIn = DigitalIn::BOARD_1;
    }

    if ((channel == InputDevice::CHANNEL_1) || (channel == InputDevice::CHANNEL_3))
    {
        // axes
        keyboard.setKeyState(KEY_LEFT,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_LEFT, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_RIGHT,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_RIGHT, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_UP,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_UP, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_DOWN,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_DOWN, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);

        // buttons
        keyboard.setKeyState(KEY_LEFTCTRL,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_SW1, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_LEFTALT,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_SW2, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_SPACE,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_SW3, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_LEFTSHIFT,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_SW4, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_Z,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_SW5, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_X,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_SW6, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_C,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_SW7, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_V,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_SW8, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_1,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_START, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_5,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_COIN, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_P,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_A, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_ENTER,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_B, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);

        keyboard.sync();
    }
    else if ((channel == InputDevice::CHANNEL_2) || (channel == InputDevice::CHANNEL_4))
    {
        // axes
        keyboard.setKeyState(KEY_D,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_LEFT, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_G,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_RIGHT, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_R,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_UP, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_F,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_DOWN, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);

        // buttons
        keyboard.setKeyState(KEY_A,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_SW1, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_S,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_SW2, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_Q,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_SW3, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_W,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_SW4, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_I,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_SW5, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_K,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_SW6, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_J,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_SW7, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_L,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_SW8, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_2,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_START, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_6,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_COIN, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_TAB,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_A, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_ESC,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_B, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);

        keyboard.sync();
    }
    else
    {
        throw 3;
    }
}

