#include "ControlBlock.h"

#include "ArcadeGamepad.h"
#include "SNESGamepad.h"
#include "MAMEGamepad.h"
#include "NONEGamepad.h"

ControlBlock::ControlBlock() :
                configuration(new ControlBlockConfiguration())
{
    // read configuration
    configuration->initialize();

    // initialize the power switch
    if (configuration->getShutdownActivation() == ControlBlockConfiguration::SHUTDOWN_ACTIVATED)
    {
        powerSwitch = new PowerSwitch(PowerSwitch::SHUTDOWN_ACTIVATED);
    }
    else
    {
        powerSwitch = new PowerSwitch(PowerSwitch::SHUTDOWN_DEACTIVATED);
    }

    // initialize the controllers
    for (uint8_t counter = 0u; counter < NUMGAMEPADS; counter++)
    {
        if (configuration->getGamepadType() == ControlBlockConfiguration::GAMEPAD_ARCADE)
        {
            gamepads[counter] = new ArcadeGamepad();
        }
        else if (configuration->getGamepadType() == ControlBlockConfiguration::GAMEPAD_SNES)
        {
            gamepads[counter] = new SNESGamepad();
        }
        else if (configuration->getGamepadType() == ControlBlockConfiguration::GAMEPAD_MAME)
        {
            gamepads[counter] = new MAMEGamepad();
        }
        else if (configuration->getGamepadType() == ControlBlockConfiguration::GAMEPAD_NONE)
        {
            gamepads[counter] = new NONEGamepad();
        }
        else
        {
            std::cout << "Error while configuring gamepad type ..." << std::endl;
            throw 1;
        }
        gamepads[counter]->initialize(counter == 0u ? InputDevice::CHANNEL_1 : InputDevice::CHANNEL_2);
    }
}

ControlBlock::~ControlBlock()
{
    for (uint8_t counter = 0u; counter < NUMGAMEPADS; counter++)
    {
        delete gamepads[counter];
        gamepads[counter] = NULL;
    }
    delete powerSwitch;
    delete configuration;
}

void ControlBlock::update()
{
    try
    {
        for (uint8_t counter = 0u; counter < NUMGAMEPADS; counter++)
        {
            gamepads[counter]->update();
        }
    }
    catch (int errno)
    {
        std::cout << "Error while updating the gamepad devices. Error number: " << errno << std::endl;
    }
    try
    {
        powerSwitch->update();
    }
    catch (int errno)
    {
        std::cout << "Error while updating the power switch instance. Error number: " << errno << std::endl;
    }
}
