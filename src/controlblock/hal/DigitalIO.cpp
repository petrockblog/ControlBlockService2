#include "hal/DigitalIO.h"
#include "bcm2835.h"
#include <iostream>

DigitalIO::DigitalIO(MCP23S17PI& mcp1ref, MCP23S17PI& mcp2ref) :
	mcp1(mcp1ref),
	mcp2(mcp2ref)
{
}

void DigitalIO::configureDevice(DIO_Device mode)
{
    switch (mode) {
    case IDigitalIO::DIO_DEVICE_POWERSWITCH:
    	bcm2835_gpio_fsel(RPI_GPIO_P1_12, BCM2835_GPIO_FSEL_INPT);
    	bcm2835_gpio_fsel(RPI_GPIO_P1_11, BCM2835_GPIO_FSEL_OUTP);
        break;
    case IDigitalIO::DIO_DEVICE_ALLIN:
        for (uint8_t i = 0u; i < TOTAL_NUMBER_OF_CHANNELS; ++i) {
            mcp1.setPinMode(i, MCP23S17PI::DIR_INPUT);
            mcp1.setPullupMode(i, MCP23S17PI::PULLUP_ENABLED);

            mcp2.setPinMode(i, MCP23S17PI::DIR_INPUT);
            mcp2.setPullupMode(i, MCP23S17PI::PULLUP_ENABLED);
        }
        break;
    case IDigitalIO::DIO_DEVICE_SNES:

        mcp1.setPinMode(11, MCP23S17PI::DIR_INPUT);
        mcp1.setPullupMode(11, MCP23S17PI::PULLUP_ENABLED);

        mcp1.setPinMode(10, MCP23S17PI::DIR_INPUT);
        mcp1.setPullupMode(10, MCP23S17PI::PULLUP_ENABLED);

        // for ESC key
        mcp2.setPinMode(7, MCP23S17PI::DIR_INPUT);
        mcp2.setPullupMode(7, MCP23S17PI::PULLUP_ENABLED);

        // for F1 key
        mcp2.setPinMode(6, MCP23S17PI::DIR_INPUT);
        mcp2.setPullupMode(6, MCP23S17PI::PULLUP_ENABLED);

        mcp1.setPinMode(12, MCP23S17PI::DIR_OUTPUT);
        mcp1.setPinMode(13, MCP23S17PI::DIR_OUTPUT);
        mcp1.setPinMode(14, MCP23S17PI::DIR_OUTPUT);
        mcp1.setPinMode(15, MCP23S17PI::DIR_OUTPUT);
        mcp1.setPullupMode(12, MCP23S17PI::PULLUP_DISABLED);
        mcp1.setPullupMode(13, MCP23S17PI::PULLUP_DISABLED);
        mcp1.setPullupMode(14, MCP23S17PI::PULLUP_DISABLED);
        mcp1.setPullupMode(15, MCP23S17PI::PULLUP_DISABLED);
        mcp1.digitalWrite(12, MCP23S17PI::LEVEL_HIGH);
        mcp1.digitalWrite(13, MCP23S17PI::LEVEL_HIGH);
        mcp1.digitalWrite(14, MCP23S17PI::LEVEL_HIGH);
        mcp1.digitalWrite(15, MCP23S17PI::LEVEL_HIGH);
        break;
    case IDigitalIO::DIO_DEVICE_GENESIS:
        // Player 1
        mcp1.setPinMode(0, MCP23S17PI::DIR_INPUT);
        mcp1.setPullupMode(0, MCP23S17PI::PULLUP_ENABLED);

        mcp1.setPinMode(1, MCP23S17PI::DIR_INPUT);
        mcp1.setPullupMode(1, MCP23S17PI::PULLUP_ENABLED);

        mcp1.setPinMode(2, MCP23S17PI::DIR_INPUT);
        mcp1.setPullupMode(2, MCP23S17PI::PULLUP_ENABLED);

        mcp1.setPinMode(3, MCP23S17PI::DIR_INPUT);
        mcp1.setPullupMode(3, MCP23S17PI::PULLUP_ENABLED);

        mcp1.setPinMode(5, MCP23S17PI::DIR_INPUT);
        mcp1.setPullupMode(5, MCP23S17PI::PULLUP_ENABLED);

        mcp2.setPinMode(0, MCP23S17PI::DIR_INPUT);
        mcp2.setPullupMode(0, MCP23S17PI::PULLUP_ENABLED);

        // Player 2
        mcp1.setPinMode(15, MCP23S17PI::DIR_INPUT);
        mcp1.setPullupMode(15, MCP23S17PI::PULLUP_ENABLED);

        mcp1.setPinMode(14, MCP23S17PI::DIR_INPUT);
        mcp1.setPullupMode(14, MCP23S17PI::PULLUP_ENABLED);

        mcp1.setPinMode(13, MCP23S17PI::DIR_INPUT);
        mcp1.setPullupMode(13, MCP23S17PI::PULLUP_ENABLED);

        mcp1.setPinMode(12, MCP23S17PI::DIR_INPUT);
        mcp1.setPullupMode(12, MCP23S17PI::PULLUP_ENABLED);

        mcp1.setPinMode(10, MCP23S17PI::DIR_INPUT);
        mcp1.setPullupMode(10, MCP23S17PI::PULLUP_ENABLED);

        mcp2.setPinMode(15, MCP23S17PI::DIR_INPUT);
        mcp2.setPullupMode(15, MCP23S17PI::PULLUP_ENABLED);

        // VCC Player 1
        mcp1.setPinMode(4, MCP23S17PI::DIR_OUTPUT);
        mcp1.setPullupMode(4, MCP23S17PI::PULLUP_DISABLED);
        mcp1.digitalWrite(4, MCP23S17PI::LEVEL_HIGH);

        // GND Player 1
        mcp1.setPinMode(7, MCP23S17PI::DIR_OUTPUT);
        mcp1.setPullupMode(7, MCP23S17PI::PULLUP_DISABLED);
        mcp1.digitalWrite(7, MCP23S17PI::LEVEL_LOW);

        // SELECT Player 1
        mcp1.setPinMode(6, MCP23S17PI::DIR_OUTPUT);
        mcp1.setPullupMode(6, MCP23S17PI::PULLUP_DISABLED);
        mcp1.digitalWrite(6, MCP23S17PI::LEVEL_LOW);

        // VCC Player 2
        mcp1.setPinMode(11, MCP23S17PI::DIR_OUTPUT);
        mcp1.setPullupMode(11, MCP23S17PI::PULLUP_DISABLED);
        mcp1.digitalWrite(11, MCP23S17PI::LEVEL_HIGH);

        // GND Player 2
        mcp1.setPinMode(8, MCP23S17PI::DIR_OUTPUT);
        mcp1.setPullupMode(8, MCP23S17PI::PULLUP_DISABLED);
        mcp1.digitalWrite(8, MCP23S17PI::LEVEL_LOW);

        // SELECT Player 2
        mcp1.setPinMode(9, MCP23S17PI::DIR_OUTPUT);
        mcp1.setPullupMode(9, MCP23S17PI::PULLUP_DISABLED);
        mcp1.digitalWrite(9, MCP23S17PI::LEVEL_LOW);

        break;
    default:
      std::cout << "DigitalIO: Unknown device type" << std::endl;
      throw 50;
    }
}

IDigitalIO::DIO_Level_e DigitalIO::getLevel(DIO_Channel_e channel)
{
    DIO_Level_e returnLevel = DIO_LEVEL_LOW;

    switch (channel) {
    case DIO_CHANNEL_FROMPOWERSWITCH: returnLevel = bcm2835_gpio_lev(RPI_GPIO_P1_12) == LOW ? DIO_LEVEL_LOW : DIO_LEVEL_HIGH;
        break;
    case DIO_CHANNEL_P1_RIGHT: returnLevel = mcp1.digitalRead(0) == MCP23S17PI::LEVEL_HIGH ? DIO_LEVEL_LOW : DIO_LEVEL_HIGH;
        break;
    case DIO_CHANNEL_P1_LEFT: returnLevel = mcp1.digitalRead(1) == MCP23S17PI::LEVEL_HIGH ? DIO_LEVEL_LOW : DIO_LEVEL_HIGH;
        break;
    case DIO_CHANNEL_P1_UP: returnLevel = mcp1.digitalRead(2) == MCP23S17PI::LEVEL_HIGH ? DIO_LEVEL_LOW : DIO_LEVEL_HIGH;
        break;
    case DIO_CHANNEL_P1_DOWN: returnLevel = mcp1.digitalRead(3) == MCP23S17PI::LEVEL_HIGH ? DIO_LEVEL_LOW : DIO_LEVEL_HIGH;
        break;
    case DIO_CHANNEL_P1_SW1: returnLevel = mcp1.digitalRead(4) == MCP23S17PI::LEVEL_HIGH ? DIO_LEVEL_LOW : DIO_LEVEL_HIGH;
        break;
    case DIO_CHANNEL_P1_SW2: returnLevel = mcp1.digitalRead(5) == MCP23S17PI::LEVEL_HIGH ? DIO_LEVEL_LOW : DIO_LEVEL_HIGH;
        break;
    case DIO_CHANNEL_P1_SW3: returnLevel = mcp1.digitalRead(6) == MCP23S17PI::LEVEL_HIGH ? DIO_LEVEL_LOW : DIO_LEVEL_HIGH;
        break;
    case DIO_CHANNEL_P1_SW4: returnLevel = mcp1.digitalRead(7) == MCP23S17PI::LEVEL_HIGH ? DIO_LEVEL_LOW : DIO_LEVEL_HIGH;
        break;
    case DIO_CHANNEL_P1_SW5: returnLevel = mcp2.digitalRead(0) == MCP23S17PI::LEVEL_HIGH ? DIO_LEVEL_LOW : DIO_LEVEL_HIGH;
        break;
    case DIO_CHANNEL_P1_SW6: returnLevel = mcp2.digitalRead(1) == MCP23S17PI::LEVEL_HIGH ? DIO_LEVEL_LOW : DIO_LEVEL_HIGH;
        break;
    case DIO_CHANNEL_P1_SW7: returnLevel = mcp2.digitalRead(2) == MCP23S17PI::LEVEL_HIGH ? DIO_LEVEL_LOW : DIO_LEVEL_HIGH;
        break;
    case DIO_CHANNEL_P1_SW8: returnLevel = mcp2.digitalRead(3) == MCP23S17PI::LEVEL_HIGH ? DIO_LEVEL_LOW : DIO_LEVEL_HIGH;
        break;
    case DIO_CHANNEL_P1_START: returnLevel = mcp2.digitalRead(4) == MCP23S17PI::LEVEL_HIGH ? DIO_LEVEL_LOW : DIO_LEVEL_HIGH;
        break;
    case DIO_CHANNEL_P1_COIN: returnLevel = mcp2.digitalRead(5) == MCP23S17PI::LEVEL_HIGH ? DIO_LEVEL_LOW : DIO_LEVEL_HIGH;
        break;
    case DIO_CHANNEL_P1_A: returnLevel = mcp2.digitalRead(6) == MCP23S17PI::LEVEL_HIGH ? DIO_LEVEL_LOW : DIO_LEVEL_HIGH;
        break;
    case DIO_CHANNEL_P1_B: returnLevel = mcp2.digitalRead(7) == MCP23S17PI::LEVEL_HIGH ? DIO_LEVEL_LOW : DIO_LEVEL_HIGH;
        break;
    case DIO_CHANNEL_P2_RIGHT: returnLevel = mcp1.digitalRead(15) == MCP23S17PI::LEVEL_HIGH ? DIO_LEVEL_LOW : DIO_LEVEL_HIGH;
        break;
    case DIO_CHANNEL_P2_LEFT: returnLevel = mcp1.digitalRead(14) == MCP23S17PI::LEVEL_HIGH ? DIO_LEVEL_LOW : DIO_LEVEL_HIGH;
        break;
    case DIO_CHANNEL_P2_UP: returnLevel = mcp1.digitalRead(13) == MCP23S17PI::LEVEL_HIGH ? DIO_LEVEL_LOW : DIO_LEVEL_HIGH;
        break;
    case DIO_CHANNEL_P2_DOWN: returnLevel = mcp1.digitalRead(12) == MCP23S17PI::LEVEL_HIGH ? DIO_LEVEL_LOW : DIO_LEVEL_HIGH;
        break;
    case DIO_CHANNEL_P2_SW1: returnLevel = mcp1.digitalRead(11) == MCP23S17PI::LEVEL_HIGH ? DIO_LEVEL_LOW : DIO_LEVEL_HIGH;
    	break;
    case DIO_CHANNEL_P2_SW2: returnLevel = mcp1.digitalRead(10) == MCP23S17PI::LEVEL_HIGH ? DIO_LEVEL_LOW : DIO_LEVEL_HIGH;
        break;
    case DIO_CHANNEL_P2_SW3: returnLevel = mcp1.digitalRead(9) == MCP23S17PI::LEVEL_HIGH ? DIO_LEVEL_LOW : DIO_LEVEL_HIGH;
        break;
    case DIO_CHANNEL_P2_SW4: returnLevel = mcp1.digitalRead(8) == MCP23S17PI::LEVEL_HIGH ? DIO_LEVEL_LOW : DIO_LEVEL_HIGH;
        break;
    case DIO_CHANNEL_P2_SW5: returnLevel = mcp2.digitalRead(15) == MCP23S17PI::LEVEL_HIGH ? DIO_LEVEL_LOW : DIO_LEVEL_HIGH;
        break;
    case DIO_CHANNEL_P2_SW6: returnLevel = mcp2.digitalRead(14) == MCP23S17PI::LEVEL_HIGH ? DIO_LEVEL_LOW : DIO_LEVEL_HIGH;
        break;
    case DIO_CHANNEL_P2_SW7: returnLevel = mcp2.digitalRead(13) == MCP23S17PI::LEVEL_HIGH ? DIO_LEVEL_LOW : DIO_LEVEL_HIGH;
        break;
    case DIO_CHANNEL_P2_SW8: returnLevel = mcp2.digitalRead(12) == MCP23S17PI::LEVEL_HIGH ? DIO_LEVEL_LOW : DIO_LEVEL_HIGH;
        break;
    case DIO_CHANNEL_P2_START: returnLevel = mcp2.digitalRead(11) == MCP23S17PI::LEVEL_HIGH ? DIO_LEVEL_LOW : DIO_LEVEL_HIGH;
        break;
    case DIO_CHANNEL_P2_COIN: returnLevel = mcp2.digitalRead(10) == MCP23S17PI::LEVEL_HIGH ? DIO_LEVEL_LOW : DIO_LEVEL_HIGH;
        break;
    case DIO_CHANNEL_P2_A: returnLevel = mcp2.digitalRead(9) == MCP23S17PI::LEVEL_HIGH ? DIO_LEVEL_LOW : DIO_LEVEL_HIGH;
        break;
    case DIO_CHANNEL_P2_B: returnLevel = mcp2.digitalRead(8) == MCP23S17PI::LEVEL_HIGH ? DIO_LEVEL_LOW : DIO_LEVEL_HIGH;
        break;
    default:
        throw 51;
    }

    return returnLevel;
}

void DigitalIO::setLevel(DIO_Channel_e channel, DIO_Level_e level)
{
    MCP23S17PI::Level mcpLevel;

    if (level == DIO_LEVEL_LOW) {
        mcpLevel = MCP23S17PI::LEVEL_LOW;
    }
    else {
        mcpLevel = MCP23S17PI::LEVEL_HIGH;
    }

    switch (channel) {
    case DIO_CHANNEL_TOPOWERSWITCH:bcm2835_gpio_write(RPI_GPIO_P1_11, mcpLevel == MCP23S17PI::LEVEL_LOW ? LOW : HIGH);
        break;
    case DIO_CHANNEL_P1_RIGHT: mcp1.digitalWrite(0, mcpLevel);
        break;
    case DIO_CHANNEL_P1_LEFT: mcp1.digitalWrite(1, mcpLevel);
        break;
    case DIO_CHANNEL_P1_UP: 
        mcp1.digitalWrite(2, mcpLevel);
        break;
    case DIO_CHANNEL_P1_DOWN: mcp1.digitalWrite(3, mcpLevel);
        break;
    case DIO_CHANNEL_P1_SW1: mcp1.digitalWrite(4, mcpLevel);
        break;
    case DIO_CHANNEL_P1_SW2: mcp1.digitalWrite(5, mcpLevel);
        break;
    case DIO_CHANNEL_P1_SW3: mcp1.digitalWrite(6, mcpLevel);
        break;
    case DIO_CHANNEL_P1_SW4: mcp1.digitalWrite(7, mcpLevel);
        break;
    case DIO_CHANNEL_P1_SW5: mcp2.digitalWrite(0, mcpLevel);
        break;
    case DIO_CHANNEL_P1_SW6: mcp2.digitalWrite(1, mcpLevel);
        break;
    case DIO_CHANNEL_P1_SW7: mcp2.digitalWrite(2, mcpLevel);
        break;
    case DIO_CHANNEL_P1_SW8: mcp2.digitalWrite(3, mcpLevel);
        break;
    case DIO_CHANNEL_P1_START: mcp2.digitalWrite(4, mcpLevel);
        break;
    case DIO_CHANNEL_P1_COIN: mcp2.digitalWrite(5, mcpLevel);
        break;
    case DIO_CHANNEL_P1_A: mcp2.digitalWrite(6, mcpLevel);
        break;
    case DIO_CHANNEL_P1_B: mcp2.digitalWrite(7, mcpLevel);
        break;
    case DIO_CHANNEL_P2_RIGHT: mcp1.digitalWrite(15, mcpLevel);
        break;
    case DIO_CHANNEL_P2_LEFT: mcp1.digitalWrite(14, mcpLevel);
        break;
    case DIO_CHANNEL_P2_UP: mcp1.digitalWrite(13, mcpLevel);
        break;
    case DIO_CHANNEL_P2_DOWN: mcp1.digitalWrite(12, mcpLevel);
        break;
    case DIO_CHANNEL_P2_SW1: mcp1.digitalWrite(11, mcpLevel);
        break;
    case DIO_CHANNEL_P2_SW2: mcp1.digitalWrite(10, mcpLevel);
        break;
    case DIO_CHANNEL_P2_SW3: mcp1.digitalWrite(9, mcpLevel);
        break;
    case DIO_CHANNEL_P2_SW4: mcp1.digitalWrite(8, mcpLevel);
        break;
    case DIO_CHANNEL_P2_SW5: mcp2.digitalWrite(15, mcpLevel);
        break;
    case DIO_CHANNEL_P2_SW6: mcp2.digitalWrite(14, mcpLevel);
        break;
    case DIO_CHANNEL_P2_SW7: mcp2.digitalWrite(13, mcpLevel);
        break;
    case DIO_CHANNEL_P2_SW8: mcp2.digitalWrite(12, mcpLevel);
        break;
    case DIO_CHANNEL_P2_START: mcp2.digitalWrite(11, mcpLevel);
        break;
    case DIO_CHANNEL_P2_COIN: mcp2.digitalWrite(10, mcpLevel);
        break;
    case DIO_CHANNEL_P2_A: mcp2.digitalWrite(9, mcpLevel);
        break;
    case DIO_CHANNEL_P2_B: mcp2.digitalWrite(8, mcpLevel);
        break;
    case DIO_CHANNEL_GENESIS_P1_SELECT: mcp1.digitalWrite(6, mcpLevel);
        break;
    case DIO_CHANNEL_GENESIS_P2_SELECT: mcp1.digitalWrite(9, mcpLevel);
        break;
    }
}
