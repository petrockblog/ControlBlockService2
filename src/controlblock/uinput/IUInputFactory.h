#ifndef CONTROLBLOCKSERVICE2_IUINPUTFACTORY_H
#define CONTROLBLOCKSERVICE2_IUINPUTFACTORY_H

#include "IUInputDevice.h"

class IUInputFactory
{
public:
    virtual IUInputDevice* getUInputDevice(IUInputDevice::DeviceType type) = 0;
};

#endif //CONTROLBLOCKSERVICE2_IUINPUTFACTORY_H
