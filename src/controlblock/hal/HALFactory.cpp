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

#include "HALFactory.h"
#include <stddef.h>

HALFactory::HALFactory() : mcp23s17_1(MCP23S17PI::CHIPSELECT_0, 0b000), 
                        mcp23s17_2(MCP23S17PI::CHIPSELECT_0, 0b001), 
                        mcp23s17_3(MCP23S17PI::CHIPSELECT_0, 0b010), 
                        mcp23s17_4(MCP23S17PI::CHIPSELECT_0, 0b011)
{
}

void HALFactory::initialize()
{
    MCP23S17PI::begin();
}

void HALFactory::deinitialize()
{
    MCP23S17PI::end();
}

HALFactory::~HALFactory()
{
}

MCP23S17PI* HALFactory::getMCP23S17(MCPChannel channel)
{
    if (channel == MCPCHANNEL_1) {
        return &mcp23s17_1;
    }
    else if (channel == MCPCHANNEL_2) {
        return &mcp23s17_2;
    }
    else if (channel == MCPCHANNEL_3) {
        return &mcp23s17_3;
    }
    else {
        return &mcp23s17_4;
    }
}
