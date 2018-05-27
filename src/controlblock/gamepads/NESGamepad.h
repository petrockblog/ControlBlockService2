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

#ifndef NESGAMEPAD_H
#define NESGAMEPAD_H

#include <stdint.h>
#include <uinput/IUInputFactory.h>
#include "hal/DigitalIO.h"
#include "InputDevice.h"

class NESGamepad: public InputDevice
{
public:
    /* bit masks for checking the button states for SNES controllers */
    static const uint16_t GPAD_NES_A = 0x01;
    static const uint16_t GPAD_NES_B = 0x02;
    static const uint16_t GPAD_NES_SELECT = 0x04;
    static const uint16_t GPAD_NES_START = 0x08;
    static const uint16_t GPAD_NES_UP = 0x10;
    static const uint16_t GPAD_NES_DOWN = 0x20;
    static const uint16_t GPAD_NES_LEFT = 0x40;
    static const uint16_t GPAD_NES_RIGHT = 0x80;
    static const uint16_t GPAD_NES_RESET = 0x1000;

    NESGamepad(IUInputFactory& uiFactoryRef, IDigitalIO& digitalIORef);
    ~NESGamepad() = default;

    virtual void initialize(InputDevice::Channel_e channel);
    virtual void update();

private:
    static const uint32_t STROBEDELAY_US = 4u;
    static const uint32_t NUMBER_OF_BUTTONS = 8u;

    static const IDigitalIO::DIO_Channel_e DIO_CHANNEL_P1_VCC = IDigitalIO::DIO_CHANNEL_P2_RIGHT;
    static const IDigitalIO::DIO_Channel_e DIO_CHANNEL_P2_VCC = IDigitalIO::DIO_CHANNEL_P2_LEFT;
    static const IDigitalIO::DIO_Channel_e DIO_CHANNEL_P1P2_STROBE = IDigitalIO::DIO_CHANNEL_P2_UP;
    static const IDigitalIO::DIO_Channel_e DIO_CHANNEL_P1P2_CLOCK = IDigitalIO::DIO_CHANNEL_P2_DOWN;
    static const IDigitalIO::DIO_Channel_e DIO_CHANNEL_P1_DATA = IDigitalIO::DIO_CHANNEL_P2_SW1;
    static const IDigitalIO::DIO_Channel_e DIO_CHANNEL_P2_DATA = IDigitalIO::DIO_CHANNEL_P2_SW2;

    IUInputFactory& uiFactory;
    IDigitalIO& digitalIO;

    bool isInitialized;
    InputDevice::Channel_e channel;
    IUInputDevice* gamepad;
    IUInputDevice* keyboard;

    uint16_t getNESControllerState();
};

#endif
