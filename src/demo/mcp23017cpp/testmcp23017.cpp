#include "../../controlblock/mcp23s17pi.h"
#include <stdio.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    MCP23S17PI mcp1(MCP23S17PI::CHIPSELECT_0, 0b000);
    MCP23S17PI mcp2(MCP23S17PI::CHIPSELECT_0, 0b001);

    mcp1.begin();
    mcp2.begin();

    for (uint8_t i = 0; i < 16; i++) {
        // mcp1.setPinMode(i, MCP23S17PI::DIR_OUTPUT);
        // mcp2.setPinMode(i, MCP23S17PI::DIR_OUTPUT);

    	mcp1.setPinMode(i, MCP23S17PI::DIR_INPUT);
    	mcp2.setPinMode(i, MCP23S17PI::DIR_INPUT);
    	mcp1.setPullupMode(i, MCP23S17PI::PULLUP_ENABLED);
    	mcp2.setPullupMode(i, MCP23S17PI::PULLUP_ENABLED);
    }

    while (true)
    {
    //     mcp1.writeGPIO(0xFFFF);
    // 	mcp2.writeGPIO(0x0000);
    //     mcp1.writeGPIO(0x0000);
	   // mcp2.writeGPIO(0xFFFF);
    	for (uint8_t index=0; index<16; index++)
    	{
    	    if (mcp1.digitalRead(index) == MCP23S17PI::LEVEL_LOW) cout << "A, pressed " << unsigned(index) << endl;
    	}
    	for (uint8_t index=0; index<16; index++)
        {
            if (mcp2.digitalRead(index) == MCP23S17PI::LEVEL_LOW) cout << "B, pressed " << unsigned(index) << endl;
        }
        delayMicroseconds(500000);
    }

    mcp1.end();
    mcp2.end();

    return 0;
}
