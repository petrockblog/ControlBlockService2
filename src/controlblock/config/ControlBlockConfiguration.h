#ifndef CONTROLBLOCKCONFIGURATION_H
#define CONTROLBLOCKCONFIGURATION_H

#include <memory>
#include <assert.h>
#include <json/json.h>
#include "SingleConfiguration.h"

class ControlBlockConfiguration
{
public:
    enum GamepadType_e
    {
        GAMEPAD_ARCADE = 0,
        GAMEPAD_MAME,
        GAMEPAD_SNES,
        GAMEPAD_GENESIS,
        GAMEPAD_NONE
    };

    enum ShutdownType_e
    {
        SHUTDOWN_DEACTIVATED = 0,
        SHUTDOWN_ACTIVATED
    };

    static ControlBlockConfiguration& getInstance()
    {
        static ControlBlockConfiguration instance = ControlBlockConfiguration();
        return instance;
    }

    ~ControlBlockConfiguration();

    SingleConfiguration& getConfiguration(int controlBlockID);

private:
    static const int MAX_CONTROLBLOCK_ID = 2u;

    Json::Value root;   // will contains the root value after parsing.
    SingleConfiguration* singleConfiguration[MAX_CONTROLBLOCK_ID];


    ControlBlockConfiguration();
};

#endif
