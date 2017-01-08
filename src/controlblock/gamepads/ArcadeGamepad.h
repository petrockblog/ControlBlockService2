#ifndef ARCADEGAMEPAD_H
#define ARCADEGAMEPAD_H

#include "InputDevice.h"
#include "hal/DigitalIn.h"
#include "uinput/UInputGamepadArcade.h"

class ArcadeGamepad: public InputDevice
{
public:
    ArcadeGamepad();
    ~ArcadeGamepad();

    virtual void initialize(InputDevice::Channel_e channel);
    virtual void update();

private:
    InputDevice::Channel_e channel;
    UInputGamepadArcade gamepad;
};

#endif
