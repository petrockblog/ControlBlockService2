cmake_minimum_required(VERSION 2.8.5)

project(ControlBlockService2)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g")
set(EXECUTABLE_NAME "controlblock")

include_directories(src/controlblock)
include_directories(src/lib/jsoncpp/include)
include_directories(src/lib/LIO/src)
include_directories(src/lib/mcp23s17)
include_directories(src/lib/plog/include)
include_directories(src/lib/fmt/include)

add_subdirectory(src/lib/jsoncpp)
add_subdirectory(src/lib/LIO/src)
add_subdirectory(src/lib/mcp23s17)
add_subdirectory(src/lib/fmt)

set(PLOG_BUILD_SAMPLES OFF)

add_subdirectory(src/controlblock/app)
add_subdirectory(src/controlblock/config)
add_subdirectory(src/controlblock/hal)
add_subdirectory(src/controlblock/gamepads)
add_subdirectory(src/controlblock/uinput)

add_subdirectory(doc)  # Doxygen documentation target

add_executable(${EXECUTABLE_NAME} "src/controlblock/main.cpp")
target_link_libraries(${EXECUTABLE_NAME} controlblock-app controlblock-config controlblock-hal controlblock-gamepads controlblock-uinput LIOlib mcp23s17Lib fmt)

install(FILES ${CMAKE_BINARY_DIR}/${EXECUTABLE_NAME} DESTINATION /usr/bin
        PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
        GROUP_EXECUTE GROUP_READ
        )
install(FILES ${CMAKE_BINARY_DIR}/../supplementary/controlblockconfig.cfg DESTINATION /etc
        PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
        GROUP_READ
        )
install(FILES ${CMAKE_BINARY_DIR}/../supplementary/controlblockswitchoff.sh DESTINATION /etc
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
