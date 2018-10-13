/**
 * (c) Copyright 2017  Florian Mueller (contact@petrockblock.com)
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

#include <stdlib.h>
#include <iostream>
#include "PowerSwitch.h"

PowerSwitch::PowerSwitch(IDigitalIO& digitalIOReference, ShutdownActivated_e doShutdownValue) :
        doShutdown(doShutdownValue),
        isShutdownInitiatedValue(false),
        digitalIO(digitalIOReference)
{
    digitalIO.configureDevice(IDigitalIO::DIO_DEVICE_POWERSWITCH);
    setPowerSignal(PowerSwitch::STATE_ON);

#ifndef NDEBUG
    std::cout << "Created PowerSwitch. doShutdown: " << doShutdownValue << std::endl;
#endif
}

void PowerSwitch::update()
{
    if ((doShutdown == SHUTDOWN_ACTIVATED) && (getShutdownSignal() == SHUTDOWN_TRUE)
            && (!isShutdownInitiatedValue)) {
        system("/etc/controlblockswitchoff.sh &");
        isShutdownInitiatedValue = true;
    }
}

bool PowerSwitch::isShutdownInitiated() const
{
    return isShutdownInitiatedValue;
}

void PowerSwitch::setPowerSignal(PowerState_e state)
{
    if (state == STATE_OFF) {
        digitalIO.setLevel(IDigitalIO::DIO_CHANNEL_TOPOWERSWITCH, IDigitalIO::DIO_LEVEL_LOW);
    }
    else {
        digitalIO.setLevel(IDigitalIO::DIO_CHANNEL_TOPOWERSWITCH, IDigitalIO::DIO_LEVEL_HIGH);
    }
}

PowerSwitch::ShutdownSignal_e PowerSwitch::getShutdownSignal()
{
    ShutdownSignal_e signal;
    if (digitalIO.getLevel(IDigitalIO::DIO_CHANNEL_FROMPOWERSWITCH) == IDigitalIO::DIO_LEVEL_LOW) {
        signal = SHUTDOWN_FALSE;
    }
    else {
        signal = SHUTDOWN_TRUE;
    }
    return signal;
}
