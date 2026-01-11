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

#include <memory>
#include <optional>
#include <gpiod.hpp>
#include "hal/IDigitalIO.h"

// Detect libgpiod version at compile time
// libgpiod v2.x uses gpiod::chip::prepare_request() which doesn't exist in v1.x
// v1.x uses gpiod::chip::get_line() with line_request struct
// The most reliable check is for GPIOD_API_VERSION which is defined in libgpiod v2.x
#if __has_include(<gpiod.h>)
    #include <gpiod.h>
    #if defined(GPIOD_API_VERSION) && GPIOD_API_VERSION >= 0x00020000
        #define GPIOD_VERSION_2X
    #endif
#endif

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

#ifdef GPIOD_VERSION_2X
    // libgpiod v2.x API
    std::unique_ptr<::gpiod::chip> chip_;
    std::optional<::gpiod::line_request> powerSwitchIn_port_;
    std::optional<::gpiod::line_request> powerSwitchOut_port_;
#else
    // libgpiod v1.x API
    std::unique_ptr<::gpiod::chip> chip_;
    std::shared_ptr<::gpiod::line> powerSwitchIn_port_;
    std::shared_ptr<::gpiod::line> powerSwitchOut_port_;
#endif

    void setPowerSignal(PowerState state);
    ShutdownSignal getShutdownSignal();
    bool isRPi5();

};

#endif // POWERSWITCH_H
