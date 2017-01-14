#ifndef CONTROLBLOCKSERVICE2_IUINPUTFACTORY_H
#define CONTROLBLOCKSERVICE2_IUINPUTFACTORY_H

#include <memory>
#include "IUInputDevice.h"

class IUInputFactory
{
public:
    virtual std::unique_ptr<IUInputDevice> getUInputDevice(IUInputDevice::DeviceType type) = 0;
};

#endif //CONTROLBLOCKSERVICE2_IUINPUTFACTORY_H
