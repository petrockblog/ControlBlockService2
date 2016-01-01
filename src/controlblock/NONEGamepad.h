#ifndef NONEGAMEPAD_H
#define NONEGAMEPAD_H

#include <stdint.h>
#include <linux/uinput.h>
#include "InputDevice.h"
#include "DigitalIn.h"
#include "uinputcpp.h"

class NONEGamepad : public InputDevice {
public:
	NONEGamepad();
	~NONEGamepad();

	virtual void initialize(InputDevice::Channel_e channel);
	virtual void update();

};

#endif