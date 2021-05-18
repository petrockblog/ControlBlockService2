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

#include <iostream>
#include <chrono>
#include <thread>
#include "SaturnGamepad.h"

const IDigitalIO::DIO_Channel_e SaturnGamepad::CHN_SELECT0[] = {IDigitalIO::DIO_CHANNEL_P1_SW1,
                                                                IDigitalIO::DIO_CHANNEL_P2_SW1};
const IDigitalIO::DIO_Channel_e SaturnGamepad::CHN_SELECT1[] = {IDigitalIO::DIO_CHANNEL_P1_DOWN,
                                                                IDigitalIO::DIO_CHANNEL_P2_DOWN};

SaturnGamepad::SaturnGamepad(IUInputFactory &uiFactory, IDigitalIO &digitalIORef) : channel(InputDevice::CHANNEL_UNDEFINED),
                                                                                    digitalIO(digitalIORef),
                                                                                    currentState(0u),
                                                                                    lastState(0xFFFF),
                                                                                    playerIndex_(0u),
                                                                                    gamepad(uiFactory.getUInputDevice(IUInputDevice::TYPE_GAMEPAD_SATURN))
{
}

void SaturnGamepad::initialize(InputDevice::Channel_e channel)
{
    if ((channel == InputDevice::CHANNEL_1) || (channel == InputDevice::CHANNEL_3))
    {
        playerIndex_ = 0u;
    }
    else if ((channel == InputDevice::CHANNEL_2) || (channel == InputDevice::CHANNEL_4))
    {
        playerIndex_ = 1u;
    }

    digitalIO.configureDevice(IDigitalIO::DIO_DEVICE_SATURN);

    this->channel = channel;
}

void SaturnGamepad::update()
{
    readButtons();
    sendStates();
}

void SaturnGamepad::readButtons()
{
    const std::chrono::microseconds dura(1);
    currentState = 0u;

    if (playerIndex_ == 0u)
    {
        digitalIO.setLevel(CHN_SELECT1[playerIndex_], IDigitalIO::DIO_LEVEL_LOW);
        digitalIO.setLevel(CHN_SELECT0[playerIndex_], IDigitalIO::DIO_LEVEL_LOW);

        currentState |= (digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_UP) == IDigitalIO::DIO_LEVEL_HIGH ? SATURNBTN_Z : 0);
        currentState |= (digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_LEFT) == IDigitalIO::DIO_LEVEL_HIGH ? SATURNBTN_Y : 0);
        currentState |= (digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_SW4) == IDigitalIO::DIO_LEVEL_HIGH ? SATURNBTN_X : 0);
        currentState |= (digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_SW3) == IDigitalIO::DIO_LEVEL_HIGH ? SATURNBTN_RT : 0);

        digitalIO.setLevel(CHN_SELECT1[playerIndex_], IDigitalIO::DIO_LEVEL_HIGH);
        digitalIO.setLevel(CHN_SELECT0[playerIndex_], IDigitalIO::DIO_LEVEL_LOW);

        currentState |= (digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_UP) == IDigitalIO::DIO_LEVEL_HIGH ? SATURNBTN_B : 0);
        currentState |= (digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_LEFT) == IDigitalIO::DIO_LEVEL_HIGH ? SATURNBTN_C : 0);
        currentState |= (digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_SW4) == IDigitalIO::DIO_LEVEL_HIGH ? SATURNBTN_A : 0);
        currentState |= (digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_SW3) == IDigitalIO::DIO_LEVEL_HIGH ? SATURNBTN_START : 0);

        digitalIO.setLevel(CHN_SELECT1[playerIndex_], IDigitalIO::DIO_LEVEL_LOW);
        digitalIO.setLevel(CHN_SELECT0[playerIndex_], IDigitalIO::DIO_LEVEL_HIGH);

        currentState |= (digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_UP) == IDigitalIO::DIO_LEVEL_HIGH ? SATURNBTN_UP : 0);
        currentState |= (digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_LEFT) == IDigitalIO::DIO_LEVEL_HIGH ? SATURNBTN_DOWN : 0);
        currentState |= (digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_SW4) == IDigitalIO::DIO_LEVEL_HIGH ? SATURNBTN_LEFT : 0);
        currentState |= (digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_SW3) == IDigitalIO::DIO_LEVEL_HIGH ? SATURNBTN_RIGHT : 0);

        digitalIO.setLevel(CHN_SELECT1[playerIndex_], IDigitalIO::DIO_LEVEL_HIGH);
        digitalIO.setLevel(CHN_SELECT0[playerIndex_], IDigitalIO::DIO_LEVEL_HIGH);

        currentState |= (digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P1_SW3) == IDigitalIO::DIO_LEVEL_HIGH ? SATURNBTN_LT : 0);

    }
    else if (playerIndex_ == 1u)
    {
        digitalIO.setLevel(CHN_SELECT1[playerIndex_], IDigitalIO::DIO_LEVEL_LOW);
        digitalIO.setLevel(CHN_SELECT0[playerIndex_], IDigitalIO::DIO_LEVEL_LOW);
        
        currentState |= (digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_UP) == IDigitalIO::DIO_LEVEL_HIGH ? SATURNBTN_Z : 0);
        currentState |= (digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_LEFT) == IDigitalIO::DIO_LEVEL_HIGH ? SATURNBTN_Y : 0);
        currentState |= (digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_SW4) == IDigitalIO::DIO_LEVEL_HIGH ? SATURNBTN_X : 0);
        currentState |= (digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_SW3) == IDigitalIO::DIO_LEVEL_HIGH ? SATURNBTN_RT : 0);

        digitalIO.setLevel(CHN_SELECT1[playerIndex_], IDigitalIO::DIO_LEVEL_HIGH);
        digitalIO.setLevel(CHN_SELECT0[playerIndex_], IDigitalIO::DIO_LEVEL_LOW);
        
        currentState |= (digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_UP) == IDigitalIO::DIO_LEVEL_HIGH ? SATURNBTN_B : 0);
        currentState |= (digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_LEFT) == IDigitalIO::DIO_LEVEL_HIGH ? SATURNBTN_C : 0);
        currentState |= (digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_SW4) == IDigitalIO::DIO_LEVEL_HIGH ? SATURNBTN_A : 0);
        currentState |= (digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_SW3) == IDigitalIO::DIO_LEVEL_HIGH ? SATURNBTN_START : 0);

        digitalIO.setLevel(CHN_SELECT1[playerIndex_], IDigitalIO::DIO_LEVEL_LOW);
        digitalIO.setLevel(CHN_SELECT0[playerIndex_], IDigitalIO::DIO_LEVEL_HIGH);
        
        currentState |= (digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_UP) == IDigitalIO::DIO_LEVEL_HIGH ? SATURNBTN_UP : 0);
        currentState |= (digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_LEFT) == IDigitalIO::DIO_LEVEL_HIGH ? SATURNBTN_DOWN : 0);
        currentState |= (digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_SW4) == IDigitalIO::DIO_LEVEL_HIGH ? SATURNBTN_LEFT : 0);
        currentState |= (digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_SW3) == IDigitalIO::DIO_LEVEL_HIGH ? SATURNBTN_RIGHT : 0);

        digitalIO.setLevel(CHN_SELECT1[playerIndex_], IDigitalIO::DIO_LEVEL_HIGH);
        digitalIO.setLevel(CHN_SELECT0[playerIndex_], IDigitalIO::DIO_LEVEL_HIGH);
        
        currentState |= (digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_P2_SW3) == IDigitalIO::DIO_LEVEL_HIGH ? SATURNBTN_LT : 0);
    }
    else
    {
        throw std::runtime_error("Unknown playerindex_.");
    }
}

void SaturnGamepad::sendStates()
{
    // Only report controller states if at least one has changed
    if (currentState != lastState)
    {
        // left-right axis
        if ((currentState & SATURNBTN_LEFT) == SATURNBTN_LEFT)
        {
            gamepad->setKeyState(ABS_X, 0, EV_ABS);
        }
        else if ((currentState & SATURNBTN_RIGHT) == SATURNBTN_RIGHT)
        {
            gamepad->setKeyState(ABS_X, 4, EV_ABS);
        }
        else
        {
            gamepad->setKeyState(ABS_X, 2, EV_ABS);
        }

        // up-down axis
        if ((currentState & SATURNBTN_UP) == SATURNBTN_UP)
        {
            gamepad->setKeyState(ABS_Y, 0, EV_ABS);
        }
        else if ((currentState & SATURNBTN_DOWN) == SATURNBTN_DOWN)
        {
            gamepad->setKeyState(ABS_Y, 4, EV_ABS);
        }
        else
        {
            gamepad->setKeyState(ABS_Y, 2, EV_ABS);
        }

        // buttons
        gamepad->setKeyState(BTN_A, (currentState & SATURNBTN_A) == SATURNBTN_A ? 1 : 0, EV_KEY);
        gamepad->setKeyState(BTN_B, (currentState & SATURNBTN_B) == SATURNBTN_B ? 1 : 0, EV_KEY);
        gamepad->setKeyState(BTN_C, (currentState & SATURNBTN_C) == SATURNBTN_C ? 1 : 0, EV_KEY);
        gamepad->setKeyState(BTN_X, (currentState & SATURNBTN_X) == SATURNBTN_X ? 1 : 0, EV_KEY);
        gamepad->setKeyState(BTN_Y, (currentState & SATURNBTN_Y) == SATURNBTN_Y ? 1 : 0, EV_KEY);
        gamepad->setKeyState(BTN_Z, (currentState & SATURNBTN_Z) == SATURNBTN_Z ? 1 : 0, EV_KEY);
        gamepad->setKeyState(BTN_TL, (currentState & SATURNBTN_LT) == SATURNBTN_LT ? 1 : 0, EV_KEY);
        gamepad->setKeyState(BTN_TR, (currentState & SATURNBTN_RT) == SATURNBTN_RT ? 1 : 0, EV_KEY);
        gamepad->setKeyState(BTN_START, (currentState & SATURNBTN_START) == SATURNBTN_START ? 1 : 0, EV_KEY);

        gamepad->sync();
    }
    lastState = currentState;
}
