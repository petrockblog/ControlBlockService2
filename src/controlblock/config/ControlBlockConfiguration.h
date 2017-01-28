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

#ifndef CONTROLBLOCKCONFIGURATION_H
#define CONTROLBLOCKCONFIGURATION_H

#include <assert.h>
#include <json/json.h>
#include "SingleConfiguration.h"

class ControlBlockConfiguration
{
public:
    enum ShutdownType_e
    {
      SHUTDOWN_DEACTIVATED = 0, SHUTDOWN_ACTIVATED
    };

    /**
     * Constructor. Loads the information from the given configuration file.
     * It is assumed that the config file follows a certain JSON schema.
     * @param configFile - Path and file name of the configuration file
     */
    ControlBlockConfiguration(std::string configFile);

    /**
     * Default destructor
     */
    ~ControlBlockConfiguration();

    SingleConfiguration& getConfiguration(int controlBlockID);

private:
    static const int MAX_CONTROLBLOCK_ID = 2u;

    Json::Value root;   // will contains the root value after parsing.
    SingleConfiguration* singleConfiguration[MAX_CONTROLBLOCK_ID];
};

#endif
