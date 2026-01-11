// Compile test for libgpiod version detection
// Usage: g++ -E test_gpiod_version.cpp 2>&1 | grep "GPIOD_VERSION"
// Or on RPi: g++ -c test_gpiod_version.cpp -o /dev/null

#include <iostream>

// Simulate the detection logic from PowerSwitch.h
#if __has_include(<gpiod.h>)
    #include <gpiod.h>
    #if defined(GPIOD_API_VERSION) && GPIOD_API_VERSION >= 0x00020000
        #define GPIOD_VERSION_2X
        #pragma message "Detected libgpiod v2.x API"
    #else
        #pragma message "Detected libgpiod v1.x API (or GPIOD_API_VERSION not defined)"
    #endif
#else
    #pragma message "gpiod.h not found - libgpiod not installed"
#endif

int main() {
#ifdef GPIOD_VERSION_2X
    std::cout << "Using libgpiod v2.x API" << std::endl;
#else
    std::cout << "Using libgpiod v1.x API" << std::endl;
#endif
    return 0;
}
