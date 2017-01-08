#ifndef MAMEGAMEPAD_H
#define MAMEGAMEPAD_H

#include <stdint.h>
#include "InputDevice.h"
#include "hal/DigitalIn.h"
#include "uinput/UInputKeyboard.h"

class MAMEGamepad: public InputDevice
{
public:
    MAMEGamepad();
    ~MAMEGamepad();

    virtual void initialize(InputDevice::Channel_e channel);
    virtual void update();

private:
    InputDevice::Channel_e channel;
    UInputKeyboard keyboard;
};

#endif
