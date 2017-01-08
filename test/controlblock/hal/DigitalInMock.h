#ifndef CONTROLBLOCKSERVICE2_DIGITALINMOCK_H
#define CONTROLBLOCKSERVICE2_DIGITALINMOCK_H

#include "gmock/gmock.h"  // Brings in Google Mock.
#include "hal/DigitalIn.h"

class DigitalInMock : public IDigitalIn {
public:
    MOCK_METHOD1(configureDevice, void(DI_Device mode));
    MOCK_METHOD2(getLevel, DI_Level_e(DI_Channel_e channel, BoardNumber_e board));
};

#endif //CONTROLBLOCKSERVICE2_DIGITALINMOCK_H
