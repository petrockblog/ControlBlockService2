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

#ifndef POWERSWITCH_H
#define POWERSWITCH_H

#include "hal/IDigitalIO.h"

/**
 * This class models the power switch functionalities of the ControlBlock.
 */
class PowerSwitch
{
public:
    /**
     * Power state identifiers
     */
    enum PowerState_e
    {
        STATE_OFF = 0,  //!< Power state is off
        STATE_ON        //!< Power state is on
    };

    /**
     * Power switch button status
     */
    enum PowerSwitchStatus_e
    {
        POWERSWITCH_PRESSED = 0,  //!< The power switch button is pressed
        POWERSWITCH_UNPRESSED     //!< The power switch button is not pressed
    };

    /**
     * Indicates whether the power switch functionality is enabled or not
     */
    enum PowerSwitchEnabled_e
    {
        POWERSWITCH_DISABLED = 0, //!< Power switch is disabled
        POWERSWITCH_ENABLED       //!< Power switch is enabled
    };

    /***
     * Indicates what type of power switch that is used
     */
    enum PowerSwitchType_e
    {
        SWITCHTYPE_MOMENTARY = 0, //!< Power switch is a momentary switch
        SWITCHTYPE_LATCHING       //!< Power switch is a latching switch
    };

    /**
     * Constructor
     * @param digitalInReference - Reference with IDigitalIn interface
     * @param digitalOutReference - Reference with IDigitalOut interface
     * @param powerSwitchEnabledValue - Power switch function is enabled or not
     * @param powerSwitchTypeValue - Type of power switch used
     */
    explicit PowerSwitch(IDigitalIO& digitalIOReference, PowerSwitchEnabled_e powerSwitchEnabledValue, PowerSwitchType_e powerSwitchTypeValue);

    /**
     * Destructor
     */
    ~PowerSwitch() = default;

    /**
     * Checks the shutdown signal. If the signal is logical high then the switch-off script
     * is executed.
     */
    void update();

    /**
     * Returns the information whether the switch-off script was called or not.
     * @return
     *  - true, if the switch-off script was called,
     *  - false, otherwise.
     */
    bool isShutdownInitiated() const;

private:
    PowerSwitchEnabled_e powerSwitchEnabled;
    PowerSwitchType_e powerSwitchType;
    bool isShutdownInitiatedValue;
    IDigitalIO& digitalIO;

    void setPowerState(PowerState_e state);
    PowerSwitchStatus_e getPowerSwitchStatus();

};

#endif // POWERSWITCH_H
