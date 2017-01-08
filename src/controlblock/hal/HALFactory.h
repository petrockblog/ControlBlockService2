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

    /**
     * Returns the singleton instance that corresponds to
     * the given channel
     * @param channel - The channel whose MCP instance should be returned
     * @return Reference to the MCP instance
     */
    MCP23S17PI& getMCP23S17(MCPChannel channel);

private:
    HALFactory();

    MCP23S17PI* mcp23s17[MCPCHANNEL_NUMBERELEMENTS];
};

#endif  // HALFACTORY_H
