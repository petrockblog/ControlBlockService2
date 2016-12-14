#ifndef CONTROLBLOCK_H
#define CONTROLBLOCK_H

#include <stdint.h>
#include <iostream>
#include "PowerSwitch.h"
#include "InputDevice.h"
#include "ISingleConfiguration.h"

class ControlBlock
{
public:
    ControlBlock();
    ~ControlBlock();

    ControlBlock(const ControlBlock& other) = delete;
    ControlBlock& operator=(const ControlBlock&) = delete;

    void update();

private:
    static const uint8_t MAX_NUMBER_OF_CONTROLBLOCKS = 2u;

    uint8_t m_numberOfGamepads;

    PowerSwitch* powerSwitch;
    InputDevice* gamepads[MAX_NUMBER_OF_CONTROLBLOCKS];

    InputDevice::Channel_e getInputDevice(int counterValue);
    void createGamepad(ISingleConfiguration::GamepadType_e type, InputDevice*& device);

};

#endif // CONTROLBLOCK_H
