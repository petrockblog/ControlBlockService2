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
#include "GenesisGamepad.h"

const IDigitalOut::DO_Channel_e GenesisGamepad::CHN_SELECT[] = {IDigitalOut::DO_CHANNEL_GENESIS_P1_SELECT,
                                                                IDigitalOut::DO_CHANNEL_GENESIS_P2_SELECT};  //!< Controller DB9 Pin 7 Mapping

/**
 * Controller DB9 Pin to Button Flag Mappings
 * First column is the controller index, second column
 * is the input pin that the controller's DB9 pin is
 * attached to, remaing columns are the button flags
 */
const GenesisGamepad::Input GenesisGamepad::inputMap[] = {
        {0, IDigitalIn::DI_CHANNEL_P1_RIGHT, UP,    UP,    Z}, // P0 DB9 Pin 1
        {0, IDigitalIn::DI_CHANNEL_P1_LEFT,  DOWN,  DOWN,  Y}, // P0 DB9 Pin 2
        {0, IDigitalIn::DI_CHANNEL_P1_UP,    ON,    LEFT,  X}, // P0 DB9 Pin 3
        {0, IDigitalIn::DI_CHANNEL_P1_DOWN,  ON,    RIGHT, MODE}, // P0 DB9 Pin 4
        {0, IDigitalIn::DI_CHANNEL_P1_SW2,   A,     B, 0}, // P0 DB9 Pin 6
        {0, IDigitalIn::DI_CHANNEL_P1_SW5,   START, C, 0}, // P0 DB9 Pin 9
        {1, IDigitalIn::DI_CHANNEL_P2_RIGHT, UP,    UP,    Z}, // P1 DB9 Pin 1
        {1, IDigitalIn::DI_CHANNEL_P2_LEFT,  DOWN,  DOWN,  Y}, // P1 DB9 Pin 2
        {1, IDigitalIn::DI_CHANNEL_P2_UP,    ON,    LEFT,  X}, // P1 DB9 Pin 3
        {1, IDigitalIn::DI_CHANNEL_P2_DOWN,  ON,    RIGHT, MODE}, // P1 DB9 Pin 4
        {1, IDigitalIn::DI_CHANNEL_P2_SW2,   A,     B, 0}, // P1 DB9 Pin 6
        {1, IDigitalIn::DI_CHANNEL_P2_SW5,   START, C, 0}, // P1 DB9 Pin 9
};

GenesisGamepad::GenesisGamepad(IUInputFactory& uiFactory, IDigitalIn& digitalInRef, IDigitalOut& digitalOutRef) :
        channel(InputDevice::CHANNEL_UNDEFINED),
        digitalIn(digitalInRef),
        digitalOut(digitalOutRef),
        isInSixButtonMode(false),
        currentState(0u),
        lastState(0xFFFF),
        boardIn(IDigitalIn::BOARD_0),
        boardOut(IDigitalOut::BOARD_0),
        playerIndex(0u),
        gamepad(uiFactory.getUInputDevice(IUInputDevice::TYPE_GAMEPAD_GENESIS))
{
}

void GenesisGamepad::initialize(InputDevice::Channel_e channel)
{
    if ((channel == InputDevice::CHANNEL_1) || (channel == InputDevice::CHANNEL_2))
    {
        boardIn = IDigitalIn::BOARD_0;
        boardOut = IDigitalOut::BOARD_0;
    }
    else {
        boardIn = IDigitalIn::BOARD_1;
        boardOut = IDigitalOut::BOARD_1;
    }

    if ((channel == InputDevice::CHANNEL_1) || (channel == InputDevice::CHANNEL_3))
    {
        playerIndex = 0u;
    }
    else if ((channel == InputDevice::CHANNEL_2) || (channel == InputDevice::CHANNEL_4))
    {
        playerIndex = 1u;
    }

    digitalIn.configureDevice(IDigitalIn::DI_DEVICE_GENESIS);
    digitalOut.configureDevice(IDigitalOut::DO_DEVICE_GENESIS);

    this->channel = channel;
}

void GenesisGamepad::update()
{
    readButtons();
    sendStates();
}

void GenesisGamepad::readButtons()
{
    resetState();
    if (isInSixButtonMode)
    {
        read6buttons(playerIndex);
    }
    else
    {
        read3buttons(playerIndex);
    }
}

void GenesisGamepad::resetState()
{
    currentState = 0u;
}

void GenesisGamepad::read3buttons(int player)
{
    // Set SELECT LOW and read lowFlag
    digitalOut.setLevel(CHN_SELECT[player], IDigitalOut::DO_LEVEL_LOW, boardOut);
    for (int i = 0; i < sizeof(inputMap) / sizeof(Input); i++) {
        if ((inputMap[i].player == player)
                && (digitalIn.getLevel(inputMap[i].inputChannel, boardIn) == IDigitalIn::DI_LEVEL_HIGH)) {
            currentState |= inputMap[i].lowFlag;
        }
    }

    // Set SELECT HIGH and read highFlag
    digitalOut.setLevel(CHN_SELECT[player], IDigitalOut::DO_LEVEL_HIGH, boardOut);
    for (int i = 0; i < sizeof(inputMap) / sizeof(Input); i++) {
        if ((inputMap[i].player == player)
                && (digitalIn.getLevel(inputMap[i].inputChannel, boardIn) == IDigitalIn::DI_LEVEL_HIGH)) {
            currentState |= inputMap[i].highFlag;
        }
    }

    const bool shouldSwitchTo6ButtonMode = ((currentState & (ON | START | A | B | C | UP)) == (ON | START | A | B | C | UP));
    if (shouldSwitchTo6ButtonMode)
    {
        isInSixButtonMode = true;
    }
    // When a controller disconnects, revert to three-button polling
    else if ((currentState & ON) != ON)
    {
       isInSixButtonMode = false;
    }
}

void GenesisGamepad::read6buttons(int player)
{
    // Poll for three-button states twice
    read3buttons(player);
    read3buttons(player);

    // After two three-button polls, pulse the SELECT line
    // so the six-button reports the higher button states
    digitalOut.setLevel(CHN_SELECT[player], IDigitalOut::DO_LEVEL_LOW, boardOut);
    digitalOut.setLevel(CHN_SELECT[player], IDigitalOut::DO_LEVEL_HIGH, boardOut);

    for (int i = 0; i < sizeof(inputMap) / sizeof(Input); i++) {
        if ((inputMap[i].player == player)
                && (digitalIn.getLevel(inputMap[i].inputChannel, boardIn) == IDigitalIn::DI_LEVEL_HIGH)) {
            currentState |= inputMap[i].pulse3Flag;
        }
    }
}

void GenesisGamepad::sendStates()
{
    // Only report controller states if at least one has changed
    if (currentState != lastState) {
        // left-right axis
        if ((currentState & LEFT) == LEFT) {
            gamepad->setKeyState(ABS_X, 0, EV_ABS);
        }
        else if ((currentState & RIGHT) == RIGHT) {
            gamepad->setKeyState(ABS_X, 4, EV_ABS);
        }
        else {
            gamepad->setKeyState(ABS_X, 2, EV_ABS);
        }

        // up-down axis
        if ((currentState & UP) == UP) {
            gamepad->setKeyState(ABS_Y, 0, EV_ABS);
        }
        else if ((currentState & DOWN) == DOWN) {
            gamepad->setKeyState(ABS_Y, 4, EV_ABS);
        }
        else {
            gamepad->setKeyState(ABS_Y, 2, EV_ABS);
        }

        // buttons
        gamepad->setKeyState(BTN_A, (currentState & A) == A ? 1 : 0, EV_KEY);
        gamepad->setKeyState(BTN_B, (currentState & B) == B ? 1 : 0, EV_KEY);
        gamepad->setKeyState(BTN_C, (currentState & C) == C ? 1 : 0, EV_KEY);
        gamepad->setKeyState(BTN_X, (currentState & X) == X ? 1 : 0, EV_KEY);
        gamepad->setKeyState(BTN_Y, (currentState & Y) == Y ? 1 : 0, EV_KEY);
        gamepad->setKeyState(BTN_Z, (currentState & Z) == Z ? 1 : 0, EV_KEY);
        gamepad->setKeyState(BTN_START, (currentState & START) == START ? 1 : 0, EV_KEY);
        gamepad->setKeyState(BTN_MODE, (currentState & MODE) == MODE ? 1 : 0, EV_KEY);

        gamepad->sync();
    }
    lastState = currentState;
}
