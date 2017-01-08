#ifndef POWERSWITCH_H
#define POWERSWITCH_H

#include "hal/IDigitalOut.h"
#include "hal/IDigitalIn.h"

class PowerSwitch
{
public:
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
