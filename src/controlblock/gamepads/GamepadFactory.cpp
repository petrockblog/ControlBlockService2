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

std::unique_ptr<InputDevice> GamepadFactory::createGamepad(InputDevice::GamepadType_e gamepadType)
{
    std::cout << "Creating gamepad of type " << gamepadType << std::endl;
    switch (gamepadType) {
    case InputDevice::GAMEPAD_ARCADE:
        return std::unique_ptr<InputDevice>(new ArcadeGamepad(*uiFactory, *digitalIn));
    case InputDevice::GAMEPAD_SNES:
        return std::unique_ptr<InputDevice>(new SNESGamepad(*uiFactory, *digitalIn, *digitalOut));
    case InputDevice::GAMEPAD_MAME:
        return std::unique_ptr<InputDevice>(new MAMEGamepad(*uiFactory, *digitalIn));
    case InputDevice::GAMEPAD_GENESIS:
        return std::unique_ptr<InputDevice>(new GenesisGamepad(*uiFactory, *digitalIn, *digitalOut));
    case InputDevice::GAMEPAD_NONE:
        return std::unique_ptr<InputDevice>(new NONEGamepad());
    default:
        std::cout << "Error while configuring gamepad type ..." << std::endl;
        throw 1;
    }
}