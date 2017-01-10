#ifndef CONTROLBLOCKSERVICE2_IUINPUTDEVICE_H
#define CONTROLBLOCKSERVICE2_IUINPUTDEVICE_H

#include "UInputEventCodes.h"

class IUInputDevice {
public:
    enum DeviceType
    {
      TYPE_GAMEPAD_ARCADE = 0,
      TYPE_GAMEPAD_SNES,
      TYPE_KEYVBOARD
    };

    /**
     * Constructor
     */
    IUInputDevice() = default;

    /**
     * Destructor
     */
    virtual ~IUInputDevice() =  default;

    /**
     * Sets the state of a key. To let the changes have an effect the method \ref sync() needs to be called.
     * @param keycode - The keycode
     * @param keyvalue
     * @param evtype
     */
    virtual void setKeyState(uint16_t keycode, int16_t keyvalue, uint16_t evtype) = 0;

    /**
     * Sends all recent key state changes via \ref setKeyState() to the uinput device.
     */
    virtual void sync() = 0;
};

#endif //CONTROLBLOCKSERVICE2_IUINPUTDEVICE_H
