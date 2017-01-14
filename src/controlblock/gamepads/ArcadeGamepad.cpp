#include "ArcadeGamepad.h"

ArcadeGamepad::ArcadeGamepad(IUInputFactory& uiFactory, IDigitalIn& digitalInRef)
        :
        channel(InputDevice::CHANNEL_UNDEFINED),
        digitalIn(digitalInRef)
{
    gamepad = uiFactory.getUInputDevice(IUInputDevice::TYPE_GAMEPAD_ARCADE);
}

void ArcadeGamepad::initialize(InputDevice::Channel_e channel)
{
    digitalIn.configureDevice(IDigitalIn::DI_DEVICE_ALLIN);
    this->channel = channel;
}

void ArcadeGamepad::update()
{
    IDigitalIn::BoardNumber_e boardIn;
    if ((channel==InputDevice::CHANNEL_1) || (channel==InputDevice::CHANNEL_2)) {
        boardIn = IDigitalIn::BOARD_0;
    }
    else {
        boardIn = IDigitalIn::BOARD_1;
    }

    if ((channel==InputDevice::CHANNEL_1) || (channel==InputDevice::CHANNEL_3)) {
        // axes
        if (digitalIn.getLevel(IDigitalIn::DI_CHANNEL_P1_LEFT, boardIn)==IDigitalIn::DI_LEVEL_HIGH) {
            gamepad->setKeyState(ABS_Y, 0, EV_ABS);
        }
        else if (digitalIn.getLevel(IDigitalIn::DI_CHANNEL_P1_RIGHT, boardIn)==IDigitalIn::DI_LEVEL_HIGH) {
            gamepad->setKeyState(ABS_Y, 4, EV_ABS);
        }
        else {
            gamepad->setKeyState(ABS_Y, 2, EV_ABS);
        }
        if (digitalIn.getLevel(IDigitalIn::DI_CHANNEL_P1_UP, boardIn)==IDigitalIn::DI_LEVEL_HIGH) {
            gamepad->setKeyState(ABS_X, 4, EV_ABS);
        }
        else if (digitalIn.getLevel(IDigitalIn::DI_CHANNEL_P1_DOWN, boardIn)==IDigitalIn::DI_LEVEL_HIGH) {
            gamepad->setKeyState(ABS_X, 0, EV_ABS);
        }
        else {
            gamepad->setKeyState(ABS_X, 2, EV_ABS);
        }

        // buttons
        gamepad->setKeyState(BTN_A,
                digitalIn.getLevel(IDigitalIn::DI_CHANNEL_P1_SW1, boardIn)==IDigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad->setKeyState(BTN_B,
                digitalIn.getLevel(IDigitalIn::DI_CHANNEL_P1_SW2, boardIn)==IDigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad->setKeyState(BTN_C,
                digitalIn.getLevel(IDigitalIn::DI_CHANNEL_P1_SW3, boardIn)==IDigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad->setKeyState(BTN_X,
                digitalIn.getLevel(IDigitalIn::DI_CHANNEL_P1_SW4, boardIn)==IDigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad->setKeyState(BTN_Y,
                digitalIn.getLevel(IDigitalIn::DI_CHANNEL_P1_SW5, boardIn)==IDigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad->setKeyState(BTN_Z,
                digitalIn.getLevel(IDigitalIn::DI_CHANNEL_P1_SW6, boardIn)==IDigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad->setKeyState(BTN_TL,
                digitalIn.getLevel(IDigitalIn::DI_CHANNEL_P1_SW7, boardIn)==IDigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad->setKeyState(BTN_TR,
                digitalIn.getLevel(IDigitalIn::DI_CHANNEL_P1_SW8, boardIn)==IDigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad->setKeyState(BTN_START,
                digitalIn.getLevel(IDigitalIn::DI_CHANNEL_P1_START, boardIn)==IDigitalIn::DI_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        gamepad->setKeyState(BTN_SELECT,
                digitalIn.getLevel(IDigitalIn::DI_CHANNEL_P1_COIN, boardIn)==IDigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad->setKeyState(BTN_TL2,
                digitalIn.getLevel(IDigitalIn::DI_CHANNEL_P1_A, boardIn)==IDigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad->setKeyState(BTN_TR2,
                digitalIn.getLevel(IDigitalIn::DI_CHANNEL_P1_B, boardIn)==IDigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);

        gamepad->sync();
    }
    else if ((channel==InputDevice::CHANNEL_2) || (channel==InputDevice::CHANNEL_4)) {
        // axes
        if (digitalIn.getLevel(IDigitalIn::DI_CHANNEL_P2_LEFT, boardIn)==IDigitalIn::DI_LEVEL_HIGH) {
            gamepad->setKeyState(ABS_Y, 0, EV_ABS);
        }
        else if (digitalIn.getLevel(IDigitalIn::DI_CHANNEL_P2_RIGHT, boardIn)==IDigitalIn::DI_LEVEL_HIGH) {
            gamepad->setKeyState(ABS_Y, 4, EV_ABS);
        }
        else {
            gamepad->setKeyState(ABS_Y, 2, EV_ABS);
        }

        if (digitalIn.getLevel(IDigitalIn::DI_CHANNEL_P2_UP, boardIn)==IDigitalIn::DI_LEVEL_HIGH) {
            gamepad->setKeyState(ABS_X, 4, EV_ABS);
        }
        else if (digitalIn.getLevel(IDigitalIn::DI_CHANNEL_P2_DOWN, boardIn)==IDigitalIn::DI_LEVEL_HIGH) {
            gamepad->setKeyState(ABS_X, 0, EV_ABS);
        }
        else {
            gamepad->setKeyState(ABS_X, 2, EV_ABS);
        }

        // buttons
        gamepad->setKeyState(BTN_A,
                digitalIn.getLevel(IDigitalIn::DI_CHANNEL_P2_SW1, boardIn)==IDigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad->setKeyState(BTN_B,
                digitalIn.getLevel(IDigitalIn::DI_CHANNEL_P2_SW2, boardIn)==IDigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad->setKeyState(BTN_C,
                digitalIn.getLevel(IDigitalIn::DI_CHANNEL_P2_SW3, boardIn)==IDigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad->setKeyState(BTN_X,
                digitalIn.getLevel(IDigitalIn::DI_CHANNEL_P2_SW4, boardIn)==IDigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad->setKeyState(BTN_Y,
                digitalIn.getLevel(IDigitalIn::DI_CHANNEL_P2_SW5, boardIn)==IDigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad->setKeyState(BTN_Z,
                digitalIn.getLevel(IDigitalIn::DI_CHANNEL_P2_SW6, boardIn)==IDigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad->setKeyState(BTN_TL,
                digitalIn.getLevel(IDigitalIn::DI_CHANNEL_P2_SW7, boardIn)==IDigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad->setKeyState(BTN_TR,
                digitalIn.getLevel(IDigitalIn::DI_CHANNEL_P2_SW8, boardIn)==IDigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad->setKeyState(BTN_START,
                digitalIn.getLevel(IDigitalIn::DI_CHANNEL_P2_START, boardIn)==IDigitalIn::DI_LEVEL_LOW ? 0 : 1,
                EV_KEY);
        gamepad->setKeyState(BTN_SELECT,
                digitalIn.getLevel(IDigitalIn::DI_CHANNEL_P2_COIN, boardIn)==IDigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad->setKeyState(BTN_TL2,
                digitalIn.getLevel(IDigitalIn::DI_CHANNEL_P2_A, boardIn)==IDigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
        gamepad->setKeyState(BTN_TR2,
                digitalIn.getLevel(IDigitalIn::DI_CHANNEL_P2_B, boardIn)==IDigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);

        gamepad->sync();
    }
    else {
        throw -1;
    }
}
