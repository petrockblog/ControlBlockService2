#ifndef NONEGAMEPAD_H
#define NONEGAMEPAD_H

#include <stdint.h>
#include "InputDevice.h"
#include "hal/DigitalIn.h"

class NONEGamepad : public InputDevice {
public:
	NONEGamepad();
	~NONEGamepad();

	virtual void initialize(InputDevice::Channel_e channel);
	virtual void update();

};

#endif
