#include "DigitalOut.h"

DigitalOut::DigitalOut()
{
    expander[0] = &HALFactory::getInstance().getMCP23S17(HALFactory::MCPCHANNEL_1);
    expander[1] = &HALFactory::getInstance().getMCP23S17(HALFactory::MCPCHANNEL_2);
}

DigitalOut::~DigitalOut()
{
}

void DigitalOut::configureDevice(DO_Device device)
{
    switch(device)
    {
        case DO_DEVICE_POWERSWITCH:
            bcm2835_gpio_fsel(RPI_GPIO_P1_11, BCM2835_GPIO_FSEL_OUTP);
            break;
        case DO_DEVICE_SNES:
            expander[0]->setPinMode(0, MCP23S17PI::DIR_OUTPUT);
            expander[0]->setPinMode(1, MCP23S17PI::DIR_OUTPUT);
            expander[0]->setPinMode(2, MCP23S17PI::DIR_OUTPUT);
            expander[0]->setPinMode(13, MCP23S17PI::DIR_OUTPUT);
            expander[0]->setPinMode(14, MCP23S17PI::DIR_OUTPUT);
            expander[0]->setPinMode(15, MCP23S17PI::DIR_OUTPUT);
            expander[0]->setPullupMode(0, MCP23S17PI::PULLUP_DISABLED);
            expander[0]->setPullupMode(1, MCP23S17PI::PULLUP_DISABLED);
            expander[0]->setPullupMode(2, MCP23S17PI::PULLUP_DISABLED);
            expander[0]->setPullupMode(13, MCP23S17PI::PULLUP_DISABLED);
            expander[0]->setPullupMode(14, MCP23S17PI::PULLUP_DISABLED);
            expander[0]->setPullupMode(15, MCP23S17PI::PULLUP_DISABLED);
            expander[0]->digitalWrite(0, MCP23S17PI::LEVEL_LOW);
            expander[0]->digitalWrite(1, MCP23S17PI::LEVEL_LOW);
            expander[0]->digitalWrite(2, MCP23S17PI::LEVEL_LOW);
            expander[0]->digitalWrite(13, MCP23S17PI::LEVEL_LOW);
            expander[0]->digitalWrite(14, MCP23S17PI::LEVEL_LOW);
            expander[0]->digitalWrite(15, MCP23S17PI::LEVEL_LOW);
            break;
    }
}

void DigitalOut::setLevel(DO_Channel_e channel, DO_Level_e level)
{
    MCP23S17PI::Level outlevel;

    if(level == DO_LEVEL_LOW)
    {
        outlevel = MCP23S17PI::LEVEL_LOW;
    }
    else
    {
        outlevel = MCP23S17PI::LEVEL_HIGH;
    }

    switch(channel)
    {
        case DO_CHANNEL_TOPOWERSWITCH:
            bcm2835_gpio_write(RPI_GPIO_P1_11, outlevel == MCP23S17PI::LEVEL_LOW ? LOW : HIGH);
            break;
        case DO_CHANNEL_P1_STROBE:
            expander[0]->digitalWrite(1, outlevel);
            break;
        case DO_CHANNEL_P1_CLOCK:
            expander[0]->digitalWrite(2, outlevel);
            break;
        case DO_CHANNEL_P1_VCC:
            expander[0]->digitalWrite(0, outlevel);
            break;
        case DO_CHANNEL_P2_STROBE:
            expander[0]->digitalWrite(14, outlevel);
            break;
        case DO_CHANNEL_P2_CLOCK:
            expander[0]->digitalWrite(13, outlevel);
            break;
        case DO_CHANNEL_P2_VCC:
            expander[0]->digitalWrite(15, outlevel);
            break;
    }
}
