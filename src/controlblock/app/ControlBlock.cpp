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

#include "ControlBlock.h"

#include "config/ControlBlockConfiguration.h"
#include "gamepads/ArcadeGamepad.h"
#include "gamepads/SNESGamepad.h"
#include "gamepads/MAMEGamepad.h"
#include "gamepads/NONEGamepad.h"
#include "gamepads/GenesisGamepad.h"

ControlBlock::ControlBlock(IUInputFactory& uiFactoryRef, IDigitalIn& digitalInRef, IDigitalOut& digitalOutRef) :
        m_numberOfGamepads(0u),
        powerSwitch(NULL),
        uiFactory(&uiFactoryRef),
        digitalIn(&digitalInRef),
        digitalOut(&digitalOutRef)
{
    ControlBlockConfiguration& config = ControlBlockConfiguration::getInstance();

    // initialize the power switch
    if (config.getConfiguration(0).isEnabled() && config.getConfiguration(0).isPowerSwitchEnabled()) {
        powerSwitch = new PowerSwitch(*digitalIn, *digitalOut,
                PowerSwitch::SHUTDOWN_ACTIVATED);
    }
    else {
        powerSwitch = new PowerSwitch(*digitalIn, *digitalOut,
                PowerSwitch::SHUTDOWN_DEACTIVATED);
    }

    // initialize the controllers
    int counter = 0;
    for (int index = 0; index<MAX_NUMBER_OF_CONTROLBLOCKS; index++) {
        if (config.getConfiguration(index).isEnabled()) {
            ISingleConfiguration::GamepadType_e type = config.getConfiguration(index).getGamepadType();
            createGamepad(type, gamepads[counter]);
            InputDevice::Channel_e channel = getInputDevice(counter);
            gamepads[counter]->initialize(channel);
            counter++;
            if (!config.getConfiguration(index).isOnlyOneGamepadEnabled()) {
                createGamepad(type, gamepads[counter]);
                InputDevice::Channel_e channel = getInputDevice(counter);
                gamepads[counter]->initialize(channel);
                counter++;
            }
        }
    }
    m_numberOfGamepads = counter;
}

ControlBlock::~ControlBlock()
{
    for (int counter = 0; counter<m_numberOfGamepads; counter++) {
        delete gamepads[counter];
        gamepads[counter] = NULL;
    }
    delete powerSwitch;
}

void ControlBlock::update()
{
    try {
        for (int counter = 0; counter<m_numberOfGamepads; counter++) {
            gamepads[counter]->update();
        }
    }
    catch (int errno) {
        std::cout << "Error while updating the gamepad devices. Error number: " << errno << std::endl;
    }

    try {
        powerSwitch->update();
    }
    catch (int errno) {
        std::cout << "Error while updating the power switch instance. Error number: " << errno << std::endl;
    }
}

InputDevice::Channel_e ControlBlock::getInputDevice(int counterValue)
{
    assert(counterValue<(2*MAX_NUMBER_OF_CONTROLBLOCKS));

    InputDevice::Channel_e channel = InputDevice::CHANNEL_UNDEFINED;
    switch (counterValue) {
    case 0:
        channel = InputDevice::CHANNEL_1;
        break;
    case 1:
        channel = InputDevice::CHANNEL_2;
        break;
    case 2:
        channel = InputDevice::CHANNEL_3;
        break;
    case 3:
        channel = InputDevice::CHANNEL_4;
        break;
    }
    return channel;
}

void ControlBlock::createGamepad(ISingleConfiguration::GamepadType_e type, InputDevice*& device)
{
    std::cout << "Creating gamepad of type " << type << std::endl;
    switch (type) {
    case ISingleConfiguration::GAMEPAD_ARCADE: {

        device = new ArcadeGamepad(*uiFactory, *digitalIn);
    }
        break;
    case ISingleConfiguration::GAMEPAD_SNES:
        device = new SNESGamepad(*uiFactory, *digitalIn, *digitalOut);
        break;
    case ISingleConfiguration::GAMEPAD_MAME:
        device = new MAMEGamepad(*uiFactory, *digitalIn);
        break;
    case ISingleConfiguration::GAMEPAD_GENESIS:
        device = new GenesisGamepad(*uiFactory, *digitalIn, *digitalOut);
        break;
    case ISingleConfiguration::GAMEPAD_NONE:
        device = new NONEGamepad();
        break;
    default:
        std::cout << "Error while configuring gamepad type ..." << std::endl;
        throw 1;
        break;
    }
}

