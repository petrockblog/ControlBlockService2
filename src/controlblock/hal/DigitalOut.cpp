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

#include "DigitalOut.h"

DigitalOut::DigitalOut()
{
    expander[0] = &HALFactory::getInstance().getMCP23S17(HALFactory::MCPCHANNEL_1);
    expander[1] = &HALFactory::getInstance().getMCP23S17(HALFactory::MCPCHANNEL_2);
    expander[2] = &HALFactory::getInstance().getMCP23S17(HALFactory::MCPCHANNEL_3);
    expander[3] = &HALFactory::getInstance().getMCP23S17(HALFactory::MCPCHANNEL_4);
}

DigitalOut::~DigitalOut()
{
}

void DigitalOut::configureDevice(DO_Device device)
{
    switch (device)
    {
    case DO_DEVICE_POWERSWITCH:
        bcm2835_gpio_fsel(RPI_GPIO_P1_11, BCM2835_GPIO_FSEL_OUTP);
        break;
    case DO_DEVICE_SNES:
        expander[0]->setPinMode(12, MCP23S17PI::DIR_OUTPUT);
        expander[0]->setPinMode(13, MCP23S17PI::DIR_OUTPUT);
        expander[0]->setPinMode(14, MCP23S17PI::DIR_OUTPUT);
        expander[0]->setPinMode(15, MCP23S17PI::DIR_OUTPUT);
        expander[0]->setPullupMode(12, MCP23S17PI::PULLUP_DISABLED);
        expander[0]->setPullupMode(13, MCP23S17PI::PULLUP_DISABLED);
        expander[0]->setPullupMode(14, MCP23S17PI::PULLUP_DISABLED);
        expander[0]->setPullupMode(15, MCP23S17PI::PULLUP_DISABLED);
        expander[0]->digitalWrite(12, MCP23S17PI::LEVEL_LOW);
        expander[0]->digitalWrite(13, MCP23S17PI::LEVEL_LOW);
        expander[0]->digitalWrite(14, MCP23S17PI::LEVEL_HIGH);
        expander[0]->digitalWrite(15, MCP23S17PI::LEVEL_HIGH);

        expander[2]->setPinMode(12, MCP23S17PI::DIR_OUTPUT);
        expander[2]->setPinMode(13, MCP23S17PI::DIR_OUTPUT);
        expander[2]->setPinMode(14, MCP23S17PI::DIR_OUTPUT);
        expander[2]->setPinMode(15, MCP23S17PI::DIR_OUTPUT);
        expander[2]->setPullupMode(12, MCP23S17PI::PULLUP_DISABLED);
        expander[2]->setPullupMode(13, MCP23S17PI::PULLUP_DISABLED);
        expander[2]->setPullupMode(14, MCP23S17PI::PULLUP_DISABLED);
        expander[2]->setPullupMode(15, MCP23S17PI::PULLUP_DISABLED);
        expander[2]->digitalWrite(12, MCP23S17PI::LEVEL_LOW);
        expander[2]->digitalWrite(13, MCP23S17PI::LEVEL_LOW);
        expander[2]->digitalWrite(14, MCP23S17PI::LEVEL_HIGH);
        expander[2]->digitalWrite(15, MCP23S17PI::LEVEL_HIGH);
        break;
    case DO_DEVICE_GENESIS:
        // todo add vcc and gnd
        expander[0]->setPinMode(6, MCP23S17PI::DIR_OUTPUT);
        expander[0]->setPullupMode(6, MCP23S17PI::PULLUP_DISABLED);
        expander[0]->digitalWrite(6, MCP23S17PI::LEVEL_LOW);

        expander[0]->setPinMode(9, MCP23S17PI::DIR_OUTPUT);
        expander[0]->setPullupMode(9, MCP23S17PI::PULLUP_DISABLED);
        expander[0]->digitalWrite(9, MCP23S17PI::LEVEL_LOW);

        expander[2]->setPinMode(6, MCP23S17PI::DIR_OUTPUT);
        expander[2]->setPullupMode(6, MCP23S17PI::PULLUP_DISABLED);
        expander[2]->digitalWrite(6, MCP23S17PI::LEVEL_LOW);

        expander[2]->setPinMode(9, MCP23S17PI::DIR_OUTPUT);
        expander[2]->setPullupMode(9, MCP23S17PI::PULLUP_DISABLED);
        expander[2]->digitalWrite(9, MCP23S17PI::LEVEL_LOW);
        break;
    }
}

void DigitalOut::setLevel(DO_Channel_e channel, DO_Level_e level, BoardNumber_e board)
{
    MCP23S17PI::Level outlevel;

    if (level == DO_LEVEL_LOW)
    {
        outlevel = MCP23S17PI::LEVEL_LOW;
    }
    else
    {
        outlevel = MCP23S17PI::LEVEL_HIGH;
    }

    const uint32_t offset = (board == BOARD_0 ? 0u : 2u);
    switch (channel)
    {
    case DO_CHANNEL_TOPOWERSWITCH:
        bcm2835_gpio_write(RPI_GPIO_P1_11, outlevel == MCP23S17PI::LEVEL_LOW ? LOW : HIGH);
        break;
    case DO_CHANNEL_P1P2_CLOCK:
        expander[0 + offset]->digitalWrite(12, outlevel);
        break;
    case DO_CHANNEL_P1P2_STROBE:
        expander[0 + offset]->digitalWrite(13, outlevel);
        break;
    case DO_CHANNEL_P2_VCC:
        expander[0 + offset]->digitalWrite(14, outlevel);
        break;
    case DO_CHANNEL_P1_VCC:
        expander[0 + offset]->digitalWrite(15, outlevel);
        break;
    }
}
