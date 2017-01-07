#include "ArcadeGamepad.h"

#include <iostream>
extern "C"
{
#include <linux/input.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
}

ArcadeGamepad::ArcadeGamepad() :
                channel(InputDevice::CHANNEL_UNDEFINED),
                gamepad()
{
}

ArcadeGamepad::~ArcadeGamepad()
{
}

void ArcadeGamepad::initialize(InputDevice::Channel_e channel)
{
    DigitalIn::getInstance().configureDevice(DigitalIn::DI_DEVICE_ALLIN);

    this->channel = channel;
}

void ArcadeGamepad::update()
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
        if (di.getLevel(DigitalIn::DI_CHANNEL_P1_LEFT, boardIn) == DigitalIn::DI_LEVEL_HIGH)
        {
            gamepad.setKeyState(ABS_Y, 4, EV_ABS);
        }
        else if (di.getLevel(DigitalIn::DI_CHANNEL_P1_RIGHT, boardIn) == DigitalIn::DI_LEVEL_HIGH)
        {
            gamepad.setKeyState(ABS_Y, 0, EV_ABS);
        }
        else
        {
            gamepad.setKeyState(ABS_Y, 2, EV_ABS);
        }
        if (di.getLevel(DigitalIn::DI_CHANNEL_P1_UP, boardIn) == DigitalIn::DI_LEVEL_HIGH)
        {
            gamepad.setKeyState(ABS_X, 0, EV_ABS);
        }
        else if (di.getLevel(DigitalIn::DI_CHANNEL_P1_DOWN, boardIn) == DigitalIn::DI_LEVEL_HIGH)
        {
            gamepad.setKeyState(ABS_X, 4, EV_ABS);
        }
        else
        {
            gamepad.setKeyState(ABS_X, 2, EV_ABS);
        }

        // buttons
        gamepad.setKeyState(BTN_A,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_SW1, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad.setKeyState(BTN_B,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_SW2, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad.setKeyState(BTN_C,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_SW3, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad.setKeyState(BTN_X,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_SW4, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad.setKeyState(BTN_Y,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_SW5, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad.setKeyState(BTN_Z,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_SW6, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad.setKeyState(BTN_TL,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_SW7, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad.setKeyState(BTN_TR,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_SW8, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad.setKeyState(BTN_START,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_START, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad.setKeyState(BTN_SELECT,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_COIN, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad.setKeyState(BTN_TL2,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_A, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad.setKeyState(BTN_TR2,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_B, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);

        gamepad.sync();
    }
    else if ((channel == InputDevice::CHANNEL_2) || (channel == InputDevice::CHANNEL_4))
    {
        // axes
        if (di.getLevel(DigitalIn::DI_CHANNEL_P2_LEFT, boardIn) == DigitalIn::DI_LEVEL_HIGH)
        {
            gamepad.setKeyState(ABS_X, 0, EV_ABS);
        }
        else if (di.getLevel(DigitalIn::DI_CHANNEL_P2_RIGHT, boardIn) == DigitalIn::DI_LEVEL_HIGH)
        {
            gamepad.setKeyState(ABS_X, 4, EV_ABS);
        }
        else
        {
            gamepad.setKeyState(ABS_X, 2, EV_ABS);
        }

        if (di.getLevel(DigitalIn::DI_CHANNEL_P2_UP, boardIn) == DigitalIn::DI_LEVEL_HIGH)
        {
            gamepad.setKeyState(ABS_Y, 0, EV_ABS);
        }
        else if (di.getLevel(DigitalIn::DI_CHANNEL_P2_DOWN, boardIn) == DigitalIn::DI_LEVEL_HIGH)
        {
            gamepad.setKeyState(ABS_Y, 4, EV_ABS);
        }
        else
        {
            gamepad.setKeyState(ABS_Y, 2, EV_ABS);
        }

        // buttons
        gamepad.setKeyState(BTN_A,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_SW1, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad.setKeyState(BTN_B,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_SW2, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad.setKeyState(BTN_C,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_SW3, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad.setKeyState(BTN_X,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_SW4, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad.setKeyState(BTN_Y,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_SW5, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad.setKeyState(BTN_Z,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_SW6, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad.setKeyState(BTN_TL,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_SW7, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad.setKeyState(BTN_TR,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_SW8, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad.setKeyState(BTN_START,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_START, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad.setKeyState(BTN_SELECT,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_COIN, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad.setKeyState(BTN_TL2,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_A, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad.setKeyState(BTN_TR2,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_B, boardIn) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);

        gamepad.sync();
    }
    else
    {
        throw -1;
    }
}
