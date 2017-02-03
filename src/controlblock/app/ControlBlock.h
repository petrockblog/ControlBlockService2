/**
 * (c) Copyright 2017  Florian Müller (contact@petrockblock.com)
 * https://github.com/petrockblog/ControlBlock2
 *
 * Permission to use, copy, modify and distribute the program in both binary and
 * source form, for non-commercial purposes, is hereby granted without fee,
 * providing that this license information and copyright notice appear with
 * all copies and any derived work.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event shall the authors be held liable for any damages
 * arising from the use of this software.
 *
 * This program is freeware for PERSONAL USE only. Commercial users must
 * seek permission of the copyright holders first. Commercial use includes
 * charging money for the program or software derived from the program.
 *
 * The copyright holders request that bug fixes and improvements to the code
 * should be forwarded to them so everyone can benefit from the modifications
 * in future versions.
 */

#ifndef CONTROLBLOCK_H
#define CONTROLBLOCK_H

#include <stdint.h>
#include <iostream>
#include <config/IControlBlockConfiguration.h>

#include "PowerSwitch.h"
#include "gamepads/IGamepadFactory.h"
#include "uinput/IUInputFactory.h"
#include "hal/IDigitalIn.h"
#include "hal/IDigitalOut.h"

/**
 * This class models the functionalities of the ControlBlock
 */
class ControlBlock
{
public:
    /**
     * Constructor
     * @param uiFactoryRef - Reference with UInputFactory interface
     * @param digitalInRef - Reference with IDigitalIn interface
     * @param digitalOutRef - Reference with IDigitalOut interface
     * @param configRef - Reference with IControlBlockConfiguration interface
     * @param gamepadFactory
     */
    ControlBlock(IUInputFactory& uiFactoryRef, IDigitalIn& digitalInRef, IDigitalOut& digitalOutRef,
            IControlBlockConfiguration& configRef, IGamepadFactory& gamepadFactory);

    /**
     * Destructor
     */
    ~ControlBlock();

    ControlBlock(const ControlBlock& other) = delete;
    ControlBlock& operator=(const ControlBlock&) = delete;

    /**
     * Updates the state of every configured gamepad and of the power switch
     */
    void update();

private:
    static const uint8_t MAX_NUMBER_OF_CONTROLBLOCKS = 2u;
    static const uint8_t MAX_NUMBER_OF_INPUTDEVICES = 2u * MAX_NUMBER_OF_CONTROLBLOCKS;

    uint8_t m_numberOfGamepads;
    PowerSwitch* powerSwitch;
    std::unique_ptr<InputDevice> gamepads[MAX_NUMBER_OF_CONTROLBLOCKS];
    InputDevice::Channel_e getInputDeviceChannel(int counterValue);

};

#endif // CONTROLBLOCK_H
