#ifndef MCP23S17PI_H
#define MCP23S17PI_H

#include <stdint.h>
#include "bcm2835.h"

class MCP23S17PI
{
public:
    enum ChipSelectPin
    {
        CHIPSELECT_0,
        CHIPSELECT_1
    };

    explicit MCP23S17PI(ChipSelectPin chipSelectPin, uint8_t deviceID);

    void begin();

    void end();

    enum Direction { DIR_INPUT = 0, DIR_OUTPUT };

    enum Level { LEVEL_LOW = 0, LEVEL_HIGH };

    enum Pullup { PULLUP_ENABLED = 0, PULLUP_DISABLED };

    void setPinMode(uint8_t pin, Direction dir);
    void setPullupMode(uint8_t pin, Pullup mode);
    void digitalWrite(uint8_t pin, Level val);
    Level digitalRead(uint8_t pin);

    void writeGPIO(uint16_t data);
    uint16_t readGPIO();

private:
    static bool isBCM2835Initialized;

    static const uint8_t MCP23S17_DEFAULT_SLAVE_ADDRESS = 0x00;
    static const uint8_t MCP23S17PI_IODIRA = 0x00;
    static const uint8_t MCP23S17PI_IODIRB = 0x01;
    static const uint8_t MCP23S17PI_IPOLA = 0x2;
    static const uint8_t MCP23S17PI_IPOLB = 0x3;
    static const uint8_t MCP23S17PI_GPIOA = 0x12;
    static const uint8_t MCP23S17PI_GPIOB = 0x13;
    static const uint8_t MCP23S17PI_OLATA = 0x14;
    static const uint8_t MCP23S17PI_OLATB = 0x15;
    static const uint8_t MCP23S17PI_IOCON = 0x0A;
    static const uint8_t MCP23S17PI_GPPUA = 0x0C;
    static const uint8_t MCP23S17PI_GPPUB = 0x0D;

    // Bits in the IOCON register
    static const uint8_t IOCON_UNUSED = 0x01;
    static const uint8_t IOCON_INTPOL = 0x02;
    static const uint8_t IOCON_ODR = 0x04;
    static const uint8_t IOCON_HAEN = 0x08;
    static const uint8_t IOCON_DISSLW = 0x10;
    static const uint8_t IOCON_SEQOP = 0x20;
    static const uint8_t IOCON_MIRROR = 0x40;
    static const uint8_t IOCON_BANK_MODE = 0x80;

    static const uint8_t MCP23S08_CMD_WRITE = 0x40;
    static const uint8_t MCP23S08_CMD_READ = 0x41;

    // Default initialisation mode
    static const uint8_t IOCON_INIT = 0x28; // IOCON_SEQOP and IOCON_HAEN from above

    bcm2835SPIChipSelect _chipSelectPin;
    uint8_t _deviceID;

    uint8_t _GPIOA, _GPIOB;
    uint8_t _IODIRA, _IODIRB;
    uint8_t _GPPUA, _GPPUB;

    void writeRegister(uint8_t regaddress, uint8_t val);
    void writeRegisterWord(const uint8_t &regAddress, uint16_t &data);
    uint8_t readRegister(uint8_t regaddress);
    uint16_t readRegisterWord(uint8_t regaddress);
};
#endif
