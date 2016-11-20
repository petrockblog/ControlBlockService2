#ifndef CONTROLBLOCKCONFIGURATION_H
#define CONTROLBLOCKCONFIGURATION_H

#include <json/json.h>

class ControlBlockConfiguration {
public:
	enum GamepadType_e {
		GAMEPAD_ARCADE = 0,
		GAMEPAD_MAME,
		GAMEPAD_SNES,
		GAMEPAD_NONE
	};

	enum ShutdownType_e {
		SHUTDOWN_DEACTIVATED = 0,
		SHUTDOWN_ACTIVATED
	};

	ControlBlockConfiguration();
	~ControlBlockConfiguration();
	
	void initialize();
	GamepadType_e getGamepadType() const;
	ShutdownType_e getShutdownActivation() const;

private:
	GamepadType_e gamepadType;
	ShutdownType_e doShutdown;

};

#endif
