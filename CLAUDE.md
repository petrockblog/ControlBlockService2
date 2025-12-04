# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

ControlBlockService2 is a Raspberry Pi driver for the ControlBlock hardware (revision 2.X), which is an extension board that provides:
- Power button signal handling with shutdown functionality
- Game controller mapping to Linux game pad devices
- Support for multiple controller types (Arcade, MAME, SNES, NES, Genesis, Saturn)
- Support for up to 2 stacked ControlBlocks (4-player support)

The driver runs as a systemd service and polls controller inputs at 25ms intervals, translating GPIO signals to Linux uinput events.

## Build System

The project uses CMake with C++17. Important commands:

```bash
# Initial setup - clone with submodules
git clone --recursive https://github.com/petrockblog/ControlBlockService2.git

# Update submodules if already cloned
git submodule update --init --recursive

# Build from scratch
mkdir build && cd build
cmake ..
make

# Install binary and config files
sudo make install

# Install as systemd service
sudo make installservice

# Uninstall service
sudo make uninstallservice

# Uninstall binary
sudo make uninstall
```

## Testing

The project uses Google Test for unit testing. Tests are located in `test/controlblock/`:

```bash
# Build and run tests (from build directory)
cd build
make
./test/runAllTests

# Run with XML output
./test/runAllTests --gtest_output=xml:gtestresults.xml
```

Test coverage includes:
- ControlBlock main logic
- PowerSwitch functionality
- Individual gamepad types (Arcade, MAME, SNES, Genesis)

## Architecture

### Main Loop
Entry point is `src/controlblock/main.cpp`. The service:
1. Initializes logger, signal handlers, and MCP23S17 SPI communication
2. Creates ControlBlock instance with factories for uinput and gamepads
3. Polls `controlBlock.update()` every 25ms until shutdown signal

### Core Components

**ControlBlock** (`src/controlblock/app/ControlBlock.h/cpp`)
- Main orchestrator that manages up to 2 ControlBlocks (4 input devices total)
- Owns PowerSwitch, MCP23S17 interfaces, and InputDevice array
- `update()` method polls all gamepads and power switch

**PowerSwitch** (`src/controlblock/app/PowerSwitch.h/cpp`)
- Monitors GPIO pins for shutdown signal from ControlBlock hardware
- Executes `/etc/controlblockswitchoff.sh` on shutdown (customizable by user)

**Configuration** (`src/controlblock/config/`)
- `ControlBlockConfiguration`: Loads JSON from `/etc/controlblockconfig.cfg`
- `SingleConfiguration`: Per-ControlBlock settings (gamepad type, address, power switch enable)
- Supports up to 2 ControlBlock configurations with hardware addressing via SJ1/SJ2 solder jumpers

**Hardware Abstraction Layer** (`src/controlblock/hal/`)
- `IDigitalIO`: Interface for GPIO operations
- `DigitalIO`: Implementation wrapping MCP23S17 I/O expander
- `mcp23s17pi`: Low-level SPI communication with MCP23S17 chips
- Each ControlBlock uses 2 MCP23S17 chips (32 GPIO total: 16 per player)

**Input Devices** (`src/controlblock/gamepads/`)
- `InputDevice`: Base interface with `initialize()` and `update()`
- `GamepadFactory`: Creates appropriate gamepad type based on config
- Implementations:
  - `ArcadeGamepad`: Direct button/joystick mapping
  - `MAMEGamepad`: Virtual keyboard with MAME-specific key layout
  - `SNESGamepad`: Serial protocol for SNES controllers
  - `NESGamepad`: Serial protocol for NES controllers
  - `GenesisGamepad`: Sega Genesis/Megadrive with 3/6-button mode switching
  - `SaturnGamepad`: Sega Saturn controller support
  - `NONEGamepad`: Disabled gamepad

**UInput Layer** (`src/controlblock/uinput/`)
- `UInputFactory`: Creates Linux uinput devices
- `UInputDevice`: Base class for uinput device registration
- Per-gamepad implementations (`UInputGamepadArcade`, `UInputGamepadSNES`, etc.)
- `UInputKeyboard`: Virtual keyboard for MAME mode
- Uses Linux uinput API to create virtual input devices at `/dev/input/js*`

### GPIO Mapping

Each player has GPIO pins mapped through 2 MCP23S17 chips:
- **Player 1**: RIGHT, LEFT, UP, DOWN, SW1-SW8, START, COIN, A, B (MCP1/MCP2)
- **Player 2**: Same layout, mirrored on upper half of MCP registers
- **Power Switch**: Special pins for shutdown signal (FROMPOWERSWITCH, TOPOWERSWITCH)
- **Genesis/Saturn**: Additional SELECT pins for serial protocol timing

See `src/controlblock/hal/IDigitalIO.h` for complete channel mapping.

## Configuration

Runtime config at `/etc/controlblockconfig.cfg` (JSON with comments):
- `enabled`: Enable/disable each ControlBlock
- `address.SJ1/SJ2`: Hardware address (0 or 1) for multi-board setups
- `gamepadtype`: "arcade", "mame", "snes", "nes", "genesis", "saturn", "none"
- `onlyOneGamepad`: Register only 1 gamepad instead of 2 (prevents ghost player 2)
- `powerswitchOn`: Enable power switch functionality (only on first ControlBlock)

For 4-player setups:
1. Set second ControlBlock's SJ1 to 1 (hardware solder jumper)
2. Bend pins 11-12 on bottom ControlBlock to interrupt power signals
3. Enable second ControlBlock in config with matching address

## Dependencies

- **jsoncpp**: JSON parsing for configuration (`src/lib/jsoncpp/`)
- **mcp23s17**: MCP23S17 I/O expander library (`src/lib/mcp23s17/`)
- **plog**: Logging library (`src/lib/plog/`)
- **fmt**: String formatting (`src/lib/fmt/`)
- **gpiodcxx**: Linux GPIO character device interface (system package: libgpiod-dev)
- **googletest/googlemock**: Unit testing framework (`test/lib/googletest/`)

All submodules are included in the repository.

## Platform-Specific

- **Target**: Raspberry Pi (requires SPI and GPIO access)
- **OS**: Raspbian/Raspberry Pi OS
- **System dependencies**: `git cmake g++ doxygen libc6 libc6-dev libgpiod-dev gpiod`
- **SPI interface**: Must be enabled on Raspberry Pi (`dtparam=spi=on`)
- **Permissions**: Requires root for GPIO/uinput access (runs as systemd service)

## Installation Script

`install.sh` performs full automated installation:
1. Installs APT dependencies
2. Clones repository with submodules (if not present)
3. Builds binary
4. Installs to `/usr/bin/controlblock`
5. Installs service to systemd
6. Configures USB max current in `/boot/config.txt`

Quick install: `wget -O - https://raw.githubusercontent.com/petrockblog/ControlBlockService2/master/install.sh | sudo bash`

## Systemd Service

Service file: `scripts/controlblock.service`
- Installed to `/etc/systemd/system/controlblock.service`
- Runs `/usr/bin/controlblock` as root
- Auto-starts on boot

Shutdown script: `/etc/controlblockswitchoff.sh` (user-customizable)

## Development Notes

- The driver uses polling (25ms interval) rather than interrupts
- GPIO operations are buffered through MCP23S17 to minimize SPI transactions
- Gamepad types have different initialization sequences (especially serial controllers)
- Genesis gamepad supports mode switching: Hold START+A+B+C+UP for 6-button mode
- SNES reset button (Player 1, Input B): Triggers ESC key + START+SELECT combo
- Power switch functionality only works on first ControlBlock in multi-board setups

## Troubleshooting

Use `scripts/testRPiGPIO.sh` to verify raw GPIO functionality.

Test gamepad inputs with `jstest`:
```bash
jstest /dev/input/js0  # Player 1
jstest /dev/input/js1  # Player 2
```

Check service status:
```bash
sudo systemctl status controlblock
journalctl -u controlblock -f  # Live logs
```
