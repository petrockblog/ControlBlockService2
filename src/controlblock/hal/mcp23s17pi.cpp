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

#include "mcp23s17pi.h"
#include <unistd.h>             //Needed for SPI port
#include <iostream>

bool MCP23S17PI::isBCM2835Initialized_ = false;
int MCP23S17PI::spi_cs0_fd_ = 0;

MCP23S17PI::MCP23S17PI(ChipSelectPin chipSelectPin, uint8_t deviceID) :
    deviceID_(deviceID),
    GPIOA_(0),
    GPIOB_(0),
    IODIRA_(0),
    IODIRB_(0),
    GPPUA_(0),
    GPPUB_(0) {
  writeRegister(MCP23S17PI_IOCON, IOCON_INIT);
}

MCP23S17PI::~MCP23S17PI() = default;

void MCP23S17PI::begin() {
  if (!isBCM2835Initialized_) {
    spi_cs0_fd_ = mcp23s17_open(0, 0);

    isBCM2835Initialized_ = true;
  }
}

void MCP23S17PI::setPinMode(uint8_t pin, Direction dir) {
  if (pin < 16) {
    uint8_t reg;
    uint8_t *data;

    if (pin < 8) {
      reg = MCP23S17PI_IODIRA;
      data = &IODIRA_;
    } else {
      reg = MCP23S17PI_IODIRB;
      pin &= 0x07;
      data = &IODIRB_;
    }

    if (DIR_INPUT == dir) {
      *data |= (1 << pin);
    } else {
      *data &= (~(1 << pin));
    }
    writeRegister(reg, *data);
  }
}

void MCP23S17PI::setPullupMode(uint8_t pin, Pullup mode) {
  if (pin < 16) {
    uint8_t reg;
    uint8_t *data;

    if (pin < 8) {
      reg = MCP23S17PI_GPPUA;
      data = &GPPUA_;
    } else {
      reg = MCP23S17PI_GPPUB;
      pin &= 0x07;
      data = &GPPUB_;
    }

    if (PULLUP_ENABLED == mode) {
      *data |= (1 << pin);
    } else {
      *data &= (~(1 << pin));
    }
    writeRegister(reg, *data);
  }
}

MCP23S17PI::Level MCP23S17PI::digitalRead(uint8_t pin) {
  if (pin < 8) {
    GPIOA_ = readRegister(MCP23S17PI_GPIOA);

    if ((GPIOA_ & (1 << pin)) != 0) {
      return LEVEL_HIGH;
    } else {
      return LEVEL_LOW;
    }
  } else if (pin < 16) {
    GPIOB_ = readRegister(MCP23S17PI_GPIOB);
    pin &= 0x07;
    if ((GPIOB_ & (1 << pin)) != 0) {
      return LEVEL_HIGH;
    } else {
      return LEVEL_LOW;
    }
  } else {
    throw std::runtime_error("Error while MCP23S17PI::digitalRead call.");
  }
}

void MCP23S17PI::digitalWrite(uint8_t pin, Level level) {
  if (pin < 16) {
    uint8_t reg;
    uint8_t *data;

    if (pin < 8) {
      reg = MCP23S17PI_GPIOA;
      data = &GPIOA_;
    } else {
      reg = MCP23S17PI_GPIOB;
      pin &= 0x07;
      data = &GPIOB_;
    }

    if (LEVEL_HIGH == level) {
      *data |= 1 << pin;
    } else {
      *data &= ~(1 << pin);
    }
    writeRegister(reg, *data);
  }
}

void MCP23S17PI::writeGPIO(uint16_t data) {
  writeRegisterWord(MCP23S17PI_GPIOA, data);
}

uint16_t MCP23S17PI::readGPIO() {
  return readRegisterWord(MCP23S17PI_GPIOA);
}

void MCP23S17PI::writeRegister(uint8_t regAddress, uint8_t data) {
  mcp23s17_write_reg(data, regAddress, deviceID_, spi_cs0_fd_);
}

void MCP23S17PI::writeRegisterWord(const uint8_t &regAddress, uint16_t &data) {
  writeRegister(regAddress, static_cast<uint8_t>(data));
  writeRegister(regAddress + 1u, static_cast<uint8_t>(data >> 8u));
}

uint8_t MCP23S17PI::readRegister(uint8_t regAddress) {
  return mcp23s17_read_reg(regAddress, deviceID_, spi_cs0_fd_);
}

uint16_t MCP23S17PI::readRegisterWord(uint8_t regAddress) {
  char buffer[2];

  buffer[0] = readRegister(regAddress);
  buffer[1] = readRegister(regAddress + 1);

  return (uint16_t)(((uint16_t)(buffer[1]) << 8) | (uint16_t) buffer[0]);
}

void MCP23S17PI::end() {
  close(spi_cs0_fd_);
}
