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

#ifndef CONTROLBLOCKSERVICE2_IDIGITALIN_H
#define CONTROLBLOCKSERVICE2_IDIGITALIN_H

class IDigitalIn {
public:
    /**
     * Digital input channel identifiers
     */
    enum DI_Channel_e
    {
      DI_CHANNEL_FROMPOWERSWITCH = 0,
      DI_CHANNEL_P1_RIGHT,
      DI_CHANNEL_P1_LEFT,
      DI_CHANNEL_P1_UP,
      DI_CHANNEL_P1_DOWN,
      DI_CHANNEL_P1_SW1,
      DI_CHANNEL_P1_SW2,
      DI_CHANNEL_P1_SW3,
      DI_CHANNEL_P1_SW4,
      DI_CHANNEL_P1_SW5,
      DI_CHANNEL_P1_SW6,
      DI_CHANNEL_P1_SW7,
      DI_CHANNEL_P1_SW8,
      DI_CHANNEL_P1_START,
      DI_CHANNEL_P1_COIN,
      DI_CHANNEL_P1_A,
      DI_CHANNEL_P1_B,
      DI_CHANNEL_P2_RIGHT,
      DI_CHANNEL_P2_LEFT,
      DI_CHANNEL_P2_UP,
      DI_CHANNEL_P2_DOWN,
      DI_CHANNEL_P2_SW1,
      DI_CHANNEL_P2_SW2,
      DI_CHANNEL_P2_SW3,
      DI_CHANNEL_P2_SW4,
      DI_CHANNEL_P2_SW5,
      DI_CHANNEL_P2_SW6,
      DI_CHANNEL_P2_SW7,
      DI_CHANNEL_P2_SW8,
      DI_CHANNEL_P2_START,
      DI_CHANNEL_P2_COIN,
      DI_CHANNEL_P2_A,
      DI_CHANNEL_P2_B,
      DI_CHANNEL_P1_DATA,
      DI_CHANNEL_P2_DATA,
      DI_CHANNEL_SNES_RESET
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
    enum DI_Level_e
    {
      DI_LEVEL_LOW = 0,
      DI_LEVEL_HIGH
    };

    /**
     * Logical device identifiers for default configurations
     */
    enum DI_Device
    {
      DI_DEVICE_ALLIN = 0,   //!< Device with all ports set as input ports
      DI_DEVICE_POWERSWITCH,
      DI_DEVICE_SNES,        //!< SNES controller device
      DI_DEVICE_GENESIS,     //!< Genesis controller device
    };

    virtual void configureDevice(DI_Device mode) = 0;

    virtual DI_Level_e getLevel(DI_Channel_e channel, BoardNumber_e board = BOARD_0) = 0;
};
#endif //CONTROLBLOCKSERVICE2_IDIGITALIN_H
