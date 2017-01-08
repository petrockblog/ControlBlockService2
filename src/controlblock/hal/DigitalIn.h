#ifndef DIGITALIN_H
#define DIGITALIN_H

#include "bcm2835.h"
#include <stdint.h>
#include "HALFactory.h"
#include "IDigitalIn.h"

/**
 * @brief Abstracts digital input signals of the application.
 * @details This class abstracts the digital input signals of the application.
 *          This includes GPIO signals as well as the signals that are available
 *          via the two MCP23S17 port expanders.
 */
class DigitalIn : public IDigitalIn
{
public:
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
    virtual void configureDevice(DI_Device mode);

    /**
     * @brief Returns the logical signal level of the given channel
     * 
     * @param channel The channel whose signal level should be returned
     * @return The logical signal level of the channel
     */
    virtual DI_Level_e getLevel(DI_Channel_e channel, BoardNumber_e board = BOARD_0);

private:
    static const uint8_t MAX_NUMBER_OF_MCPS = 4u;

    MCP23S17PI* expander[MAX_NUMBER_OF_MCPS];

    DigitalIn();
};

#endif // DIGITALIN_H
