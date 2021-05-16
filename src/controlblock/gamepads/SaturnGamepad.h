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

#ifndef CONTROLBLOCKSERVICE2_SATURNGAMEPAD_H
#define CONTROLBLOCKSERVICE2_SATURNGAMEPAD_H

#include <memory>
#include "InputDevice.h"
#include "uinput/IUInputDevice.h"
#include "uinput/IUInputFactory.h"
#include "hal/IDigitalIO.h"

/**
 * Models a Sega Saturn gamepad. Polls the controller and sends the corresponding
 * user inputs to the uinput device.
 */
class SaturnGamepad: public InputDevice
{
public:
    /**
     * Constructor
     * @param uiFactory
     * @param digitalInRef
     * @param digitalOutRef
     */
    SaturnGamepad(IUInputFactory& uiFactory, IDigitalIO& digitalIORef);

    /**
     * Default Destructor
     */
    virtual ~SaturnGamepad() = default;

    /**
     * Implements \ref InputDevice::initialize
     */
    void initialize(InputDevice::Channel_e channel) override;

    /**
     * Implement \ref InputDevice::update()
     */
    void update() override;

private:
    struct Input
    {
        int player;
        IDigitalIO::DIO_Channel_e inputChannel;
        int lowFlag;
        int highFlag;
        int pulse3Flag;
    };

    // Controller Button Flags
    static const uint32_t UP    = 0x0001;
    static const uint32_t DOWN  = 0x0002;
    static const uint32_t LEFT  = 0x0004;
    static const uint32_t RIGHT = 0x0008;
    static const uint32_t START = 0x0010;
    static const uint32_t A     = 0x0020;
    static const uint32_t B     = 0x0040;
    static const uint32_t C     = 0x0080;
    static const uint32_t X     = 0x0100;
    static const uint32_t Y     = 0x0200;
    static const uint32_t Z     = 0x0400;
    static const uint32_t LT    = 0x0800;
    static const uint32_t RT    = 0x1000;

    static const IDigitalIO::DIO_Channel_e CHN_SELECT0[];
    static const IDigitalIO::DIO_Channel_e CHN_SELECT1[];
    // static const Input inputMap[];

    static const uint32_t SHORTDELAY = 20u;
    static const uint32_t LONGDELAY = 1000u;

    InputDevice::Channel_e channel;
    IUInputDevice* gamepad;
    IDigitalIO& digitalIO;

    uint32_t currentState;
    uint32_t lastState;
    uint32_t playerIndex;

    void readButtons();
    void resetState();
    // void read3buttons(int player);
    void sendStates();
};

#endif //CONTROLBLOCKSERVICE2_SATURNGAMEPAD_H
