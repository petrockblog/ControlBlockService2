#ifndef POWERSWITCH_H
#define POWERSWITCH_H

#include "DigitalOut.h"
#include "DigitalIn.h"

class PowerSwitch {
public:
	typedef enum {
	    STATE_OFF = 0,
	    STATE_ON
	} PowerState_e;

	typedef enum {
	    SHUTDOWN_FALSE = 0,
	    SHUTDOWN_TRUE
	} ShutdownSignal_e;

	typedef enum {
		SHUTDOWN_DEACTIVATED = 0,
		SHUTDOWN_ACTIVATED
	} ShutdownActivated_e;

	PowerSwitch(ShutdownActivated_e doShutdownValue);
	~PowerSwitch();

	void update();

private:
	ShutdownActivated_e doShutdown;

	void setPowerSignal(PowerState_e state);
	ShutdownSignal_e getShutdownSignal();

};

#endif // POWERSWITCH_H
