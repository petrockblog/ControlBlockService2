cmake_minimum_required(VERSION 2.8.5)

project(ControlBlockService2)

set(CMAKE_CXX_STANDARD 11)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        ${SOURCE_FILES}
        src/controlblock/ArcadeGamepad.cpp
        src/controlblock/ArcadeGamepad.h
        src/controlblock/ControlBlock.cpp
        src/controlblock/ControlBlock.h
        src/controlblock/ControlBlockConfiguration.cpp
        src/controlblock/ControlBlockConfiguration.h
        src/controlblock/DigitalIn.cpp
        src/controlblock/DigitalIn.h
        src/controlblock/DigitalOut.cpp
        src/controlblock/DigitalOut.h
        src/controlblock/HALFactory.cpp
        src/controlblock/HALFactory.h
        src/controlblock/InputDevice.h
        src/controlblock/ISingleConfiguration.h
        src/controlblock/main.cpp
        src/controlblock/MAMEGamepad.cpp
        src/controlblock/MAMEGamepad.h
        src/controlblock/mcp23s17pi.cpp
        src/controlblock/mcp23s17pi.h
        src/controlblock/NONEGamepad.cpp
        src/controlblock/NONEGamepad.h
        src/controlblock/PowerSwitch.cpp
        src/controlblock/PowerSwitch.h
        src/controlblock/SingleConfiguration.cpp
        src/controlblock/SingleConfiguration.h
        src/controlblock/SNESGamepad.cpp
        src/controlblock/SNESGamepad.h
        src/controlblock/UInputDevice.cpp
        src/controlblock/UInputDevice.h
        src/controlblock/UInputGamepadArcade.cpp
        src/controlblock/UInputGamepadArcade.h
        src/controlblock/UInputGamepadSNES.cpp
        src/controlblock/UInputGamepadSNES.h
        src/controlblock/UInputKeyboard.cpp
        src/controlblock/UInputKeyboard.h
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