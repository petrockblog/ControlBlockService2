#include "UInputFactory.h"

#include "UInputGamepadArcade.h"
#include "UInputKeyboard.h"
#include "UInputGamepadSNES.h"

IUInputDevice* UInputFactory::getUInputDevice(IUInputDevice::DeviceType type)
{
    IUInputDevice* newInstance;
    switch (type)
    {
        case IUInputDevice::TYPE_GAMEPAD_ARCADE: newInstance = new UInputGamepadArcade(); break;
        case IUInputDevice::TYPE_GAMEPAD_SNES: newInstance = new UInputGamepadSNES(); break;
        case IUInputDevice::TYPE_KEYVBOARD: newInstance = new UInputKeyboard(); break;
    }
    return newInstance;
}
