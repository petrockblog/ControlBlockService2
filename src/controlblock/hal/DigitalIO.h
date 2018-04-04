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

#ifndef CONTROLBLOCKSERVICE2_DIGITALIO_H
#define CONTROLBLOCKSERVICE2_DIGITALIO_H

#include "hal/IDigitalIO.h"

class DigitalIO : public IDigitalIO {
public:
    DigitalIO(MCP23S17PI& mcp1ref, MCP23S17PI& mcp2ref);

    virtual void configureDevice(DIO_Device mode);

    virtual DIO_Level_e getLevel(DIO_Channel_e channel);

      /**
     * @brief Sets a logical signal level of a given channel
     *
     * @param channel The channel whose signal level should be set
     * @param level The signal level to be set
     */
    virtual void setLevel(DIO_Channel_e channel, DIO_Level_e level);

private:
  MCP23S17PI& mcp1;
  MCP23S17PI& mcp2;

};

#endif //CONTROLBLOCKSERVICE2_DIGITALIO_H
