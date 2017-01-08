add_library(controlblock-hal STATIC
        DigitalIn.cpp
        DigitalOut.cpp
        HALFactory.cpp
        mcp23s17pi.cpp
        )

target_link_libraries(controlblock-hal bcm2835)
