#ifndef CONTROLBLOCKSERVICE2_UINPUTDEVICEMOCK_H
#define CONTROLBLOCKSERVICE2_UINPUTDEVICEMOCK_H

#include "gmock/gmock.h"  // Brings in Google Mock.
#include "uinput/IUInputDevice.h"

class UInputDeviceMock : public IUInputDevice {
public:
    MOCK_METHOD3(setKeyState, void(uint16_t keycode, int16_t keyvalue, uint16_t evtype));
    MOCK_METHOD0(sync, void());
};

#endif //CONTROLBLOCKSERVICE2_UINPUTDEVICEMOCK_H
