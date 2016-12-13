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

    if (channel == InputDevice::CHANNEL_1)
    {
        // axes
        keyboard.setKeyState(KEY_LEFT,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_LEFT) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_RIGHT,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_RIGHT) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_UP,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_UP) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_DOWN,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_DOWN) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);

        // buttons
        keyboard.setKeyState(KEY_LEFTCTRL,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_SW1) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_LEFTALT,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_SW2) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_SPACE,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_SW3) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_LEFTSHIFT,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_SW4) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_Z,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_SW5) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_X,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_SW6) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_C,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_SW7) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_V,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_SW8) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_1,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_START) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_5,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_COIN) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_P,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_A) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_ENTER,
                di.getLevel(DigitalIn::DI_CHANNEL_P1_B) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);

        keyboard.sync();
    }
    else if (channel == InputDevice::CHANNEL_2)
    {
        // axes
        keyboard.setKeyState(KEY_D,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_LEFT) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_G,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_RIGHT) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_R,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_UP) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_F,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_DOWN) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);

        // buttons
        keyboard.setKeyState(KEY_A,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_SW1) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_S,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_SW2) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_Q,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_SW3) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_W,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_SW4) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_I,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_SW5) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_K,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_SW6) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_J,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_SW7) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_L,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_SW8) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_2,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_START) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_6,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_COIN) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_TAB,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_A) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        keyboard.setKeyState(KEY_ESC,
                di.getLevel(DigitalIn::DI_CHANNEL_P2_B) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);

        keyboard.sync();
    }
    else
    {
        throw 3;
    }
}

