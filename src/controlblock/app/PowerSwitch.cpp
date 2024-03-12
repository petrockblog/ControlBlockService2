/**
 * (c) Copyright 2017  Florian Mueller (contact@petrockblock.com)
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

#include <stdlib.h>
#include <fstream>
#include <regex>
#include <iostream>
#include "fmt/format.h"
#include "PowerSwitch.h"
#include "Logger.h"

PowerSwitch::PowerSwitch(IDigitalIO &digitalIOReference, ShutdownActivated doShutdownValue) : doShutdown(doShutdownValue),
                                                                                              isShutdownInitiatedValue(false),
                                                                                              digitalIO(digitalIOReference)
{
    digitalIO.configureDevice(IDigitalIO::DIO_DEVICE_POWERSWITCH);

    const bool kIsRPi5 = isRPi5();
    Logger::logMessage(fmt::format("Determined RPi model {}", kIsRPi5 ? ">=5" : "<5"));
    ::gpiod::chip chip(kIsRPi5 ? "gpiochip4" : "gpiochip0");

    powerSwitchIn_port_ = std::make_shared<::gpiod::line>(chip.get_line(18));
    powerSwitchIn_port_->request({"gpiochip0", ::gpiod::line_request::DIRECTION_INPUT, 0}, 0);

    powerSwitchOut_port_ = std::make_shared<::gpiod::line>(chip.get_line(17));
    setPowerSignal(PowerState::ON);

    Logger::logMessage(fmt::format("Created PowerSwitch. doShutdown: {}", doShutdownValue));
}

bool PowerSwitch::isRPi5()
{
    // Determine Raspberry Pi version
    std::ifstream cpuinfo("/proc/cpuinfo");
    std::string line;
    std::regex raspberryPiVersionPattern("Raspberry Pi 5");
    std::smatch match;
    bool isRaspberryPi5 = false;

    while (std::getline(cpuinfo, line))
    {        
        if (std::regex_search(line, match, raspberryPiVersionPattern))
        {
            isRaspberryPi5 = true;
            break;
        }
    }

    return isRaspberryPi5;
}

void PowerSwitch::update()
{
    if ((doShutdown == ShutdownActivated::ACTIVATED) && (getShutdownSignal() == ShutdownSignal::ACTIVATED) && (!isShutdownInitiatedValue))
    {
        const std::string kShutdownCommand{"/etc/controlblockswitchoff.sh &"};
        Logger::logMessage("Initiating shutdown. Calling");
        system(kShutdownCommand.c_str());
        isShutdownInitiatedValue = true;
    }
}

bool PowerSwitch::isShutdownInitiated() const
{
    return isShutdownInitiatedValue;
}

void PowerSwitch::setPowerSignal(PowerState state)
{
    if (state == PowerState::OFF)
    {
        powerSwitchOut_port_->request({"gpiochip0", ::gpiod::line_request::DIRECTION_OUTPUT, 0}, 0);
        Logger::logMessage("Disabled power signal.");
    }
    else
    {
        powerSwitchOut_port_->request({"gpiochip0", ::gpiod::line_request::DIRECTION_OUTPUT, 0}, 1);
        Logger::logMessage("Enabled power signal.");
    }
}

PowerSwitch::ShutdownSignal PowerSwitch::getShutdownSignal()
{
    ShutdownSignal signal;
    if (!powerSwitchIn_port_->get_value())
    {
        signal = ShutdownSignal::DEACTIVATED;
    }
    else
    {
        signal = ShutdownSignal::ACTIVATED;
    }
    return signal;
}
