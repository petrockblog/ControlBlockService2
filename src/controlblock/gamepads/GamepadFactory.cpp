#include <iostream>
#include "GamepadFactory.h"
#include "ArcadeGamepad.h"
#include "SNESGamepad.h"
#include "NESGamepad.h"
#include "MAMEGamepad.h"
#include "GenesisGamepad.h"
#include "NONEGamepad.h"

GamepadFactory::GamepadFactory(IUInputFactory& uiFactoryRef) :
        uiFactory(uiFactoryRef)
{
}

InputDevice* GamepadFactory::createGamepad(InputDevice::GamepadType_e gamepadType, IDigitalIO& digitalIO)
{
    switch (gamepadType)
    {
    case InputDevice::GAMEPAD_ARCADE:
        return new ArcadeGamepad(uiFactory, digitalIO);
    case InputDevice::GAMEPAD_SNES:
        return new SNESGamepad(uiFactory, digitalIO);
    case InputDevice::GAMEPAD_NES:
        return new NESGamepad(uiFactory, digitalIO);
    case InputDevice::GAMEPAD_MAME:
        return new MAMEGamepad(uiFactory, digitalIO);
    case InputDevice::GAMEPAD_GENESIS:
        return new GenesisGamepad(uiFactory, digitalIO);
    case InputDevice::GAMEPAD_NONE:
        return new NONEGamepad();
    default:
        std::cout << "GamepadFactory: Error while configuring gamepad type ..." << std::endl;
        throw 1;
    }
}