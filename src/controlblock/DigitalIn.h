#ifndef DIGITALIN_H
#define DIGITALIN_H

#include "bcm2835.h"
#include <stdint.h>
#include "HALFactory.h"

/**
 * @brief Abstracts digital input signals of the application.
 * @details This class abstracts the digital input signals of the application.
 *          This includes GPIO signals as well as the signals that are available
 *          via the two MCP23S17 port expanders.
 */
class DigitalIn
{
public:

    /**
     * Digital input channel identifiers
     */
    enum DI_Channel_e
    {
        DI_CHANNEL_FROMPOWERSWITCH = 0,
        DI_CHANNEL_P1_RIGHT,
        DI_CHANNEL_P1_LEFT,
        DI_CHANNEL_P1_UP,
        DI_CHANNEL_P1_DOWN,
        DI_CHANNEL_P1_SW1,
        DI_CHANNEL_P1_SW2,
        DI_CHANNEL_P1_SW3,
        DI_CHANNEL_P1_SW4,
        DI_CHANNEL_P1_SW5,
        DI_CHANNEL_P1_SW6,
        DI_CHANNEL_P1_SW7,
        DI_CHANNEL_P1_SW8,
        DI_CHANNEL_P1_START,
        DI_CHANNEL_P1_COIN,
        DI_CHANNEL_P1_A,
        DI_CHANNEL_P1_B,
        DI_CHANNEL_P2_RIGHT,
        DI_CHANNEL_P2_LEFT,
        DI_CHANNEL_P2_UP,
        DI_CHANNEL_P2_DOWN,
        DI_CHANNEL_P2_SW1,
        DI_CHANNEL_P2_SW2,
        DI_CHANNEL_P2_SW3,
        DI_CHANNEL_P2_SW4,
        DI_CHANNEL_P2_SW5,
        DI_CHANNEL_P2_SW6,
        DI_CHANNEL_P2_SW7,
        DI_CHANNEL_P2_SW8,
        DI_CHANNEL_P2_START,
        DI_CHANNEL_P2_COIN,
        DI_CHANNEL_P2_A,
        DI_CHANNEL_P2_B,
        DI_CHANNEL_P1_DATA,
        DI_CHANNEL_P2_DATA
    };

    /**
     * Logical input level identifiers
     */
    enum DI_Level_e
    {
        DI_LEVEL_LOW = 0,
        DI_LEVEL_HIGH
    };

    /**
     * Logical device identifiers for default configurations
     */
    enum DI_Device
    {
        DI_DEVICE_ALLIN = 0,   //!< Device with all ports set as input ports
        DI_DEVICE_POWERSWITCH, //!< Powerswitch device
        DI_DEVICE_SNES         //!< SNES controller device
    };

    /**
     * @brief Destructor
     */
    ~DigitalIn();

    /**
     * @brief Returns a singleton instance
     * @return Reference to singleton instance
     */
    static DigitalIn& getInstance()
    {
        static DigitalIn digitalIn = DigitalIn();
        return digitalIn;
    }

    /**
     * @brief Sets port direction and pullup mode for the given device type
     */
    void configureDevice(DI_Device mode);

    /**
     * @brief Returns the logical signal level of the given channel
     * 
     * @param channel The channel whose signal level should be returned
     * @return The logical signal level of the channel
     */
    DI_Level_e getLevel(DI_Channel_e channel);

private:
    MCP23S17PI* expander[2];

    DigitalIn();
};

#endif // DIGITALIN_H
