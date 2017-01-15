#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "uinput/UInputDeviceMock.h"
#include "uinput/UInputFactoryMock.h"
#include "hal/DigitalInMock.h"
#include "hal/DigitalOutMock.h"
#include "gamepads/GenesisGamepad.h"

using ::testing::Return;
using ::testing::NiceMock;

TEST(GenesisGamepadTest, Constructor)
{
    UInputFactoryMock uiFactory;
    DigitalInMock di;
    DigitalOutMock digitalOut;

    EXPECT_CALL(uiFactory, getUInputDeviceProxy(IUInputDevice::TYPE_GAMEPAD_GENESIS));
    GenesisGamepad gamepad(uiFactory, di, digitalOut);
}

