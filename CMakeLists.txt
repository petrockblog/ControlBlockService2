cmake_minimum_required(VERSION 2.8.5)

project(ControlBlockService2)

set(CMAKE_CXX_STANDARD 11)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        ${SOURCE_FILES}
        src/controlblock/gamepads/ArcadeGamepad.cpp
        src/controlblock/gamepads/ArcadeGamepad.h
        src/controlblock/app/ControlBlock.cpp
        src/controlblock/app/ControlBlock.h
        src/controlblock/config/ControlBlockConfiguration.cpp
        src/controlblock/config/ControlBlockConfiguration.h
        src/controlblock/hal/DigitalIn.cpp
        src/controlblock/hal/DigitalIn.h
        src/controlblock/hal/DigitalOut.cpp
        src/controlblock/hal/DigitalOut.h
        src/controlblock/hal/HALFactory.cpp
        src/controlblock/hal/HALFactory.h
        src/controlblock/gamepads/InputDevice.h
        src/controlblock/config/ISingleConfiguration.h
        src/controlblock/app/main.cpp
        src/controlblock/gamepads/MAMEGamepad.cpp
        src/controlblock/gamepads/MAMEGamepad.h
        src/controlblock/hal/mcp23s17pi.cpp
        src/controlblock/hal/mcp23s17pi.h
        src/controlblock/gamepads/NONEGamepad.cpp
        src/controlblock/gamepads/NONEGamepad.h
        src/controlblock/app/PowerSwitch.cpp
        src/controlblock/app/PowerSwitch.h
        src/controlblock/config/SingleConfiguration.cpp
        src/controlblock/config/SingleConfiguration.h
        src/controlblock/gamepads/SNESGamepad.cpp
        src/controlblock/gamepads/SNESGamepad.h
        src/controlblock/uinput/UInputDevice.cpp
        src/controlblock/uinput/UInputDevice.h
        src/controlblock/uinput/UInputGamepadArcade.cpp
        src/controlblock/uinput/UInputGamepadArcade.h
        src/controlblock/uinput/UInputGamepadSNES.cpp
        src/controlblock/uinput/UInputGamepadSNES.h
        src/controlblock/uinput/UInputKeyboard.cpp
        src/controlblock/uinput/UInputKeyboard.h
        src/lib/bcm2835-1.48/src/bcm2835.c
        src/lib/bcm2835-1.48/src/bcm2835.h
        )

include_directories(src/controlblock)
include_directories(src/lib/bcm2835-1.48/src)
include_directories(src/lib/jsoncpp/include)

add_subdirectory(src/lib/jsoncpp)

add_executable(controlblockservice2 ${SOURCE_FILES})
target_link_libraries(controlblockservice2 jsoncpp_lib_static)

install(FILES ${CMAKE_BINARY_DIR}/controlblockservice2 DESTINATION bin
        PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
        GROUP_EXECUTE GROUP_READ
        )
install(FILES ${CMAKE_BINARY_DIR}/../supplementary/controlblockconfig.cfg DESTINATION etc
        PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
        GROUP_EXECUTE GROUP_READ
        )

add_custom_target(uninstall
        "${CMAKE_COMMAND}" -P "${CMAKE_SOURCE_DIR}/scripts/uninstall.cmake"
        )

add_custom_target(installservice
        COMMAND chmod +x insertLine.sh
        COMMAND chmod +x controlblockservice
        COMMAND ./insertLine.sh
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/scripts
        COMMENT "Installing service."
        )

add_custom_target(uninstallservice
        COMMAND /etc/init.d/controlblockservice stop
        COMMAND update-rc.d controlblockservice remove
        COMMAND rm /etc/init.d/controlblockservice
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/../scripts
        COMMENT "Uninstalling service."
        )

enable_testing()
add_subdirectory(test)
add_test(testname sample_tests)