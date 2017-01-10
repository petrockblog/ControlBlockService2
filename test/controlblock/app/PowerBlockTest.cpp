#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "hal/DigitalOutMock.h"
#include "hal/DigitalInMock.h"
#include "app/PowerSwitch.h"

using ::testing::Return;

TEST(PowerBlockTest, Constructor)
{
    DigitalOutMock doMock;
    DigitalInMock diMock;

    EXPECT_CALL(doMock, configureDevice(IDigitalOut::DO_DEVICE_POWERSWITCH));
    EXPECT_CALL(doMock, setLevel(IDigitalOut::DO_CHANNEL_TOPOWERSWITCH, IDigitalOut::DO_LEVEL_HIGH, IDigitalOut::BOARD_0));
    PowerSwitch powerSwitch(diMock, doMock, PowerSwitch::SHUTDOWN_ACTIVATED);
    EXPECT_FALSE(powerSwitch.isShutdownInitiated());
}

TEST(PowerBlockTest, updateAndExpectShutdown)
{
    DigitalOutMock doMock;
    DigitalInMock diMock;
    PowerSwitch powerSwitch(diMock, doMock, PowerSwitch::SHUTDOWN_ACTIVATED);

    EXPECT_CALL(diMock, getLevel(IDigitalIn::DI_CHANNEL_FROMPOWERSWITCH, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_HIGH));

    powerSwitch.update();
    EXPECT_TRUE(powerSwitch.isShutdownInitiated());
}

TEST(PowerBlockTest, updateAndExpectNoShutdown)
{
    DigitalOutMock doMock;
    DigitalInMock diMock;
    PowerSwitch powerSwitch(diMock, doMock, PowerSwitch::SHUTDOWN_ACTIVATED);

    EXPECT_CALL(diMock, getLevel(IDigitalIn::DI_CHANNEL_FROMPOWERSWITCH, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_LOW));

    powerSwitch.update();
    EXPECT_FALSE(powerSwitch.isShutdownInitiated());
}
