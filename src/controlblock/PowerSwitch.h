#ifndef POWERSWITCH_H
#define POWERSWITCH_H

#include "DigitalOut.h"
#include "DigitalIn.h"

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

    explicit PowerSwitch(ShutdownActivated_e doShutdownValue);

    ~PowerSwitch();

    void update();

private:
    ShutdownActivated_e doShutdown;

    void setPowerSignal(PowerState_e state);
    ShutdownSignal_e getShutdownSignal();

};

#endif // POWERSWITCH_H
