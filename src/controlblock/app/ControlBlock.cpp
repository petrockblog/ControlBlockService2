/**
 * (c) Copyright 2017  Florian Mueller (contact@petrockblock.com)
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

#include <assert.h>

#include "ControlBlock.h"

ControlBlock::ControlBlock(IUInputFactory& uiFactoryRef, IDigitalIn& digitalInRef, IDigitalOut& digitalOutRef,
        IControlBlockConfiguration& configRef, IGamepadFactory& gamepadFactory) :
        m_numberOfGamepads(0u),
        powerSwitch(NULL)
{
    configRef.loadConfiguration();

    // initialize the power switch
    if (configRef.getConfiguration(0).isEnabled() && configRef.getConfiguration(0).isPowerSwitchEnabled()) {
        powerSwitch = new PowerSwitch(digitalInRef, digitalOutRef, PowerSwitch::SHUTDOWN_ACTIVATED);
    }
    else {
        powerSwitch = new PowerSwitch(digitalInRef, digitalOutRef, PowerSwitch::SHUTDOWN_DEACTIVATED);
    }

    // initialize the controllers
    uint8_t counter = 0u;
    for (auto index = 0; index < MAX_NUMBER_OF_CONTROLBLOCKS; index++) {
        if (configRef.getConfiguration(index).isEnabled()) {
            InputDevice::GamepadType_e type = configRef.getConfiguration(index).getGamepadType();
            gamepads[counter] = gamepadFactory.createGamepad(type);
            InputDevice::Channel_e channel = getInputDeviceChannel(counter);
            gamepads[counter]->initialize(channel);
            counter++;
            if (!configRef.getConfiguration(index).isOnlyOneGamepadEnabled()) {
                gamepads[counter] = gamepadFactory.createGamepad(type);
                channel = getInputDeviceChannel(counter);
                gamepads[counter]->initialize(channel);
                counter++;
            }
        }
    }
    m_numberOfGamepads = counter;
}

ControlBlock::~ControlBlock()
{
    delete powerSwitch;
}

void ControlBlock::update()
{
    try {
        for (int counter = 0; counter < m_numberOfGamepads; counter++) {
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

InputDevice::Channel_e ControlBlock::getInputDeviceChannel(int counterValue)
{
    assert(counterValue < (MAX_NUMBER_OF_INPUTDEVICES));

    InputDevice::Channel_e channel;
    switch (counterValue) {
    case 0:channel = InputDevice::CHANNEL_1;
        break;
    case 1:channel = InputDevice::CHANNEL_2;
        break;
    case 2:channel = InputDevice::CHANNEL_3;
        break;
    case 3:channel = InputDevice::CHANNEL_4;
        break;
    default:
        throw 1;
    }
    return channel;
}
