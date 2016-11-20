#include <chrono>
#include <thread>
#include <iostream>

#include "SNESGamepad.h"

SNESGamepad::SNESGamepad() :
                channel(InputDevice::CHANNEL_UNDEFINED),
                gamepad(),
                keyboard()
{
}

SNESGamepad::~SNESGamepad()
{
}

void SNESGamepad::initialize(InputDevice::Channel_e channel)
{
    DigitalIn::getInstance().configureDevice(DigitalIn::DI_DEVICE_SNES);
    DigitalOut::getInstance().configureDevice(DigitalOut::DO_DEVICE_SNES);

    this->channel = channel;

    DigitalOut dout = DigitalOut::getInstance();
    if (channel == InputDevice::CHANNEL_1)
    {
        dout.setLevel(DigitalOut::DO_CHANNEL_P1P2_STROBE, DigitalOut::DO_LEVEL_LOW);
        dout.setLevel(DigitalOut::DO_CHANNEL_P1P2_CLOCK, DigitalOut::DO_LEVEL_LOW);
        dout.setLevel(DigitalOut::DO_CHANNEL_P1_VCC, DigitalOut::DO_LEVEL_HIGH);
    }
    else
    {
        dout.setLevel(DigitalOut::DO_CHANNEL_P2_VCC, DigitalOut::DO_LEVEL_HIGH);
        // strobe and clock were already initialized with player 1 initialization.
    }
}

uint16_t SNESGamepad::getSNESControllerState()
{
    uint16_t state = 0u;

    DigitalIn din = DigitalIn::getInstance();
    DigitalOut dout = DigitalOut::getInstance();

    dout.setLevel(DigitalOut::DO_CHANNEL_P1P2_STROBE, DigitalOut::DO_LEVEL_HIGH);
    delayMicroseconds(2u * STROBEDELAY);
    dout.setLevel(DigitalOut::DO_CHANNEL_P1P2_STROBE, DigitalOut::DO_LEVEL_LOW);
    delayMicroseconds (STROBEDELAY);

    for (uint8_t i = 0u; i < 16u; i++)
    {
        DigitalIn::DI_Level_e curpin;
        if (channel == InputDevice::CHANNEL_1)
        {
            curpin = din.getLevel(DigitalIn::DI_CHANNEL_P1_DATA);
        }
        else
        {
            curpin = din.getLevel(DigitalIn::DI_CHANNEL_P2_DATA);
        }

        if (curpin == DigitalIn::DI_LEVEL_HIGH)
        {
            state |= (1u << i);
        }

        dout.setLevel(DigitalOut::DO_CHANNEL_P1P2_CLOCK, DigitalOut::DO_LEVEL_HIGH);
        delayMicroseconds(STROBEDELAY);
        dout.setLevel(DigitalOut::DO_CHANNEL_P1P2_CLOCK, DigitalOut::DO_LEVEL_LOW);
        delayMicroseconds(STROBEDELAY);
    }

    return state;
}

void SNESGamepad::update()
{
    DigitalIn di = DigitalIn::getInstance();
    DigitalIn::DI_Level_e resetLevel = di.getLevel(DigitalIn::DI_CHANNEL_P2_B);
    gamepad.setKeyState(KEY_ESC, resetLevel == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);

    uint16_t state = getSNESControllerState();

    // left-right axis
    if ((state & GPAD_SNES_LEFT) == GPAD_SNES_LEFT)
    {
        gamepad.setKeyState(ABS_X, 0, EV_ABS);
    }
    else if ((state & GPAD_SNES_RIGHT) == GPAD_SNES_RIGHT)
    {
        gamepad.setKeyState(ABS_X, 4, EV_ABS);
    }
    else
    {
        gamepad.setKeyState(ABS_X, 2, EV_ABS);
    }

    // up-down axis
    if ((state & GPAD_SNES_UP) == GPAD_SNES_UP)
    {
        gamepad.setKeyState(ABS_Y, 0, EV_ABS);
    }
    else if ((state & GPAD_SNES_DOWN) == GPAD_SNES_DOWN)
    {
        gamepad.setKeyState(ABS_Y, 4, EV_ABS);
    }
    else
    {
        gamepad.setKeyState(ABS_Y, 2, EV_ABS);
    }

    // buttons
    gamepad.setKeyState(BTN_A, (state & GPAD_SNES_A) == GPAD_SNES_A ? 1 : 0, EV_KEY);
    gamepad.setKeyState(BTN_B, (state & GPAD_SNES_B) == GPAD_SNES_B ? 1 : 0, EV_KEY);
    gamepad.setKeyState(BTN_X, (state & GPAD_SNES_X) == GPAD_SNES_X ? 1 : 0, EV_KEY);
    gamepad.setKeyState(BTN_Y, (state & GPAD_SNES_Y) == GPAD_SNES_Y ? 1 : 0, EV_KEY);
    gamepad.setKeyState(BTN_TL, (state & GPAD_SNES_L) == GPAD_SNES_L ? 1 : 0, EV_KEY);
    gamepad.setKeyState(BTN_TR, (state & GPAD_SNES_R) == GPAD_SNES_R ? 1 : 0, EV_KEY);
    gamepad.setKeyState(BTN_START, (state & GPAD_SNES_START) == GPAD_SNES_START ? 1 : 0, EV_KEY);
    gamepad.setKeyState(BTN_SELECT, (state & GPAD_SNES_SELECT) == GPAD_SNES_SELECT ? 1 : 0, EV_KEY);

    gamepad.sync();

    if (channel == InputDevice::CHANNEL_1)
    {
        keyboard.setKeyState(KEY_ESC,
                di.getLevel(DigitalIn::DI_CHANNEL_SNES_RESET) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
    }
}
