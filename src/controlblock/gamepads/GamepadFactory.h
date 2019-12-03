#ifndef CONTROLBLOCKSERVICE2_GAMEPADFACTORY_H
#define CONTROLBLOCKSERVICE2_GAMEPADFACTORY_H

#include <memory>
#include "IGamepadFactory.h"
#include "InputDevice.h"
#include "uinput/IUInputFactory.h"
#include "hal/IDigitalIO.h"

class GamepadFactory: public IGamepadFactory
{
public:
    explicit GamepadFactory(IUInputFactory& uiFactoryRef);
    InputDevice* createGamepad(InputDevice::GamepadType_e gamepadType, IDigitalIO& digitalIO) override;

private:
    IUInputFactory& uiFactory;

};

#endif //CONTROLBLOCKSERVICE2_GAMEPADFACTORY_H
