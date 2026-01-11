# ControlBlockService2 - AI Coding Assistant Guide

## Project Overview
Raspberry Pi driver for ControlBlock hardware (rev 2.X) - an SPI-based extension board enabling retro gamepad connectivity and power management. Runs as systemd service, polling GPIO at 25ms intervals to translate hardware signals into Linux uinput events.

## Architecture Essentials

### Core Components & Data Flow
1. **Main Loop** ([src/controlblock/main.cpp](../src/controlblock/main.cpp)): Initializes MCP23S17 SPI interface → creates ControlBlock → polls every 25ms
2. **ControlBlock** ([src/controlblock/app/ControlBlock.cpp](../src/controlblock/app/ControlBlock.cpp)): Orchestrator managing up to 2 boards (4 gamepads total), owns PowerSwitch and InputDevice array
3. **HAL** ([src/controlblock/hal/](../src/controlblock/hal/)): `DigitalIO` wraps 2 MCP23S17 chips per board (32 GPIO) accessed via SPI
4. **Gamepads** ([src/controlblock/gamepads/](../src/controlblock/gamepads/)): Factory-created types (Arcade/MAME/SNES/NES/Genesis/Saturn) with type-specific protocols
5. **UInput** ([src/controlblock/uinput/](../src/controlblock/uinput/)): Creates Linux virtual input devices (`/dev/input/js*`) matching gamepad type

**Key Pattern**: Dependency injection via interfaces (`IDigitalIO`, `IUInputFactory`, `IGamepadFactory`) enables testing with mocks.

### Hardware Specifics
- **MCP23S17 Chips**: 2 per ControlBlock, 16 GPIO each → Player 1 on lower half, Player 2 on upper half
- **Multi-Board**: Second ControlBlock requires SJ1=1 (solder jumper) and bent pins 11-12 to interrupt power signals
- **Serial Protocols**: SNES/NES/Genesis use bit-banged serial on SELECT/CLOCK pins with precise timing

## Build & Test Commands

```bash
# Build (requires submodules initialized)
mkdir build && cd build
cmake ..
make

# Install binary + config + service
sudo make install
sudo make installservice

# Run tests (Google Test framework)
./test/runAllTests
./test/runAllTests --gtest_output=xml:gtestresults.xml

# Uninstall
sudo make uninstallservice
sudo make uninstall
```

**Quick install**: `wget -O - https://raw.githubusercontent.com/petrockblog/ControlBlockService2/master/install.sh | sudo bash`

## Project-Specific Conventions

### Code Patterns
- **C++17** with manual memory management for gamepads (raw pointers in arrays)
- **Polling architecture**: No interrupts, 25ms sleep in main loop
- **Configuration**: JSON at `/etc/controlblockconfig.cfg` loaded once at startup
- **Logging**: plog library with file output, use `Logger::logMessage()`
- **Error handling**: Exceptions caught in main loop, no recovery attempt

### File Organization
- **CMakeLists per component**: Each subdirectory has own CMakeLists.txt
- **Interface pattern**: `I<Name>.h` for abstract interfaces, concrete implementations without prefix
- **Test mirrors source**: `test/controlblock/` mirrors `src/controlblock/` structure

### Naming Conventions
- Enums: `Type_e` suffix (e.g., `GamepadType_e`, `Channel_e`)
- Private members: `m_` prefix (e.g., `m_numberOfGamepads`)
- Constants: `k` prefix (e.g., `kWaitingTime_ms`)
- Factories: Create via `createGamepad()` / `createUInputDevice()` methods

## Critical Implementation Details

### Gamepad Type Implementations
- **Arcade/MAME**: Direct GPIO mapping, MAME uses `UInputKeyboard` for MAME-specific keycodes
- **SNES/NES**: 8/16-bit shift registers read via serial protocol in `update()` (NES has reset button on Player 1 Input B)
- **Genesis**: Auto-detects 3/6-button via mode polling, Hold START+A+B+C+UP forces 6-button
- **Saturn**: 8-bit serial protocol on SELECT pin

### Power Switch Behavior
- Only enabled on first ControlBlock (config `powerswitchOn: true`)
- Monitors `FROMPOWERSWITCH` pin for shutdown signal
- Executes `/etc/controlblockswitchoff.sh` (user-customizable) before system shutdown

### Testing Strategy
Uses Google Test with mocked interfaces - **enables testing without physical hardware**:
- Mock `IDigitalIO` for GPIO expectations (simulates MCP23S17 chip responses)
- Mock `IUInputDevice` for event verification (captures uinput calls)
- Test file pattern: `test/controlblock/<component>/<Class>Test.cpp`
- Compile definition: `DEF_TESTCONFIGFILE` points to test config

**Testing without hardware**:
1. Create mock implementations of `IDigitalIO` using Google Mock
2. Set expectations for GPIO reads/writes (e.g., `EXPECT_CALL(mockIO, getLevel(_))`)
3. Verify gamepad `update()` produces correct button states
4. Check `UInputDevice` receives expected event codes
5. Example: [test/controlblock/gamepads/ArcadeGamepadTest.cpp](../test/controlblock/gamepads/ArcadeGamepadTest.cpp)

## Dependencies & External Integrations
- **jsoncpp**: JSON parsing, config comments via preprocessing
- **mcp23s17**: Custom SPI library for I/O expander (submodule `src/lib/mcp23s17/`)
- **plog**: Header-only logging (submodule `src/lib/plog/`)
- **fmt**: String formatting (submodule `src/lib/fmt/`)
- **gpiodcxx**: Linux GPIO character device API (system package: `libgpiod-dev`)
- **uinput kernel API**: Creates virtual input devices, requires root access

**libgpiod Version Compatibility** (critical for RPi5/Bookworm):
- Code supports both libgpiod v1.x (Bullseye) and v2.x (future) APIs
- Version detection via `GPIOD_API_VERSION` macro in [PowerSwitch.h](../src/controlblock/app/PowerSwitch.h)
- v1.x uses `chip->get_line()` + `line_request` struct
- v2.x uses `chip->prepare_request()` + `line_settings` builder pattern
- Debian Bookworm ships libgpiod v1.6.x despite being newer than Bullseye

## Troubleshooting Workflows

**Debug gamepad input**:
```bash
jstest /dev/input/js0  # Test player 1
journalctl -u controlblock -f  # Live service logs
```

**Verify GPIO**: `scripts/testRPiGPIO.sh` tests raw Raspberry Pi GPIO

**Service management**:
```bash
sudo systemctl status controlblock
sudo systemctl restart controlblock
```

## When Modifying Code

**Adding new gamepad type**:
1. Subclass `InputDevice` in `src/controlblock/gamepads/`
2. Add enum value to `GamepadType_e` in `InputDevice.h`
3. Update `GamepadFactory::createGamepad()` switch statement
4. Create matching `UInputGamepad<Type>` class
5. Update `configureDevice()` in `ControlBlock.cpp` for GPIO setup
6. Add test file mirroring source structure

**Configuration changes**: Modify `/etc/controlblockconfig.cfg`, restart service (no hot-reload)

**GPIO mapping changes**: Update pin assignments in `IDigitalIO::DIO_Channel_e` enum - impacts both ControlBlock hardware layout and software expectations
