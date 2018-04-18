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

#ifndef CONTROLBLOCKSERVICE2_IDIGITALIO_H
#define CONTROLBLOCKSERVICE2_IDIGITALIO_H

#include "hal/mcp23s17pi.h"

class IDigitalIO {
public:
    /**
     * Digital input channel identifiers
     */
    enum DIO_Channel_e
    {
      DIO_CHANNEL_P1_RIGHT = 0,
      DIO_CHANNEL_P1_LEFT,
      DIO_CHANNEL_P1_UP,
      DIO_CHANNEL_P1_DOWN,
      DIO_CHANNEL_P1_SW1,
      DIO_CHANNEL_P1_SW2,
      DIO_CHANNEL_P1_SW3,
      DIO_CHANNEL_P1_SW4,
      DIO_CHANNEL_P1_SW5,
      DIO_CHANNEL_P1_SW6,
      DIO_CHANNEL_P1_SW7,
      DIO_CHANNEL_P1_SW8,
      DIO_CHANNEL_P1_START,
      DIO_CHANNEL_P1_COIN,
      DIO_CHANNEL_P1_A,
      DIO_CHANNEL_P1_B,
      DIO_CHANNEL_P2_RIGHT,
      DIO_CHANNEL_P2_LEFT,
      DIO_CHANNEL_P2_UP,
      DIO_CHANNEL_P2_DOWN,
      DIO_CHANNEL_P2_SW1,
      DIO_CHANNEL_P2_SW2,
      DIO_CHANNEL_P2_SW3,
      DIO_CHANNEL_P2_SW4,
      DIO_CHANNEL_P2_SW5,
      DIO_CHANNEL_P2_SW6,
      DIO_CHANNEL_P2_SW7,
      DIO_CHANNEL_P2_SW8,
      DIO_CHANNEL_P2_START,
      DIO_CHANNEL_P2_COIN,
      DIO_CHANNEL_P2_A,
      DIO_CHANNEL_P2_B,
      DIO_CHANNEL_FROMPOWERSWITCH,
      DIO_CHANNEL_TOPOWERSWITCH,
      DIO_CHANNEL_GENESIS_P1_SELECT,  //!< Select signal for Genesis controller, player 1
      DIO_CHANNEL_GENESIS_P2_SELECT,  //!< Select signal for Genesis controller, player 2

    };

    /**
     * Board identifiers in case of several stacked ControlBLocks
     */
    enum BoardNumber_e
    {
      BOARD_0 = 0,//!< BOARD_0
      BOARD_1     //!< BOARD_1
    };

    /**
     * Logical input level identifiers
     */
    enum DIO_Level_e
    {
      DIO_LEVEL_LOW = 0,
      DIO_LEVEL_HIGH
    };

    /**
     * Logical device identifiers for default configurations
     */
    enum DIO_Device
    {
      DIO_DEVICE_ALLIN = 0,   //!< Device with all ports set as input ports
      DIO_DEVICE_POWERSWITCH, //!< PowerBlock communication pins
      DIO_DEVICE_SNES,        //!< SNES controller device
      DIO_DEVICE_GENESIS,     //!< Genesis controller device
    };

    static const uint8_t TOTAL_NUMBER_OF_CHANNELS = 16u;

    virtual void configureDevice(DIO_Device mode) = 0;

    virtual DIO_Level_e getLevel(DIO_Channel_e channel) = 0;

      /**
     * @brief Sets a logical signal level of a given channel
     *
     * @param channel The channel whose signal level should be set
     * @param level The signal level to be set
     */
    virtual void setLevel(DIO_Channel_e channel, DIO_Level_e level) = 0;

};

#endif //CONTROLBLOCKSERVICE2_IDIGITALIO_H
