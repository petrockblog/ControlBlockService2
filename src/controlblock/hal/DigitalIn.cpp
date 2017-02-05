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

#include <stdint.h>

#include "DigitalIn.h"

DigitalIn::DigitalIn()
{
    expander[0] = &HALFactory::getInstance().getMCP23S17(HALFactory::MCPCHANNEL_1);
    expander[1] = &HALFactory::getInstance().getMCP23S17(HALFactory::MCPCHANNEL_2);
    expander[2] = &HALFactory::getInstance().getMCP23S17(HALFactory::MCPCHANNEL_3);
    expander[3] = &HALFactory::getInstance().getMCP23S17(HALFactory::MCPCHANNEL_4);
}

void DigitalIn::configureDevice(DI_Device device)
{
    switch (device) {
    case DI_DEVICE_POWERSWITCH:bcm2835_gpio_fsel(RPI_GPIO_P1_12, BCM2835_GPIO_FSEL_INPT);
        break;
    case DI_DEVICE_ALLIN:
        for (uint8_t i = 0u; i < TOTAL_NUMBER_OF_CHANNELS; ++i) {
            for (uint8_t mcpIndex = 0u; mcpIndex < MAX_NUMBER_OF_MCPS; mcpIndex++) {
                expander[mcpIndex]->setPinMode(i, MCP23S17PI::DIR_INPUT);
                expander[mcpIndex]->setPullupMode(i, MCP23S17PI::PULLUP_ENABLED);
            }
        }
        break;
    case DI_DEVICE_SNES:

        expander[0]->setPinMode(11, MCP23S17PI::DIR_INPUT);
        expander[0]->setPullupMode(11, MCP23S17PI::PULLUP_ENABLED);

        expander[0]->setPinMode(10, MCP23S17PI::DIR_INPUT);
        expander[0]->setPullupMode(10, MCP23S17PI::PULLUP_ENABLED);

        // for reset button
        expander[1]->setPinMode(8, MCP23S17PI::DIR_INPUT);
        expander[1]->setPullupMode(8, MCP23S17PI::PULLUP_ENABLED);

        expander[2]->setPinMode(11, MCP23S17PI::DIR_INPUT);
        expander[2]->setPullupMode(11, MCP23S17PI::PULLUP_ENABLED);

        expander[2]->setPinMode(10, MCP23S17PI::DIR_INPUT);
        expander[2]->setPullupMode(10, MCP23S17PI::PULLUP_ENABLED);

        // for reset button
        expander[3]->setPinMode(8, MCP23S17PI::DIR_INPUT);
        expander[3]->setPullupMode(8, MCP23S17PI::PULLUP_ENABLED);
        break;
    case DI_DEVICE_GENESIS:
        // Player 1
        expander[0]->setPinMode(0, MCP23S17PI::DIR_INPUT);
        expander[0]->setPullupMode(0, MCP23S17PI::PULLUP_ENABLED);

        expander[0]->setPinMode(1, MCP23S17PI::DIR_INPUT);
        expander[0]->setPullupMode(1, MCP23S17PI::PULLUP_ENABLED);

        expander[0]->setPinMode(2, MCP23S17PI::DIR_INPUT);
        expander[0]->setPullupMode(2, MCP23S17PI::PULLUP_ENABLED);

        expander[0]->setPinMode(3, MCP23S17PI::DIR_INPUT);
        expander[0]->setPullupMode(3, MCP23S17PI::PULLUP_ENABLED);

        expander[0]->setPinMode(5, MCP23S17PI::DIR_INPUT);
        expander[0]->setPullupMode(5, MCP23S17PI::PULLUP_ENABLED);

        expander[0]->setPinMode(6, MCP23S17PI::DIR_INPUT);
        expander[0]->setPullupMode(6, MCP23S17PI::PULLUP_ENABLED);

        expander[1]->setPinMode(0, MCP23S17PI::DIR_INPUT);
        expander[1]->setPullupMode(0, MCP23S17PI::PULLUP_ENABLED);

        // Player 2
        expander[0]->setPinMode(15, MCP23S17PI::DIR_INPUT);
        expander[0]->setPullupMode(15, MCP23S17PI::PULLUP_ENABLED);

        expander[0]->setPinMode(14, MCP23S17PI::DIR_INPUT);
        expander[0]->setPullupMode(14, MCP23S17PI::PULLUP_ENABLED);

        expander[0]->setPinMode(13, MCP23S17PI::DIR_INPUT);
        expander[0]->setPullupMode(13, MCP23S17PI::PULLUP_ENABLED);

        expander[0]->setPinMode(12, MCP23S17PI::DIR_INPUT);
        expander[0]->setPullupMode(12, MCP23S17PI::PULLUP_ENABLED);

        expander[0]->setPinMode(10, MCP23S17PI::DIR_INPUT);
        expander[0]->setPullupMode(10, MCP23S17PI::PULLUP_ENABLED);

        expander[0]->setPinMode(9, MCP23S17PI::DIR_INPUT);
        expander[0]->setPullupMode(9, MCP23S17PI::PULLUP_ENABLED);

        expander[1]->setPinMode(15, MCP23S17PI::DIR_INPUT);
        expander[1]->setPullupMode(15, MCP23S17PI::PULLUP_ENABLED);
        break;
    default:throw 50;
    }
}

DigitalIn::DI_Level_e DigitalIn::getLevel(DigitalIn::DI_Channel_e channel, BoardNumber_e board)
{
    DI_Level_e returnLevel = DI_LEVEL_LOW;

    const uint32_t offset = (board == BOARD_0 ? 0u : 2u);
    switch (channel) {
    case DI_CHANNEL_FROMPOWERSWITCH:
        returnLevel = bcm2835_gpio_lev(RPI_GPIO_P1_12) == LOW ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P1_RIGHT: returnLevel =
                                      expander[0 + offset]->digitalRead(0) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW
                                                                                                     : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P1_LEFT: returnLevel = expander[0 + offset]->digitalRead(1) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW
                                                                                                          : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P1_UP: returnLevel = expander[0 + offset]->digitalRead(2) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW
                                                                                                        : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P1_DOWN: returnLevel = expander[0 + offset]->digitalRead(3) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW
                                                                                                          : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P1_SW1: returnLevel = expander[0 + offset]->digitalRead(4) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW
                                                                                                         : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P1_SW2: returnLevel = expander[0 + offset]->digitalRead(5) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW
                                                                                                         : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P1_SW3: returnLevel = expander[0 + offset]->digitalRead(6) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW
                                                                                                         : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P1_SW4: returnLevel = expander[0 + offset]->digitalRead(7) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW
                                                                                                         : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P1_SW5: returnLevel = expander[1 + offset]->digitalRead(0) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW
                                                                                                         : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P1_SW6: returnLevel = expander[1 + offset]->digitalRead(1) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW
                                                                                                         : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P1_SW7: returnLevel = expander[1 + offset]->digitalRead(2) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW
                                                                                                         : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P1_SW8: returnLevel = expander[1 + offset]->digitalRead(3) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW
                                                                                                         : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P1_START: returnLevel =
                                      expander[1 + offset]->digitalRead(4) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW
                                                                                                     : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P1_COIN: returnLevel = expander[1 + offset]->digitalRead(5) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW
                                                                                                          : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P1_A: returnLevel = expander[1 + offset]->digitalRead(6) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW
                                                                                                       : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P1_B: returnLevel = expander[1 + offset]->digitalRead(7) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW
                                                                                                       : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P2_RIGHT: returnLevel =
                                      expander[0 + offset]->digitalRead(15) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW
                                                                                                      : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P2_LEFT: returnLevel =
                                     expander[0 + offset]->digitalRead(14) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW
                                                                                                     : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P2_UP: returnLevel = expander[0 + offset]->digitalRead(13) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW
                                                                                                         : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P2_DOWN: returnLevel =
                                     expander[0 + offset]->digitalRead(12) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW
                                                                                                     : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P1_DATA:
    case DI_CHANNEL_P2_SW1: returnLevel = expander[0 + offset]->digitalRead(11) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW
                                                                                                          : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P2_DATA:
    case DI_CHANNEL_P2_SW2: returnLevel = expander[0 + offset]->digitalRead(10) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW
                                                                                                          : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P2_SW3: returnLevel = expander[0 + offset]->digitalRead(9) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW
                                                                                                         : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P2_SW4: returnLevel = expander[0 + offset]->digitalRead(8) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW
                                                                                                         : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P2_SW5: returnLevel = expander[1 + offset]->digitalRead(15) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW
                                                                                                          : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P2_SW6: returnLevel = expander[1 + offset]->digitalRead(14) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW
                                                                                                          : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P2_SW7: returnLevel = expander[1 + offset]->digitalRead(13) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW
                                                                                                          : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P2_SW8: returnLevel = expander[1 + offset]->digitalRead(12) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW
                                                                                                          : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P2_START: returnLevel =
                                      expander[1 + offset]->digitalRead(11) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW
                                                                                                      : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_SNES_RESET:
    case DI_CHANNEL_P2_COIN: returnLevel =
                                     expander[1 + offset]->digitalRead(10) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW
                                                                                                     : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P2_A: returnLevel = expander[1 + offset]->digitalRead(9) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW
                                                                                                       : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P2_B: returnLevel = expander[1 + offset]->digitalRead(8) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW
                                                                                                       : DI_LEVEL_HIGH;
        break;
    }

    return returnLevel;
}
