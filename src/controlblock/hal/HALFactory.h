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

#ifndef HALFACTORY_H
#define HALFACTORY_H

#include "hal/mcp23s17pi.h"

class HALFactory
{
public:
    /**
     * Indicates individual MCP components
     */
    enum MCPChannel
    {
        MCPCHANNEL_1 = 0, //!< MCPCHANNEL_1
        MCPCHANNEL_2,     //!< MCPCHANNEL_2
        MCPCHANNEL_3,     //!< MCPCHANNEL_3
        MCPCHANNEL_4,     //!< MCPCHANNEL_4

        MCPCHANNEL_NUMBERELEMENTS
    };

    /**
     * Destructor
     */
    ~HALFactory();

    /**
     * Returns a singleton instance of the HAL factory
     * @return
     */
    static HALFactory& getInstance()
    {
        static HALFactory halFactory = HALFactory();
        return halFactory;
    }

    static void initialize();

    static void deinitialize();

    /**
     * Returns the singleton instance that corresponds to
     * the given channel
     * @param channel - The channel whose MCP instance should be returned
     * @return Reference to the MCP instance
     */
    MCP23S17PI* getMCP23S17(MCPChannel channel);

private:
    HALFactory();

    MCP23S17PI mcp23s17_1;
    MCP23S17PI mcp23s17_2;
    MCP23S17PI mcp23s17_3;
    MCP23S17PI mcp23s17_4;
};

#endif  // HALFACTORY_H
