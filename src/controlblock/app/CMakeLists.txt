add_library(controlblock-app STATIC
        ControlBlock.cpp
        PowerSwitch.cpp
        )

target_link_libraries(controlblock-app controlblock-config)
target_link_libraries(controlblock-app controlblock-gamepads)

