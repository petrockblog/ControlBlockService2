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

#ifndef SINGLECONFIGURATION_H
#define SINGLECONFIGURATION_H

#include <string>
#include "gamepads/InputDevice.h"

/**
 * Instances of this class represent the configuration of a single ControlBlock
 */
class SingleConfiguration
{
public:
    /**
     * Constructor
     * @param enabled - The enable status
     * @param address - The hardware address
     * @param type - The type of the gamepad
     * @param pwrSwitch - Whether the power switch functionality is enabled (=true) or not (=false)
     * @param momentSwitch - Whether the power switch is momentary (=true) or latching (=false)
     * @param oneGp - Whether one (=true) or two (=false) gamepads should be registered
     */
    SingleConfiguration(bool enabled, uint8_t address, std::string type, bool pwrSwitch, bool momentSwitch, bool oneGp);

    /**
     * Destructor
     */
    virtual ~SingleConfiguration();

    /**
     * Returns whether the ControlBlock is enabled or not
     * @return
     *  - true, if the ControlBlock is enabled,
     *  - false, otherwise.
     */
    virtual bool isEnabled();

    /**
     * Returns the device address of the ControlBlock
     * @return The address of the ControlBlock
     */
    virtual uint8_t getDeviceAddress();

    /**
     * Returns the type of gamepad
     * @return The type of gamepad
     */
    virtual InputDevice::GamepadType_e getGamepadType();

    /**
     * Returns whether the power switch functionality is enabled or not
     * @return
     *  - true, if the power switch functionality is enabled,
     *  - false, otherwise.
     */
    virtual bool isPowerSwitchEnabled();

    /**
     * Returns whether the power switch is momentary or not
     * @return
     *  - true, if the power switch is momentary,
     *  - false, if the power switch is latching.
     */
    virtual bool isPowerSwitchMomentary();

    /**
     * Returns whether only one gamepad should be enabled or not
     * @return
     *  - true, if only one gamepad should be enabled,
     *  - false, otherwise.
     */
    virtual bool isOnlyOneGamepadEnabled();

private:
    bool isEnabledValue;
    uint8_t deviceAddress;
    InputDevice::GamepadType_e padType;
    bool isPowerSwitchEnabledValue;
    bool isPowerSwitchMomentaryValue;
    bool isOnlyOneGamepadEnabledValue;
};

#endif
