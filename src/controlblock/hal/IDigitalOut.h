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

#ifndef CONTROLBLOCKSERVICE2_IDIGITALOUT_H
#define CONTROLBLOCKSERVICE2_IDIGITALOUT_H

class IDigitalOut
{
public:
    /**
 * Digital output channel identifiers
 */
    enum DO_Channel_e
    {
        DO_CHANNEL_TOPOWERSWITCH = 0,  //!< Status signal to power switch uC
        DO_CHANNEL_P1P2_STROBE,        //!< Strobe/latch signal for SNES controller
        DO_CHANNEL_P1P2_CLOCK,         //!< Clock signal for SNES controller
        DO_CHANNEL_P1_VCC,             //!< Supply voltage for SNES controller, player 1
        DO_CHANNEL_P2_VCC,             //!< Supply voltage for SNES controller, player 2
        DO_CHANNEL_GENESIS_P1_SELECT,  //!< Select signal for Genesis controller, player 1
        DO_CHANNEL_GENESIS_P2_SELECT,  //!< Select signal for Genesis controller, player 2
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
     * Logical output level identifiers
     */
    enum DO_Level_e
    {
        DO_LEVEL_LOW = 0,  //!< Logical low
        DO_LEVEL_HIGH      //!< Logical high
    };

    /**
     * Logical device identifiers
     */
    enum DO_Device
    {
        DO_DEVICE_POWERSWITCH = 0,  //!< Power switch device
        DO_DEVICE_SNES,             //!< SNES controller device
        DO_DEVICE_GENESIS,          //!< Genesis controller device
    };

    virtual void configureDevice(DO_Device device) = 0;

    /**
     * @brief Sets a logical signal level of a given channel
     *
     * @param channel The channel whose signal level should be set
     * @param level The signal level to be set
     */
    virtual void setLevel(DO_Channel_e channel, DO_Level_e level, BoardNumber_e board = BOARD_0) = 0;
};

#endif //CONTROLBLOCKSERVICE2_IDIGITALOUT_H
