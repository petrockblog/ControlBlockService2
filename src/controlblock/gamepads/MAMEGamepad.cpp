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

MAMEGamepad::MAMEGamepad(IUInputFactory& uiFactory, IDigitalIO& digitalIORef) :
        channel(CHANNEL_UNDEFINED),
        digitalIO(digitalIORef),
        keyboard(uiFactory.getUInputDevice(IUInputDevice::TYPE_KEYBOARD))
{
}

void MAMEGamepad::initialize(InputDevice::Channel_e channel)
{
    digitalIO.configureDevice(IDigitalIO::DIO_DEVICE_ALLIN);

    this->channel = channel;
}

void MAMEGamepad::update()
{
    if ((channel == InputDevice::CHANNEL_1) || (channel == InputDevice::CHANNEL_3)) {
        // axes
        keyboard->setKeyState(KEY_LEFT,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_LEFT) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_RIGHT,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_RIGHT) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_UP,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_UP) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard->setKeyState(KEY_DOWN,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_DOWN) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1,
                EV_KEY);

        // buttons
        keyboard->setKeyState(KEY_LEFTCTRL,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_SW1) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_LEFTALT,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_SW2) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_SPACE,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_SW3) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_LEFTSHIFT,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_SW4) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_Z,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_SW5) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_X,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_SW6) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_C,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_SW7) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_V,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_SW8) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_1,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_START) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_5,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_COIN) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_P,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_A) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard->setKeyState(KEY_ENTER,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_B) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1, EV_KEY);

        keyboard->sync();
    }
    else if ((channel == InputDevice::CHANNEL_2) || (channel == InputDevice::CHANNEL_4)) {
        // axes
        keyboard->setKeyState(KEY_D,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_LEFT) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_G,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_RIGHT) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_R,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_UP) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard->setKeyState(KEY_F,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_DOWN) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1,
                EV_KEY);

        // buttons
        keyboard->setKeyState(KEY_A,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_SW1) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_S,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_SW2) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_Q,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_SW3) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_W,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_SW4) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_I,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_SW5) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_K,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_SW6) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_J,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_SW7) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_L,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_SW8) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_2,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_START) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_6,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_COIN) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        keyboard->setKeyState(KEY_TAB,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_A) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard->setKeyState(KEY_ESC,
                digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_B) == IDigitalIO::DIO_LEVEL_LOW ? 0 : 1, EV_KEY);

        keyboard->sync();
    }
    else {
        throw 3;
    }
}

