#ifndef DIGITALOUT_H
#define DIGITALOUT_H

#include "bcm2835.h"
#include <stdint.h>
#include "HALFactory.h"
#include "IDigitalOut.h"

/**
 * @brief Abstracts digital output signals of the application.
 * @details This class abstracts the digital output signals of the application.
 *          This includes GPIO signals as well as the signals that are available
 *          via the two MCP23S17 port expanders.
 */
class DigitalOut : public IDigitalOut
{
public:
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
    virtual void configureDevice(DO_Device device);

    /**
     * @brief Sets a logical signal level of a given channel
     *
     * @param channel The channel whose signal level should be set
     * @param level The signal level to be set
     */
    virtual void setLevel(DO_Channel_e channel, DO_Level_e level, BoardNumber_e board = BOARD_0);

private:
    static const uint8_t MAX_NUMBER_OF_MCPS = 4u;

    MCP23S17PI* expander[MAX_NUMBER_OF_MCPS];

    DigitalOut();  // hide default constructor

};

#endif // DIGITALOUT_H
