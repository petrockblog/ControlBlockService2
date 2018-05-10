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

#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

/**
 * Interface for an input device supported by the ControlBlock
 */
class InputDevice
{
public:
    /**
     * Gamepad types
     */
    enum GamepadType_e
    {
        GAMEPAD_ARCADE = 0,  //!< Arcade gamepad type
        GAMEPAD_MAME,        //!< MAME gamepad type
        GAMEPAD_SNES,        //!< SNES gamepad type
        GAMEPAD_NES,        //!< SNES gamepad type
        GAMEPAD_GENESIS,     //!< Genesis gamepad type
        GAMEPAD_NONE         //!< Neutral gamepad type
    };

    /**
     * Channel identifiers
     */
    enum Channel_e
    {
        CHANNEL_1 = 0,     //!< Channel 1
        CHANNEL_2,         //!< Channel 2
        CHANNEL_3,         //!< Channel 3
        CHANNEL_4,         //!< Channel 4
        CHANNEL_UNDEFINED  //!< Undefined channel
    };

    /**
     * Initializes the input and output interfaces specifically for the gamepad type
     * and the given channel
     * @param channel - THe channel for which the gamepad should be initialized
     */
    virtual void initialize(Channel_e channel) = 0;

    /**
     * Update the gamepad state.
     */
    virtual void update() = 0;
};

#endif
