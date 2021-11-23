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

#include <gpiod.hpp>
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
    enum class PowerState
    {
        OFF,  //!< Power state is off
        ON    //!< Power state is on
    };

    /**
     * Shutdown signal identifiers
     */
    enum class ShutdownSignal
    {
        DEACTIVATED,  //!< Shutdown signal is not set
        ACTIVATED     //!< Shutdown signal is set
    };

    /**
     * Indicates whether the power switch functionality is enabled or not
     */
    enum class ShutdownActivated
    {
        DEACTIVATED, //!< Power switch is disabled
        ACTIVATED    //!< Power switch is enabled
    };

    /**
     * Constructor
     * @param digitalInReference - Reference with IDigitalIn interface
     * @param digitalOutReference - Reference with IDigitalOut interface
     * @param doShutdownValue - Power switch function is enabled or not
     */
    explicit PowerSwitch(IDigitalIO& digitalIOReference, ShutdownActivated doShutdownValue);

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
    ShutdownActivated doShutdown;
    bool isShutdownInitiatedValue;
    IDigitalIO& digitalIO;
    std::shared_ptr<::gpiod::line> powerSwitchIn_port_;
    std::shared_ptr<::gpiod::line> powerSwitchOut_port_;

    void setPowerSignal(PowerState state);
    ShutdownSignal getShutdownSignal();

};

#endif // POWERSWITCH_H
