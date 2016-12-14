#ifndef DIGITALOUT_H
#define DIGITALOUT_H

#include "bcm2835.h"
#include <stdint.h>
#include "HALFactory.h"

/**
 * @brief Abstracts digital output signals of the application.
 * @details This class abstracts the digital output signals of the application.
 *          This includes GPIO signals as well as the signals that are available
 *          via the two MCP23S17 port expanders.
 */
class DigitalOut
{
public:
    /**
     * Digital output channel identifiers
     */
    enum DO_Channel_e
    {
        DO_CHANNEL_TOPOWERSWITCH = 0,  //!< Status signal to power switch uC
        DO_CHANNEL_P1P2_STROBE,        //!< Strobe/latch signal for SNES controller
        DO_CHANNEL_P1P2_CLOCK,         //!< Clock signal for SNES controller
        DO_CHANNEL_P1_VCC,             //!< Supply voltage for SNES controller, player 1 
        DO_CHANNEL_P2_VCC,             //!< Supply voltage for SNES controller, player 2
    };

    /**
     * Board identifiers in case of several stacked ControlBLocks
     */
    enum BoardNumber_e
    {
        BOARD_0 = 0,//!< BOARD_0
        BOARD_1     //!< BOARD_1
    };

    /**
     * Logical output level identifiers
     */
    enum DO_Level_e
    {
        DO_LEVEL_LOW = 0,  //!< Logical low
        DO_LEVEL_HIGH      //!< Logical high
    };

    /**
     * Logical device identifiers
     */
    enum DO_Device
    {
        DO_DEVICE_POWERSWITCH = 0,  //!< Power switch device
        DO_DEVICE_SNES              //!< SNES controller device
    };

    /**
     * @brief Destructor
     */
    ~DigitalOut();

    /**
     * @brief Returns a singleton instance
     */
    static DigitalOut& getInstance()
    {
        static DigitalOut digitalOut = DigitalOut();
        return digitalOut;
    }

    /**
     * @brief Configures port direction, pullup-mode, and initial signal level
     *        for a given device.
     *
     * @param device The device.
     */
    void configureDevice(DO_Device device);

    /**
     * @brief Sets a logical signal level of a given channel
     *
     * @param channel The channel whose signal level should be set
     * @param level The signal level to be set
     */
    void setLevel(DO_Channel_e channel, DO_Level_e level, BoardNumber_e board = BOARD_0);

private:
    static const uint8_t MAX_NUMBER_OF_MCPS = 4u;

    MCP23S17PI* expander[MAX_NUMBER_OF_MCPS];

    DigitalOut();  // hide default constructor

};

#endif // DIGITALOUT_H
