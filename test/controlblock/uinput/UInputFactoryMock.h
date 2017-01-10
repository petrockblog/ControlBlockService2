#ifndef CONTROLBLOCKSERVICE2_UINPUTFACTORYMOCK_H
#define CONTROLBLOCKSERVICE2_UINPUTFACTORYMOCK_H

#include "gmock/gmock.h"  // Brings in Google Mock.
#include "uinput/IUInputFactory.h"

class UInputFactoryMock : public IUInputFactory {
public:
    MOCK_METHOD1(getUInputDevice, IUInputDevice*(IUInputDevice::DeviceType type));
};

#endif //CONTROLBLOCKSERVICE2_UINPUTFACTORYMOCK_H
