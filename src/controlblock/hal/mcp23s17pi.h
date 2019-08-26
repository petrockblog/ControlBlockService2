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

#ifndef MCP23S17PI_H
#define MCP23S17PI_H

#include <stdint.h>
//#include "bcm2835.h"
#include "mcp23s17.h"

/**
 * @brief This class abstracts a port expander MCP23S17
 */
class MCP23S17PI {
 public:
  /**
   * @brief Chip select pin identifiers
   */
  enum ChipSelectPin {
    CHIPSELECT_0 = 0,  //!< Chip select pin CS0
    CHIPSELECT_1 = 1  //!< Chip select pin CS1
  };

  /**
   * Port direction identifiers
   */
  enum Direction {
    DIR_INPUT = 0,  //!< Input direction
    DIR_OUTPUT      //!< Output direction
  };

  /**
   * @brief Logical signal level identifiers
   */
  enum Level {
    LEVEL_LOW = 0,  //!< Logical low
    LEVEL_HIGH      //!< Logical high
  };

  /**
   * Pullup mode identifiers
   */
  enum Pullup {
    PULLUP_ENABLED = 0,  //!< Pullup enabled
    PULLUP_DISABLED      //!< Pullup disabled
  };

  /**
   * @brief Constructor
   *
   * @param chipSelectPin The chip-select pin of this expander
   * @param deviceID The device identifier, i.e., the address, of this expander
   */
  explicit MCP23S17PI(ChipSelectPin chipSelectPin, uint8_t deviceID);

  ~MCP23S17PI();

  /**
   * @brief Initializes the communication interface for the MCP23S17 instance
   */
  static void begin();

  /**
   * @brief Deinitializes the communication interface for the MCP23S17 instance
   */
  static void end();

  /**
   * @brief Sets the port direction of a given pin
   *
   * @param pin The pin whose direction should be set
   * @param dir The port direction to be set
   */
  void setPinMode(uint8_t pin, Direction dir);

  /**
   * @brief Sets the pullup mode of a given pin
   *
   * @param pin The pin whose pullup mode should be set
   * @param mode The pullup mode to be set
   */
  void setPullupMode(uint8_t pin, Pullup mode);

  /**
   * @brief Sets a given signal level for a given pin number
   * @details The pins numbers are organized in this way:
   *            /-------\
   *          0 |       | 15
   *          1 |       | 14
   *          2 |       | 13
   *          3 |       | 12
   *          4 |       | 11
   *          5 |       | 10
   *          6 |       |  9
   *          7 |      o|  8
   *            \-------/
   *
   * @param pin The pin number
   * @param val The signal level
   */
  void digitalWrite(uint8_t pin, Level val);

  /**
   * @brief Reads the signal level of a given pin number
   * @details The pins numbers are organized in this way:
   *            /-------\
   *          0 |       | 15
   *          1 |       | 14
   *          2 |       | 13
   *          3 |       | 12
   *          4 |       | 11
   *          5 |       | 10
   *          6 |       |  9
   *          7 |      o|  8
   *            \-------/
   *
   * @param pin The pin number
   * @return The signal level
   */
  Level digitalRead(uint8_t pin);

  /**
   * @brief Sets the port signal levels for all pins given the 16-bit data value
   *
   * @param data The data to be set. Bit 0 corresponds to pin 0, bit 1 to pin 1, and so on.
   */
  void writeGPIO(uint16_t data);

  /**
   * @brief Returns the port signal level for all pins in a 16-bit value.
   * @return The port levels. Bit 0 corresponds to pin 0, bit 1 to pin 1, and so on.
   */
  uint16_t readGPIO();

 private:
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

  // Default initialization mode
  static const uint8_t IOCON_INIT = 0x28; // IOCON_SEQOP and IOCON_HAEN from above

  static bool isBCM2835Initialized_;
  static int spi_cs0_fd_;

  ChipSelectPin chipSelectPin_;
  uint8_t deviceID_;

  uint8_t GPIOA_;
  uint8_t GPIOB_;
  uint8_t IODIRA_;
  uint8_t IODIRB_;
  uint8_t GPPUA_;
  uint8_t GPPUB_;

  void writeRegister(uint8_t regaddress, uint8_t val);
  void writeRegisterWord(const uint8_t &regAddress, uint16_t &data);
  uint8_t readRegister(uint8_t regaddress);
  uint16_t readRegisterWord(uint8_t regaddress);

};
#endif
