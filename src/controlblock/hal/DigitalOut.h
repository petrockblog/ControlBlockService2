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
    DigitalOut();

    /**
     * @brief Destructor
     */
    ~DigitalOut();

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
};

#endif // DIGITALOUT_H
