cmake_minimum_required(VERSION 2.8.5)

add_subdirectory(lib/googletest)

set(ALL_TESTS_RUNNER_FILE "runAllTests")

include_directories(
        ${gtest_SOURCE_DIR}/include
        ${gtest_SOURCE_DIR}/
        ${gmock_SOURCE_DIR}/include
        ${gmock_SOURCE_DIR}/
        controlblock
)

set_source_files_properties(controlblock/app/ControlBlockTest.cpp PROPERTIES COMPILE_DEFINITIONS TESTCONFIGFILE="${PROJECT_SOURCE_DIR}/supplementary/controlblockconfig.cfg")

add_executable(${ALL_TESTS_RUNNER_FILE}
        ../src/controlblock/app/ControlBlock.cpp
        controlblock/app/ControlBlockTest.cpp

        ../src/controlblock/app/PowerSwitch.cpp
        controlblock/app/PowerBlockTest.cpp

        ../src/controlblock/gamepads/ArcadeGamepad.cpp
        controlblock/gamepads/ArcadeGamepadTest.cpp

        ../src/controlblock/gamepads/GenesisGamepad.cpp
        controlblock/gamepads/GenesisGamepadTest.cpp
        )

target_link_libraries(${ALL_TESTS_RUNNER_FILE} gtest gtest_main gmock controlblock-gamepads controlblock-config)

add_test(NAME AllControlBlockTests COMMAND "${PROJECT_BINARY_DIR}/test/${ALL_TESTS_RUNNER_FILE}" " --gtest_output=xml:gtestresults.xml")
