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
#include "hal/DigitalIO.h"

ControlBlock::ControlBlock(IUInputFactory& uiFactoryRef, IControlBlockConfiguration& configRef, IGamepadFactory& gamepadFactory) :
        m_numberOfGamepads(0u),
        powerSwitch(NULL)
{
    configRef.loadConfiguration();

    // initialize the controllers
    auto counter = 0;
    for (auto index = 0; index < MAX_NUMBER_OF_CONTROLBLOCKS; index++) 
    {
        if (configRef.getConfiguration(index).isEnabled()) 
        {
            // initialize MCP23S17 and DigitalIO instances
            const uint8_t address = configRef.getConfiguration(index).getDeviceAddress();
            const uint8_t mcpIndex1 = index * 2;
            const uint8_t mcpIndex2 = (index * 2) + 1;
            mcp23s17[mcpIndex1] = new MCP23S17PI(MCP23S17PI::CHIPSELECT_0, address);
            mcp23s17[mcpIndex2] = new MCP23S17PI(MCP23S17PI::CHIPSELECT_0, (address | 0x01));
            digitalIO[index] = new DigitalIO(*mcp23s17[mcpIndex1], *mcp23s17[mcpIndex2]);

            // configure GPIOs according to the gamepad type
            const InputDevice::GamepadType_e type = configRef.getConfiguration(index).getGamepadType();
            configureDevice(digitalIO[index], type);

            // create gamepad instances
            gamepads[counter] = gamepadFactory.createGamepad(type, *digitalIO[index]);
            InputDevice::Channel_e channel = getInputDeviceChannel(counter);
            gamepads[counter]->initialize(channel);
            counter++;
            if (!configRef.getConfiguration(index).isOnlyOneGamepadEnabled())
            {
                gamepads[counter] = gamepadFactory.createGamepad(type, *digitalIO[index]);
                InputDevice::Channel_e channel = getInputDeviceChannel(counter);
                gamepads[counter]->initialize(channel);
                counter++;
            }
        }
    }
    m_numberOfGamepads = counter;

    // initialize the power switch
    if (configRef.getConfiguration(0).isEnabled() && configRef.getConfiguration(0).isPowerSwitchEnabled()) {
        powerSwitch = new PowerSwitch(*digitalIO[0], PowerSwitch::SHUTDOWN_ACTIVATED);
    }
}

ControlBlock::~ControlBlock()
{
    if (powerSwitch != NULL)
    {
        delete powerSwitch;
    }

    for (auto mcp : mcp23s17)
    {
        if (mcp != NULL)
        {
            delete mcp;
        }
    }
    for (auto digIO : digitalIO)
    {
        if (digIO != NULL)
        {
            delete digIO;
        }
    }
    for (auto pad : gamepads)
    {
        if (pad != NULL)
        {
            delete pad;
        }
    }
}

void ControlBlock::update()
{
    try {
        for (int counter = 0; counter < m_numberOfGamepads; counter++) {
            gamepads[counter]->update();
        }
    }
    catch (int errno) {
        std::cout << "ControlBlock.cpp: Error while updating the gamepad devices. Error number: " << errno << std::endl;
    }

    try {
        if (powerSwitch != NULL)
        {
            powerSwitch->update();
        }
    }
    catch (int errno) {
        std::cout << "ControlBlock.cpp: Error while updating the power switch instance. Error number: " << errno << std::endl;
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
        std::cout << "ControlBlock.cpp: Unknown counter value" << std::endl;
        throw 1;
    }
    return channel;
}

void ControlBlock::configureDevice(IDigitalIO* digitalIO, InputDevice::GamepadType_e type)
{
    assert(digitalIO != NULL);

    switch (type)
    {
        case InputDevice::GAMEPAD_ARCADE:
            digitalIO->configureDevice(IDigitalIO::DIO_DEVICE_ALLIN);
            break;
        case InputDevice::GAMEPAD_MAME:
            digitalIO->configureDevice(IDigitalIO::DIO_DEVICE_SNES);
            break;
        case InputDevice::GAMEPAD_SNES:
            digitalIO->configureDevice(IDigitalIO::DIO_DEVICE_SNES);
            break;
        case InputDevice::GAMEPAD_NES:
            digitalIO->configureDevice(IDigitalIO::DIO_DEVICE_SNES);
            break;
        case InputDevice::GAMEPAD_GENESIS:
            digitalIO->configureDevice(IDigitalIO::DIO_DEVICE_GENESIS);
            break;
        case InputDevice::GAMEPAD_NONE:
            // do nothing
            break;
        default:
            std::cout << "ControlBlock.cpp: Unknown type" << std::endl;
            throw 1;
    }
    
}
