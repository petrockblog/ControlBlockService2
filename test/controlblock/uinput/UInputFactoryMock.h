#ifndef CONTROLBLOCKSERVICE2_UINPUTFACTORYMOCK_H
#define CONTROLBLOCKSERVICE2_UINPUTFACTORYMOCK_H

#include "gmock/gmock.h"  // Brings in Google Mock.
#include "uinput/IUInputFactory.h"

class UInputFactoryMock : public IUInputFactory
{
public:
    UInputFactoryMock() { }
    virtual ~UInputFactoryMock() { }

    virtual std::unique_ptr<IUInputDevice> getUInputDevice(IUInputDevice::DeviceType type)
    {
        return std::unique_ptr<IUInputDevice>(getUInputDeviceProxy(type));
    }

    MOCK_METHOD1(getUInputDeviceProxy, IUInputDevice*(IUInputDevice::DeviceType type));
};

#endif //CONTROLBLOCKSERVICE2_UINPUTFACTORYMOCK_H
