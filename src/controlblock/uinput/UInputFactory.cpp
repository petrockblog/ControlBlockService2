#include "UInputFactory.h"

#include "UInputGamepadArcade.h"
#include "UInputKeyboard.h"
#include "UInputGamepadSNES.h"

std::unique_ptr<IUInputDevice> UInputFactory::getUInputDevice(IUInputDevice::DeviceType type)
{
    switch (type) {
    case IUInputDevice::TYPE_GAMEPAD_ARCADE:
        return std::unique_ptr<IUInputDevice>(new UInputGamepadArcade());
    case IUInputDevice::TYPE_GAMEPAD_SNES:
        return std::unique_ptr<IUInputDevice>(new UInputGamepadSNES());
    case IUInputDevice::TYPE_KEYVBOARD:
        return std::unique_ptr<IUInputDevice>(new UInputKeyboard());
    }
}
