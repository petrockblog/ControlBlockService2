#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>

#include "ControlBlockConfiguration.h"

const std::string ControlBlockConfiguration::CONFIGFILEPATH = "/usr/local/etc/controlblockconfig.cfg";

ControlBlockConfiguration::ControlBlockConfiguration()
{
    try
    {
        Json::Reader reader;

        std::ifstream configStream(CONFIGFILEPATH);
        std::string config_doc((std::istreambuf_iterator<char>(configStream)),
                std::istreambuf_iterator<char>());

        bool parsingSuccessful = reader.parse(config_doc, root);
        if (!parsingSuccessful)
        {
            // report to the user the failure and their locations in the document.
            std::cout << "Failed to parse configuration\n" << reader.getFormattedErrorMessages();
            throw(1);
        }

        singleConfiguration[0] = new SingleConfiguration(
                root["controlblocks"][0]["enabled"].asBool(),
                root["controlblocks"][0]["address"]["SJ2"].asInt() << 2 || root["controlblocks"][0]["address"]["SJ1"].asInt() << 1,
                root["controlblocks"][0]["gamepadtype"].asString(),
                root["controlblocks"][0]["powerswitchOn"].asBool(),
                root["controlblocks"][0]["onlyOneGamepad"].asBool()
            );
        singleConfiguration[1] = new SingleConfiguration(
                root["controlblocks"][1]["enabled"].asBool(),
                root["controlblocks"][1]["address"]["SJ2"].asInt() << 2 || root["controlblocks"][1]["address"]["SJ1"].asInt() << 1,
                root["controlblocks"][1]["gamepadtype"].asString(),
                root["controlblocks"][1]["powerswitchOn"].asBool(),
                root["controlblocks"][1]["onlyOneGamepad"].asBool()
            );
    }
    catch (int errno)
    {
        std::cout << "Error while initializing ControlBlockConfiguration instance. Error number: " << errno
                << std::endl;
    }
}

ControlBlockConfiguration::~ControlBlockConfiguration()
{
    for (int index = 0; index < MAX_CONTROLBLOCK_ID; index++)
    {
        if (singleConfiguration[0] != NULL)
        {
            delete singleConfiguration[0];
        }
    }
}

SingleConfiguration& ControlBlockConfiguration::getConfiguration(int controlBlockID)
{
    assert(controlBlockID < MAX_CONTROLBLOCK_ID);

    return *singleConfiguration[controlBlockID];
}

