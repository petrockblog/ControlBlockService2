#include "HALFactory.h"
#include <stddef.h>

HALFactory::HALFactory()
{
}

HALFactory::~HALFactory()
{
    for (auto i = 0u; i < MCPCHANNEL_NUMBERELEMENTS; ++i)
    {
        if (mcp23s17[i] != NULL)
        {
            mcp23s17[i]->end();
            delete mcp23s17[i];
            mcp23s17[i] = NULL;
        }
    }
}

MCP23S17PI& HALFactory::getMCP23S17(MCPChannel channel)
{
    if (channel == MCPCHANNEL_1)
    {
        if (mcp23s17[0] == NULL)
        {
            mcp23s17[0] = new MCP23S17PI(MCP23S17PI::CHIPSELECT_0, 0b000);
            mcp23s17[0]->begin();
        }
        return *mcp23s17[0];
    }
    else if (channel == MCPCHANNEL_2)
    {
        if (mcp23s17[1] == NULL)
        {
            mcp23s17[1] = new MCP23S17PI(MCP23S17PI::CHIPSELECT_0, 0b001);
            mcp23s17[1]->begin();
        }
        return *mcp23s17[1];
    }
    else if (channel == MCPCHANNEL_3)
    {
        if (mcp23s17[2] == NULL)
        {
            mcp23s17[2] = new MCP23S17PI(MCP23S17PI::CHIPSELECT_0, 0b010);
            mcp23s17[2]->begin();
        }
        return *mcp23s17[2];
    }
    else
    {
        if (mcp23s17[3] == NULL)
        {
            mcp23s17[3] = new MCP23S17PI(MCP23S17PI::CHIPSELECT_0, 0b011);
            mcp23s17[3]->begin();
        }
        return *mcp23s17[3];
    }
}
