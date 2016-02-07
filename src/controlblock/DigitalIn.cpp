#include <stdint.h>

#include "DigitalIn.h"
#include <iostream>

DigitalIn::DigitalIn()
{
    expander[0] = &HALFactory::getInstance().getMCP23S17(HALFactory::MCPCHANNEL_1);
    expander[1] = &HALFactory::getInstance().getMCP23S17(HALFactory::MCPCHANNEL_2);
}

DigitalIn::~DigitalIn()
{
}

void DigitalIn::configureDevice(DI_Device device)
{
    switch(device)
    {
        case DI_DEVICE_ALLIN:
            bcm2835_gpio_fsel(RPI_GPIO_P1_12, BCM2835_GPIO_FSEL_INPT);
            for (uint8_t i = 0u ; i < 16u ; ++i)
            {
                expander[0]->setPinMode(i, MCP23S17PI::DIR_INPUT);
                expander[0]->setPullupMode(i, MCP23S17PI::PULLUP_ENABLED);

                expander[1]->setPinMode(i, MCP23S17PI::DIR_INPUT);
                expander[1]->setPullupMode(i, MCP23S17PI::PULLUP_ENABLED);
            }
            break;
        case DI_DEVICE_SNES:
            bcm2835_gpio_fsel(RPI_GPIO_P1_12, BCM2835_GPIO_FSEL_INPT);

            expander[0]->setPinMode(11, MCP23S17PI::DIR_INPUT);
            expander[0]->setPullupMode(11, MCP23S17PI::PULLUP_ENABLED);

            expander[0]->setPinMode(10, MCP23S17PI::DIR_INPUT);
            expander[0]->setPullupMode(10, MCP23S17PI::PULLUP_ENABLED);

            break;
        default:
            throw 50;
    }
}

DigitalIn::DI_Level_e DigitalIn::getLevel(DigitalIn::DI_Channel_e channel)
{
    DI_Level_e returnLevel = DI_LEVEL_LOW;

    switch(channel)
    {
        case DI_CHANNEL_FROMPOWERSWITCH:
            returnLevel = bcm2835_gpio_lev(RPI_GPIO_P1_12) == LOW ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
            break;
        case DI_CHANNEL_P1_RIGHT:
            returnLevel = expander[0]->digitalRead(0) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
            break;
        case DI_CHANNEL_P1_LEFT:
            returnLevel = expander[0]->digitalRead(1) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
            break;
        case DI_CHANNEL_P1_UP:
            returnLevel = expander[0]->digitalRead(2) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
            break;
        case DI_CHANNEL_P1_DOWN:
            returnLevel = expander[0]->digitalRead(3) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
            break;
        case DI_CHANNEL_P1_SW1:
            returnLevel = expander[0]->digitalRead(4) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
            break;
        case DI_CHANNEL_P1_SW2:
            returnLevel = expander[0]->digitalRead(5) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
            break;
        case DI_CHANNEL_P1_SW3:
            returnLevel = expander[0]->digitalRead(6) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
            break;
        case DI_CHANNEL_P1_SW4:
            returnLevel = expander[0]->digitalRead(7) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
            break;
        case DI_CHANNEL_P1_SW5:
            returnLevel = expander[1]->digitalRead(0) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
            break;
        case DI_CHANNEL_P1_SW6:
            returnLevel = expander[1]->digitalRead(1) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
            break;
        case DI_CHANNEL_P1_SW7:
            returnLevel = expander[1]->digitalRead(2) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
            break;
        case DI_CHANNEL_P1_SW8:
            returnLevel = expander[1]->digitalRead(3) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
            break;
        case DI_CHANNEL_P1_START:
            returnLevel = expander[1]->digitalRead(4) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
            break;
        case DI_CHANNEL_P1_COIN:
            returnLevel = expander[1]->digitalRead(5) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
            break;
        case DI_CHANNEL_P1_A:
            returnLevel = expander[1]->digitalRead(6) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
            break;
        case DI_CHANNEL_P1_B:
            returnLevel = expander[1]->digitalRead(7) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
            break;
        case DI_CHANNEL_P2_RIGHT:
            returnLevel = expander[0]->digitalRead(15) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
            break;
        case DI_CHANNEL_P2_LEFT:
            returnLevel = expander[0]->digitalRead(14) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
            break;
        case DI_CHANNEL_P2_UP:
            returnLevel = expander[0]->digitalRead(13) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
            break;
        case DI_CHANNEL_P2_DOWN:
            returnLevel = expander[0]->digitalRead(12) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
            break;
        case DI_CHANNEL_P2_SW1:
            returnLevel = expander[0]->digitalRead(11) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
            break;
        case DI_CHANNEL_P2_SW2:
            returnLevel = expander[0]->digitalRead(10) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
            break;
        case DI_CHANNEL_P2_SW3:
            returnLevel = expander[0]->digitalRead(9) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
            break;
        case DI_CHANNEL_P2_SW4:
            returnLevel = expander[0]->digitalRead(8) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
            break;
        case DI_CHANNEL_P2_SW5:
            returnLevel = expander[1]->digitalRead(15) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
            break;
        case DI_CHANNEL_P2_SW6:
            returnLevel = expander[1]->digitalRead(14) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
            break;
        case DI_CHANNEL_P2_SW7:
            returnLevel = expander[1]->digitalRead(13) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
            break;
        case DI_CHANNEL_P2_SW8:
            returnLevel = expander[1]->digitalRead(12) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
            break;
        case DI_CHANNEL_P2_START:
            returnLevel = expander[1]->digitalRead(11) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
            break;
        case DI_CHANNEL_P2_COIN:
            returnLevel = expander[1]->digitalRead(10) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
            break;
        case DI_CHANNEL_P2_A:
            returnLevel = expander[1]->digitalRead(9) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
            break;
        case DI_CHANNEL_P2_B:
            returnLevel = expander[1]->digitalRead(8) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
            break;
        case DI_CHANNEL_P1_DATA:
            returnLevel = expander[0]->digitalRead(11) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
            break;
        case DI_CHANNEL_P2_DATA:
            returnLevel = expander[0]->digitalRead(10) == MCP23S17PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
            break;
    }

    return returnLevel;
}
