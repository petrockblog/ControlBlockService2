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

#include "hal/IDigitalOut.h"
#include "hal/IDigitalIn.h"

class PowerSwitch
{
public:
    /**
     * Power state identifiers
     */
    enum PowerState_e
    {
        STATE_OFF = 0,
        STATE_ON
    };

    enum ShutdownSignal_e
    {
        SHUTDOWN_FALSE = 0,
        SHUTDOWN_TRUE
    };

    enum ShutdownActivated_e
    {
        SHUTDOWN_DEACTIVATED = 0,
        SHUTDOWN_ACTIVATED
    };

    explicit PowerSwitch(IDigitalIn& digitalInReference, IDigitalOut& digitalOutReference, ShutdownActivated_e doShutdownValue);

    ~PowerSwitch();

    void update();
    bool isShutdownInitiated() const;

private:
    ShutdownActivated_e doShutdown;
    bool isShutdownInitiatedValue;

    IDigitalIn& digitalIn;
    IDigitalOut& digitalOut;

    void setPowerSignal(PowerState_e state);
    ShutdownSignal_e getShutdownSignal();

};

#endif // POWERSWITCH_H
