#ifndef ARCADEGAMEPAD_H
#define ARCADEGAMEPAD_H

#include <memory>
#include "InputDevice.h"
#include "uinput/IUInputDevice.h"
#include "uinput/IUInputFactory.h"
#include "hal/IDigitalIn.h"

class ArcadeGamepad: public InputDevice
{
public:
    ArcadeGamepad(IUInputFactory& uiFactory, IDigitalIn& digitalInRef);
    ~ArcadeGamepad() = default;

    virtual void initialize(InputDevice::Channel_e channel);
    virtual void update();

private:
    InputDevice::Channel_e channel;
    std::unique_ptr<IUInputDevice> gamepad;
    IDigitalIn& digitalIn;
};

#endif
