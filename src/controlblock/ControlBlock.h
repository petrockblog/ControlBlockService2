#ifndef CONTROLBLOCK_H
#define CONTROLBLOCK_H

#include <stdint.h>
#include <iostream>
#include "PowerSwitch.h"
#include "InputDevice.h"
 #include "ControlBlockConfiguration.h"

class ControlBlock
{
public:
    static const uint8_t NUMGAMEPADS = 2u;

    ControlBlock();
    ~ControlBlock();

    void initialize();
    void update();

private:
    PowerSwitch* powerSwitch;
    InputDevice* gamepads[NUMGAMEPADS];
    ControlBlockConfiguration* configuration;

};

#endif // CONTROLBLOCK_H
