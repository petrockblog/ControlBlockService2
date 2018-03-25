#include <iostream>
#include "GamepadFactory.h"
#include "ArcadeGamepad.h"
#include "SNESGamepad.h"
#include "MAMEGamepad.h"
#include "GenesisGamepad.h"
#include "NONEGamepad.h"

GamepadFactory::GamepadFactory(IUInputFactory& uiFactoryRef, IDigitalIn& digitalInRef, IDigitalOut& digitalOutRef) :
        uiFactory(&uiFactoryRef),
        digitalIn(&digitalInRef),
        digitalOut(&digitalOutRef)
{
}

InputDevice* GamepadFactory::createGamepad(InputDevice::GamepadType_e gamepadType)
{
#ifndef NDEBUG
    std::cout << "Creating gamepad of type " << gamepadType << std::endl;
#endif
    switch (gamepadType)
    {
    case InputDevice::GAMEPAD_ARCADE:
        return new ArcadeGamepad(*uiFactory, *digitalIn);
    case InputDevice::GAMEPAD_SNES:
        return new SNESGamepad(*uiFactory, *digitalIn, *digitalOut);
    case InputDevice::GAMEPAD_MAME:
        return new MAMEGamepad(*uiFactory, *digitalIn);
    case InputDevice::GAMEPAD_GENESIS:
        return new GenesisGamepad(*uiFactory, *digitalIn, *digitalOut);
    case InputDevice::GAMEPAD_NONE:
        return new NONEGamepad();
    default:
        std::cout << "Error while configuring gamepad type ..." << std::endl;
        throw 1;
    }
}