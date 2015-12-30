#ifndef HALFACTORY_H
#define HALFACTORY_H

#include "mcp23s17pi.h"

class HALFactory
{
public:
    enum MCPChannel
    {
        MCPCHANNEL_1 = 0,
        MCPCHANNEL_2,

        MCPCHANNEL_NUMBERELEMENTS
    };

    ~HALFactory();

    static HALFactory& getInstance()
    {
        static HALFactory halFactory = HALFactory();
        return halFactory;
    }

    MCP23S17PI& getMCP23S17(MCPChannel channel);

private:
    HALFactory();

    MCP23S17PI* mcp23s17[MCPCHANNEL_NUMBERELEMENTS];
};

#endif  // HALFACTORY_H