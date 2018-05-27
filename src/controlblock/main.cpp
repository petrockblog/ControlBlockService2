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

#include <stdio.h>
#include <iostream>
#include <thread>
#include <bcm2835.h>
#include <signal.h>
#include "hal/mcp23s17pi.h"

#include "app/ControlBlock.h"
#include "config/ControlBlockConfiguration.h"
#include "uinput/UInputFactory.h"
#include "gamepads/GamepadFactory.h"

static volatile sig_atomic_t doRun = 1;

extern "C" {
void sig_handler(int signo)
{
    if ((signo == SIGINT) || (signo == SIGQUIT) || (signo == SIGABRT) || (signo == SIGTERM)) {
        printf("[ControlBlockService] Releasing input devices.\n");
        doRun = 0;
    }
}
}

void register_signalhandlers()
{
    /* Register signal handlers  */
    if (signal(SIGINT, sig_handler) == SIG_ERR) {
        printf("\n[ControlBlockService] Cannot catch SIGINT\n");
    }
    if (signal(SIGQUIT, sig_handler) == SIG_ERR) {
        printf("\n[ControlBlockService] Cannot catch SIGQUIT\n");
    }
    if (signal(SIGABRT, sig_handler) == SIG_ERR) {
        printf("\n[ControlBlockService] Cannot catch SIGABRT\n");
    }
    if (signal(SIGTERM, sig_handler) == SIG_ERR) {
        printf("\n[ControlBlockService] Cannot catch SIGTERM\n");
    }
}

int main(int argc, char** argv)
{
    register_signalhandlers();
    MCP23S17PI::begin();

    try {
        UInputFactory uiFactory;
        ControlBlockConfiguration config;
        GamepadFactory gamepadFactory(uiFactory);

        ControlBlock controlBlock{uiFactory, config, gamepadFactory};
        
        std::cout << "[ControlBlockService] Starting gamepad polling ... " << std::endl;
        while (doRun) {
            controlBlock.update();
            std::this_thread::sleep_for(std::chrono::milliseconds(25));
        }
    }
    catch (int errno) {
        std::cout << "Error while running main loop. Error number: " << errno << std::endl;
    }

    MCP23S17PI::end();

    return 0;
}
