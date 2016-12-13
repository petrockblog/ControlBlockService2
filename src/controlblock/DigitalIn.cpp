#include <stdint.h>

#include "DigitalIn.h"
#include <iostream>

DigitalIn::DigitalIn()
{
    expander[0] = &HALFactory::getInstance().getMCP23S17(HALFactory::MCPCHANNEL_1);
    expander[1] = &HALFactory::getInstance().getMCP23S17(HALFactory::MCPCHANNEL_2);
    expander[2] = &HALFactory::getInstance().getMCP23S17(HALFactory::MCPCHANNEL_3);
    expander[3] = &HALFactory::getInstance().getMCP23S17(HALFactory::MCPCHANNEL_4);
}

DigitalIn::~DigitalIn()
{
}

void DigitalIn::configureDevice(DI_Device device)
{
    switch (device)
    {
    case DI_DEVICE_ALLIN:
        bcm2835_gpio_fsel(RPI_GPIO_P1_12, BCM2835_GPIO_FSEL_INPT);
        for (uint8_t i = 0u; i < 16u; ++i)
        {
            for (uint8_t mcpIndex = 0u; mcpIndex < MAX_NUMBER_OF_MCPS; mcpIndex++)
            {
                expander[mcpIndex]->setPinMode(i, MCP23S17PI::DIR_INPUT);
                expander[mcpIndex]->setPullupMode(i, MCP23S17PI::PULLUP_ENABLED);
            }
        }
        break;
    case DI_DEVICE_SNES:
        bcm2835_gpio_fsel(RPI_GPIO_P1_12, BCM2835_GPIO_FSEL_INPT);

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
    default:
        throw 50;
    }
}

DigitalIn::DI_Level_e DigitalIn::getLevel(DigitalIn::DI_Channel_e channel, BoardNumber_e board)
{
    DI_Level_e returnLevel = DI_LEVEL_LOW;

    const uint32_t offset = (board == BOARD_0 ? 0u : 2u);
    switch (channel)
    {
    case DI_CHANNEL_FROMPOWERSWITCH:
        returnLevel = bcm2835_gpio_lev(RPI_GPIO_P1_12) == LOW ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P1_RIGHT:
        returnLevel =
                expander[0 + offset]->digitalRead(0) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P1_LEFT:
        returnLevel =
                expander[0 + offset]->digitalRead(1) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P1_UP:
        returnLevel =
                expander[0 + offset]->digitalRead(2) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P1_DOWN:
        returnLevel =
                expander[0 + offset]->digitalRead(3) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P1_SW1:
        returnLevel =
                expander[0 + offset]->digitalRead(4) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P1_SW2:
        returnLevel =
                expander[0 + offset]->digitalRead(5) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P1_SW3:
        returnLevel =
                expander[0 + offset]->digitalRead(6) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P1_SW4:
        returnLevel =
                expander[0 + offset]->digitalRead(7) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P1_SW5:
        returnLevel =
                expander[1 + offset]->digitalRead(0) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P1_SW6:
        returnLevel =
                expander[1 + offset]->digitalRead(1) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P1_SW7:
        returnLevel =
                expander[1 + offset]->digitalRead(2) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P1_SW8:
        returnLevel =
                expander[1 + offset]->digitalRead(3) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P1_START:
        returnLevel =
                expander[1 + offset]->digitalRead(4) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P1_COIN:
        returnLevel =
                expander[1 + offset]->digitalRead(5) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P1_A:
        returnLevel =
                expander[1 + offset]->digitalRead(6) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P1_B:
        returnLevel =
                expander[1 + offset]->digitalRead(7) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P2_RIGHT:
        returnLevel =
                expander[0 + offset]->digitalRead(15) == MCP23S17PI::LEVEL_HIGH ?
                        DI_LEVEL_LOW : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P2_LEFT:
        returnLevel =
                expander[0 + offset]->digitalRead(14) == MCP23S17PI::LEVEL_HIGH ?
                        DI_LEVEL_LOW : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P2_UP:
        returnLevel =
                expander[0 + offset]->digitalRead(13) == MCP23S17PI::LEVEL_HIGH ?
                        DI_LEVEL_LOW : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P2_DOWN:
        returnLevel =
                expander[0 + offset]->digitalRead(12) == MCP23S17PI::LEVEL_HIGH ?
                        DI_LEVEL_LOW : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P2_SW1:
        returnLevel =
                expander[0 + offset]->digitalRead(11) == MCP23S17PI::LEVEL_HIGH ?
                        DI_LEVEL_LOW : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P2_SW2:
        returnLevel =
                expander[0 + offset]->digitalRead(10) == MCP23S17PI::LEVEL_HIGH ?
                        DI_LEVEL_LOW : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P2_SW3:
        returnLevel =
                expander[0 + offset]->digitalRead(9) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P2_SW4:
        returnLevel =
                expander[0 + offset]->digitalRead(8) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P2_SW5:
        returnLevel =
                expander[1 + offset]->digitalRead(15) == MCP23S17PI::LEVEL_HIGH ?
                        DI_LEVEL_LOW : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P2_SW6:
        returnLevel =
                expander[1 + offset]->digitalRead(14) == MCP23S17PI::LEVEL_HIGH ?
                        DI_LEVEL_LOW : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P2_SW7:
        returnLevel =
                expander[1 + offset]->digitalRead(13) == MCP23S17PI::LEVEL_HIGH ?
                        DI_LEVEL_LOW : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P2_SW8:
        returnLevel =
                expander[1 + offset]->digitalRead(12) == MCP23S17PI::LEVEL_HIGH ?
                        DI_LEVEL_LOW : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P2_START:
        returnLevel =
                expander[1 + offset]->digitalRead(11) == MCP23S17PI::LEVEL_HIGH ?
                        DI_LEVEL_LOW : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P2_COIN:
        returnLevel =
                expander[1 + offset]->digitalRead(10) == MCP23S17PI::LEVEL_HIGH ?
                        DI_LEVEL_LOW : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P2_A:
        returnLevel =
                expander[1 + offset]->digitalRead(9) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P2_B:
        returnLevel =
                expander[1 + offset]->digitalRead(8) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P1_DATA:
        returnLevel =
                expander[0 + offset]->digitalRead(11) == MCP23S17PI::LEVEL_HIGH ?
                        DI_LEVEL_LOW : DI_LEVEL_HIGH;
        break;
    case DI_CHANNEL_P2_DATA:
        returnLevel =
                expander[0 + offset]->digitalRead(10) == MCP23S17PI::LEVEL_HIGH ?
                        DI_LEVEL_LOW : DI_LEVEL_HIGH;
        break;
    }

    return returnLevel;
}
