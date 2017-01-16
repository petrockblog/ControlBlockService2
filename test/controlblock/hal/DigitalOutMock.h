#ifndef CONTROLBLOCKSERVICE2_DIGITALOUTMOCK_H
#define CONTROLBLOCKSERVICE2_DIGITALOUTMOCK_H

#include "gmock/gmock.h"  // Brings in Google Mock.
#include "hal/IDigitalOut.h"

class DigitalOutMock : public IDigitalOut {
public:
    MOCK_METHOD1(configureDevice, void(DO_Device device));
    MOCK_METHOD3(setLevel, void(DO_Channel_e channel, DO_Level_e level, BoardNumber_e board));
};

#endif //CONTROLBLOCKSERVICE2_DIGITALOUTMOCK_H
