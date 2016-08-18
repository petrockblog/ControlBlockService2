#include <chrono>
#include <thread>
#include <iostream>
#include <linux/uinput.h>

#include "SNESGamepad.h"
#include "uinputcpp.h"

SNESGamepad::SNESGamepad() : channel(InputDevice::CHANNEL_UNDEFINED), uinp_fd(0)
{
}

SNESGamepad::~SNESGamepad()
{
    if(uinp_fd != 0)
    {
        UInputcpp::releaseHandle(uinp_fd);
    }
}

void SNESGamepad::initialize(InputDevice::Channel_e channel)
{
    DigitalIn::getInstance().configureDevice(DigitalIn::DI_DEVICE_SNES);
    DigitalOut::getInstance().configureDevice(DigitalOut::DO_DEVICE_SNES);

    uinp_fd = UInputcpp::getHandle();
    this->channel = channel;

    struct uinput_user_dev uinp;
    memset(&uinp, 0, sizeof(uinp));
    strncpy(uinp.name, "ControlBlock SNES Gamepad", strlen("ControlBlock SNES Gamepad"));
    uinp.id.version = 4;
    uinp.id.bustype = BUS_USB;
    uinp.id.product = 1;
    uinp.id.vendor = 1;

    // Setup the uinput device
    ioctl(uinp_fd, UI_SET_EVBIT, EV_KEY);
    ioctl(uinp_fd, UI_SET_EVBIT, EV_REL);
	for (int i = 0; i < 256; i++) {
		ioctl(uinp_fd, UI_SET_KEYBIT, i);
	}

    // gamepad, buttons
    ioctl(uinp_fd, UI_SET_KEYBIT, BTN_A);
    ioctl(uinp_fd, UI_SET_KEYBIT, BTN_B);
    ioctl(uinp_fd, UI_SET_KEYBIT, BTN_X);
    ioctl(uinp_fd, UI_SET_KEYBIT, BTN_Y);
    ioctl(uinp_fd, UI_SET_KEYBIT, BTN_TL);
    ioctl(uinp_fd, UI_SET_KEYBIT, BTN_TR);
    ioctl(uinp_fd, UI_SET_KEYBIT, BTN_START);
    ioctl(uinp_fd, UI_SET_KEYBIT, BTN_SELECT);

    // Add Absolute (D-pad) type
    ioctl(uinp_fd, UI_SET_EVBIT, EV_ABS);

    ioctl(uinp_fd, UI_SET_ABSBIT, ABS_X);
    ioctl(uinp_fd, UI_SET_ABSBIT, ABS_Y);

    // AXIS_MIN for left/up, AXIS_MAX for right/down
    ioctl(uinp_fd, UI_SET_EVBIT, EV_ABS);
    ioctl(uinp_fd, UI_SET_ABSBIT, ABS_X);
    ioctl(uinp_fd, UI_SET_ABSBIT, ABS_Y);
    uinp.absmin[ABS_X] = 0;
    uinp.absmax[ABS_X] = 4;
    uinp.absmin[ABS_Y] = 0;
    uinp.absmax[ABS_Y] = 4;

    /* Create input device into input sub-system */
    write(uinp_fd, &uinp, sizeof(uinp));
    if (ioctl(uinp_fd, UI_DEV_CREATE)) {
      printf("[SNESGamepad] Unable to create UINPUT device.");
      // throw -1;
    }

    UInputcpp::setKeyState(uinp_fd, ABS_X, 2, EV_ABS);
    UInputcpp::setKeyState(uinp_fd, ABS_Y, 2, EV_ABS);
    UInputcpp::sync(uinp_fd);

    DigitalOut dout = DigitalOut::getInstance();
    if (channel == InputDevice::CHANNEL_1)
    {
        dout.setLevel(DigitalOut::DO_CHANNEL_P1P2_STROBE, DigitalOut::DO_LEVEL_LOW);
        dout.setLevel(DigitalOut::DO_CHANNEL_P1P2_CLOCK, DigitalOut::DO_LEVEL_LOW);
        dout.setLevel(DigitalOut::DO_CHANNEL_P1_VCC, DigitalOut::DO_LEVEL_HIGH);
    }
    else
    {
        dout.setLevel(DigitalOut::DO_CHANNEL_P2_VCC, DigitalOut::DO_LEVEL_HIGH);
        // strobe and clock were already initialized with player 1 initialization.
    }
}

uint16_t SNESGamepad::getSNESControllerState()
{
    uint16_t state = 0u;

    DigitalIn din = DigitalIn::getInstance();
    DigitalOut dout = DigitalOut::getInstance();

    dout.setLevel(DigitalOut::DO_CHANNEL_P1P2_STROBE, DigitalOut::DO_LEVEL_HIGH);
    delayMicroseconds(2u * STROBEDELAY);
    dout.setLevel(DigitalOut::DO_CHANNEL_P1P2_STROBE, DigitalOut::DO_LEVEL_LOW);
    delayMicroseconds(STROBEDELAY);

    for(uint8_t i = 0u; i < 16u; i++)
    {
        DigitalIn::DI_Level_e curpin;
        if (channel == InputDevice::CHANNEL_1)
        {
            curpin = din.getLevel(DigitalIn::DI_CHANNEL_P1_DATA);
        }
        else
        {
            curpin = din.getLevel(DigitalIn::DI_CHANNEL_P2_DATA);
        }

        if(curpin == DigitalIn::DI_LEVEL_HIGH)
        {
            state |= (1u << i);
        }

        dout.setLevel(DigitalOut::DO_CHANNEL_P1P2_CLOCK, DigitalOut::DO_LEVEL_HIGH);
        delayMicroseconds(STROBEDELAY);
        dout.setLevel(DigitalOut::DO_CHANNEL_P1P2_CLOCK, DigitalOut::DO_LEVEL_LOW);
        delayMicroseconds(STROBEDELAY);
    }

    return state;
}

void SNESGamepad::update()
{
    DigitalIn di = DigitalIn::getInstance();
    DigitalIn::DI_Level_e resetLevel = di.getLevel(DigitalIn::DI_CHANNEL_P2_B);
    UInputcpp::setKeyState(uinp_fd, KEY_ESC, resetLevel == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);

    uint16_t state = getSNESControllerState();

    // left-right axis
    if((state & GPAD_SNES_LEFT) == GPAD_SNES_LEFT)
    {
        UInputcpp::setKeyState(uinp_fd, ABS_X, 0, EV_ABS);
    }
    else if((state & GPAD_SNES_RIGHT) == GPAD_SNES_RIGHT)
    {
        UInputcpp::setKeyState(uinp_fd, ABS_X, 4, EV_ABS);
    }
    else
    {
        UInputcpp::setKeyState(uinp_fd, ABS_X, 2, EV_ABS);
    }

    // up-down axis
    if((state & GPAD_SNES_UP) == GPAD_SNES_UP)
    {
        UInputcpp::setKeyState(uinp_fd, ABS_Y, 0, EV_ABS);
    }
    else if((state & GPAD_SNES_DOWN) == GPAD_SNES_DOWN)
    {
        UInputcpp::setKeyState(uinp_fd, ABS_Y, 4, EV_ABS);
    }
    else
    {
        UInputcpp::setKeyState(uinp_fd, ABS_Y, 2, EV_ABS);
    }

    // buttons
    UInputcpp::setKeyState(uinp_fd, BTN_A, (state & GPAD_SNES_A) == GPAD_SNES_A ? 1 : 0, EV_KEY);
    UInputcpp::setKeyState(uinp_fd, BTN_B, (state & GPAD_SNES_B) == GPAD_SNES_B ? 1 : 0, EV_KEY);
    UInputcpp::setKeyState(uinp_fd, BTN_X, (state & GPAD_SNES_X) == GPAD_SNES_X ? 1 : 0, EV_KEY);
    UInputcpp::setKeyState(uinp_fd, BTN_Y, (state & GPAD_SNES_Y) == GPAD_SNES_Y ? 1 : 0, EV_KEY);
    UInputcpp::setKeyState(uinp_fd, BTN_TL, (state & GPAD_SNES_L) == GPAD_SNES_L ? 1 : 0, EV_KEY);
    UInputcpp::setKeyState(uinp_fd, BTN_TR, (state & GPAD_SNES_R) == GPAD_SNES_R ? 1 : 0, EV_KEY);
    UInputcpp::setKeyState(uinp_fd, BTN_START, (state & GPAD_SNES_START) == GPAD_SNES_START ? 1 : 0,
                           EV_KEY);
    UInputcpp::setKeyState(uinp_fd, BTN_SELECT, (state & GPAD_SNES_SELECT) == GPAD_SNES_SELECT ? 1 : 0,
                           EV_KEY);

    UInputcpp::sync(uinp_fd);
}
