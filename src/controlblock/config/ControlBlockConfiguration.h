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

#include "IControlBlockConfiguration.h"

/**
 * This class models the user configuration of the ControlBlock
 */
class ControlBlockConfiguration: public IControlBlockConfiguration
{
public:
    /**
     * Constructor. Loads the information from the given configuration file.
     * It is assumed that the config file follows a certain JSON schema.
     * @param configFile - Path and file name of the configuration file
     */
    ControlBlockConfiguration();

    /**
     * Default destructor
     */
    ~ControlBlockConfiguration();

    /**
     * Loads the configuration from \ref CONFIGFILEPATH
     */
    virtual void loadConfiguration();

    /**
     * Returns the configuration for a given ControlBlock ID
     * @param controlBlockID - The ID of the ControlBlock
     * @return Reference to the configuration of the given ControlBlock ID
     */
    virtual SingleConfiguration& getConfiguration(int controlBlockID);

private:
    static const int MAX_CONTROLBLOCK_ID = 2u;

    const std::string CONFIGFILEPATH{"/etc/controlblockconfig.cfg"};

    bool hasLoadedConfiguration;

    SingleConfiguration* singleConfiguration[MAX_CONTROLBLOCK_ID];
};

#endif
