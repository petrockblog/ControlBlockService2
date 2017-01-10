#ifndef CONTROLBLOCKSERVICE2_UINPUTFACTORY_H
#define CONTROLBLOCKSERVICE2_UINPUTFACTORY_H

#include "IUInputFactory.h"
#include "IUInputDevice.h"

class UInputFactory : public IUInputFactory
{
public:
    virtual IUInputDevice* getUInputDevice(IUInputDevice::DeviceType type);

};

#endif //CONTROLBLOCKSERVICE2_UINPUTFACTORY_H
