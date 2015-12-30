#ifndef DIGITALOUT_H
#define DIGITALOUT_H

#include "bcm2835.h"
#include <stdint.h>
#include "HALFactory.h"

class DigitalOut
{
public:
    typedef enum
    {
        DO_CHANNEL_TOPOWERSWITCH = 0,
        DO_CHANNEL_P1_STROBE,
        DO_CHANNEL_P1_CLOCK,
        DO_CHANNEL_P1_VCC,
        DO_CHANNEL_P2_STROBE,
        DO_CHANNEL_P2_CLOCK,
        DO_CHANNEL_P2_VCC,
    } DO_Channel_e;

    typedef enum
    {
        DO_LEVEL_LOW = 0,
        DO_LEVEL_HIGH
    } DO_Level_e;

    enum DO_Device
    {
        DO_DEVICE_POWERSWITCH = 0,
        DO_DEVICE_SNES
    };

    ~DigitalOut();

    static DigitalOut& getInstance()
    {
        static DigitalOut digitalOut = DigitalOut();
        return digitalOut;
    }

    void configureDevice(DO_Device device);
    void setLevel(DO_Channel_e channel, DO_Level_e level);

private:
    MCP23S17PI* expander[2];

    DigitalOut();  // hide default constructor

};

#endif // DIGITALOUT_H
