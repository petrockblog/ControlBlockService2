/**
 * (c) Copyright 2017  Florian Müller (contact@petrockblock.com)
 * https://github.com/petrockblog/ControlBlock2
 *
 * Permission to use, copy, modify and distribute the program in both binary and
 * source form, for non-commercial purposes, is hereby granted without fee,
 * providing that this license information and copyright notice appear with
 * all copies and any derived work.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event shall the authors be held liable for any damages
 * arising from the use of this software.
 *
 * This program is freeware for PERSONAL USE only. Commercial users must
 * seek permission of the copyright holders first. Commercial use includes
 * charging money for the program or software derived from the program.
 *
 * The copyright holders request that bug fixes and improvements to the code
 * should be forwarded to them so everyone can benefit from the modifications
 * in future versions.
 */

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
class DigitalIn: public IDigitalIn
{
public:
    /**
     * Constructor
     */
    DigitalIn();

    /**
     * @brief Destructor
     */
    ~DigitalIn();

    void initialize();

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
    static const uint8_t TOTAL_NUMBER_OF_CHANNELS = 16u;
    static const uint8_t MAX_NUMBER_OF_MCPS = 4u;

    MCP23S17PI* expander[MAX_NUMBER_OF_MCPS];
};

#endif // DIGITALIN_H
