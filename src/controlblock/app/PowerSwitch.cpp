#include <stdlib.h>
#include <iostream>
#include "PowerSwitch.h"

PowerSwitch::PowerSwitch(IDigitalIn& digitalInReference, IDigitalOut& digitalOutReference, ShutdownActivated_e doShutdownValue)
        :
        doShutdown(doShutdownValue),
        isShutdownInitiatedValue(false),
        digitalIn(digitalInReference),
        digitalOut(digitalOutReference)
{
    digitalOut.configureDevice(IDigitalOut::DO_DEVICE_POWERSWITCH);
    digitalIn.configureDevice(IDigitalIn::DI_DEVICE_POWERSWITCH);
    setPowerSignal(PowerSwitch::STATE_ON);

#ifndef NDEBUG
    std::cout << "Created PowerSwitch. doShutdown: " << doShutdownValue << std::endl;
#endif
}

PowerSwitch::~PowerSwitch()
{
}

void PowerSwitch::update()
{
    if ((doShutdown==SHUTDOWN_ACTIVATED) && (getShutdownSignal()==SHUTDOWN_TRUE)
            && (isShutdownInitiatedValue==false)) {
        system("/etc/controlblockswitchoff.sh");
        isShutdownInitiatedValue = true;
    }
}

bool PowerSwitch::isShutdownInitiated() const
{
    return isShutdownInitiatedValue;
}

void PowerSwitch::setPowerSignal(PowerState_e state)
{
    if (state==STATE_OFF) {
        digitalOut.setLevel(IDigitalOut::DO_CHANNEL_TOPOWERSWITCH, IDigitalOut::DO_LEVEL_LOW);
    }
    else {
        digitalOut.setLevel(IDigitalOut::DO_CHANNEL_TOPOWERSWITCH, IDigitalOut::DO_LEVEL_HIGH);
    }
}

PowerSwitch::ShutdownSignal_e PowerSwitch::getShutdownSignal()
{
    ShutdownSignal_e signal = SHUTDOWN_FALSE;
    if (digitalIn.getLevel(IDigitalIn::DI_CHANNEL_FROMPOWERSWITCH)==IDigitalIn::DI_LEVEL_LOW) {
        signal = SHUTDOWN_FALSE;
    }
    else {
        signal = SHUTDOWN_TRUE;
    }
    return signal;
}
