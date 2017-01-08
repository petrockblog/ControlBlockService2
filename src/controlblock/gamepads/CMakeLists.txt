add_library(controlblock-gamepads STATIC
        ArcadeGamepad.cpp
        MAMEGamepad.cpp
        NONEGamepad.cpp
        SNESGamepad.cpp
        )

target_link_libraries(controlblock-gamepads controlblock-uinput)
target_link_libraries(controlblock-gamepads controlblock-hal)
