#ifndef CONTROLBLOCKSERVICE2_GAMEPADFACTORY_H
#define CONTROLBLOCKSERVICE2_GAMEPADFACTORY_H

#include <memory>
#include "IGamepadFactory.h"
#include "InputDevice.h"
#include "uinput/IUInputFactory.h"
#include "hal/IDigitalIn.h"
#include "hal/IDigitalOut.h"

class GamepadFactory: public IGamepadFactory
{
public:
    GamepadFactory(IUInputFactory& uiFactoryRef, IDigitalIn& digitalInRef, IDigitalOut& digitalOutRef);
    virtual InputDevice* createGamepad(InputDevice::GamepadType_e gamepadType);

private:
    IUInputFactory* uiFactory;
    IDigitalIn* digitalIn;
    IDigitalOut* digitalOut;

};

#endif //CONTROLBLOCKSERVICE2_GAMEPADFACTORY_H
