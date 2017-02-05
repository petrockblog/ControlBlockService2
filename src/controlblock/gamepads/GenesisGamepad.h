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

#ifndef CONTROLBLOCKSERVICE2_GENESISGAMEPAD_H
#define CONTROLBLOCKSERVICE2_GENESISGAMEPAD_H

#include <memory>
#include "InputDevice.h"
#include "uinput/IUInputDevice.h"
#include "uinput/IUInputFactory.h"
#include "hal/IDigitalIn.h"
#include "hal/IDigitalOut.h"

/**
 * Models a Genesis/Megadrive gamepad. Polls the controller and sends the corresponding
 * user inputs to the uinput device.
 */
class GenesisGamepad: public InputDevice
{
public:
    /**
     * Constructor
     * @param uiFactory
     * @param digitalInRef
     * @param digitalOutRef
     */
    GenesisGamepad(IUInputFactory& uiFactory, IDigitalIn& digitalInRef, IDigitalOut& digitalOutRef);

    /**
     * Default Destructor
     */
    virtual ~GenesisGamepad() = default;

    /**
     * Implements \ref InputDevice::initialize
     */
    virtual void initialize(InputDevice::Channel_e channel);

    /**
     * Implement \ref InputDevice::update()
     */
    virtual void update();

private:
    struct Input
    {
        int player;
        IDigitalIn::DI_Channel_e inputChannel;
        int lowFlag;
        int highFlag;
        int pulse3Flag;
    };

    // Controller Button Flags
    static const uint32_t ON = 1u;
    static const uint32_t UP = (1u << 1);
    static const uint32_t DOWN = (1u << 2);
    static const uint32_t LEFT = (1u << 3);
    static const uint32_t RIGHT = (1u << 4);
    static const uint32_t START = (1u << 5);
    static const uint32_t A = (1u << 6);
    static const uint32_t B = (1u << 7);
    static const uint32_t C = (1u << 8);
    static const uint32_t X = (1u << 9);
    static const uint32_t Y = (1u << 10);
    static const uint32_t Z = (1u << 11);
    static const uint32_t MODE = (1u << 12);

    static const IDigitalOut::DO_Channel_e CHN_SELECT[];
    static const Input inputMap[];

    InputDevice::Channel_e channel;
    std::unique_ptr<IUInputDevice> gamepad;
    IDigitalIn& digitalIn;
    IDigitalOut& digitalOut;

    bool isInSixButtonMode;
    uint32_t currentState;
    uint32_t lastState;
    IDigitalIn::BoardNumber_e boardIn;
    IDigitalOut::BoardNumber_e boardOut;
    uint32_t playerIndex;

    void readButtons();
    void resetState();
    void read3buttons(int player);
    void read6buttons(int player);
    void sendStates();
};

#endif //CONTROLBLOCKSERVICE2_GENESISGAMEPAD_H
