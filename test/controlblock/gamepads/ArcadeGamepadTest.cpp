#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "uinput/UInputDeviceMock.h"
#include "uinput/UInputFactoryMock.h"
#include "hal/DigitalInMock.h"
#include "gamepads/ArcadeGamepad.h"

using ::testing::Return;

TEST(ArcadeGamepadTest, Constructor)
{
    UInputFactoryMock uiFactory;
    DigitalInMock di;

    EXPECT_CALL(uiFactory, getUInputDevice(IUInputDevice::TYPE_GAMEPAD_ARCADE));
    ArcadeGamepad gamepad(uiFactory, di);
}

TEST(ArcadeGamepadTest, initialize)
{
    UInputFactoryMock uiFactory;
    DigitalInMock di;
    ArcadeGamepad gamepad(uiFactory, di);

    EXPECT_CALL(di, configureDevice(IDigitalIn::DI_DEVICE_ALLIN));
    gamepad.initialize(InputDevice::CHANNEL_1);
}

TEST(ArcadeGamepadTest, update)
{
    UInputFactoryMock uiFactory;
    DigitalInMock di;
    UInputDeviceMock gamepadMock;

    EXPECT_CALL(uiFactory, getUInputDevice(IUInputDevice::TYPE_GAMEPAD_ARCADE)).WillOnce(Return(&gamepadMock));
    ArcadeGamepad gamepad(uiFactory, di);
    gamepad.initialize(InputDevice::CHANNEL_1);

    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_LEFT, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_HIGH));
    EXPECT_CALL(gamepadMock, setKeyState(ABS_Y, 0, EV_ABS));

    EXPECT_CALL(di, getLevel(IDigitalIn::DI_CHANNEL_P1_UP, IDigitalIn::BOARD_0)).WillOnce(Return(IDigitalIn::DI_LEVEL_HIGH));
    EXPECT_CALL(gamepadMock, setKeyState(ABS_X, 4, EV_ABS));

    gamepad.update();
}