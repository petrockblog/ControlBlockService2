ControlBlockService2
====================

[![Build Status](https://travis-ci.org/petrockblog/ControlBlockService2.svg?branch=master)](https://travis-ci.org/petrockblog/ControlBlockService2)

This is the driver for the petrockblock.com ControlBlock, which is an extension board for the Raspberry Pi (TM). The driver itself is denoted as _controlblock_ in the following. The driver provides a service for interacting with the power button signals as well as for mapping attached game controllers to corresponding game pad devices on the Raspberry Pi.

**Please note that this is the driver for revision 2.X of the ControlBlock. If you have a revision 1.X board, you need to use the [driver for that revision series](https://github.com/petrockblog/ControlBlockService).**

## Contents



 - [Prerequisites](#prerequisites)
 - [Downloading](#downloading) 
 - [Quick Installation](#quick-installation)
 - [Building and Installation](#building-and-installation)
 - [Make the Driver Start at Boot](#installation-as-service)
 - [Uninstalling the driver and the service](#uninstalling-the-service-andor-the-binary)
 - [Configuration](#configuration)
    - [Setting the Type of Game Pad](#setting-the-type-of-gamepad)
    - [Using only One Game Pad](#using-only-one-game-pad)
    - [Enabling or Disabling the Power Switch Functionality](#enabling-or-disabling-the-power-switch-functionality)
 - [Custom Actions at Shutdown](#custom-actions-at-shutdown)
 - [4-Player Extension with two ControlBlocks](#4-player-extension-with-two-controlblocks)
     + [Four Player Hardware Setup Example](#four-player-hardware-setup-example)
 - [Troubleshooting](#troubleshooting)


## Prerequisites

To be able to successfully build ControlBlockService you need to have certain APT packages installed. You can make sure that you have the latest version of those packages with these commands:

```bash
sudo apt-get update
sudo apt-get upgrade -y
sudo apt-get install -y git cmake g++-4.9 doxygen
```


## Downloading

If you would like to download the latest version of _controlblock_ from [its Github repository](https://github.com/petrockblog/ControlBlockService2), you can use this command:
```bash
git clone --recursive https://github.com/petrockblog/ControlBlockService2.git
```

Note that the above command also takes care for downloading the included Git submodules.

## Quick Installation

There comes an installation script with this reposity that does all the steps described below: `install.sh` This script compiles the driver, installs the binary and configuration files, and installs the ControlBlock service. 

To run the quick installation, you just need to call this one line from the Raspbian console

```bash
wget -O - https://raw.githubusercontent.com/petrockblog/ControlBlockService2/master/install.sh | sudo bash
```

Here is a video of a typical quick installation procedure:

[![asciicast](https://asciinema.org/a/lOGtRU99jT0MDulxSc3ZGuPRd.png)](https://asciinema.org/a/lOGtRU99jT0MDulxSc3ZGuPRd)

## Building and Installation

To build _controlblock_ follow these commands:
```bash
cd ControlBlockService2
mkdir build
cd build
cmake ..
make
```

If everything went fine you can install the driver from within the folder `build` with the command
```bash
sudo make install
```

## Installation as Service

You can install _controlblock_ as daemon from within the folder `build` with this command:
```bash
sudo make installservice
```
It might be that you need to **restart** your Raspberry afterwards to have all needed services running.

## Uninstalling the service and/or the binary

You can uninstall the daemon from within the folder `build` with this command:
```bash
sudo make uninstallservice
```

You can uninstall the binary from within the folder `build` with this command:
```bash
sudo make uninstall
```

## Configuration

The configuration file of _controlblock_ is located at __```/etc/controlblockconfig.cfg```__. It uses JSON syntax for setting the the values of its configuration parameters.

The default configuration file looks like this:

```
{
    "controlblocks" : [
        {
            "enabled" : true,          // Enables (=true) or disables (=false) the ControlBlock 
            "address" : {              // The address information of the first ControlBlock
                "SJ1" : 0,             // The hardware address solder-jumper SJ1. Options: 0, 1 
                "SJ2" : 0              // The hardware address solder-jumper SJ2, Options: 0, 1
            },
            "gamepadtype" : "arcade",  // Sets the gamepad type. Options: "arcade", "mame", "snes", "genesis", "none"
            "onlyOneGamepad" : false,  // If true, registers only one gamepad instead of two
            "powerswitchOn" : true     // Enables (=true) the power switch functionality. Options: true, false
        },
        {
            "enabled" : false,          // Enables (=true) or disables (=false) the second ControlBlock 
            "address" : {               // The address information of the second ControlBlock
                "SJ1" : 1,              // The hardware address solder-jumper SJ1. Options: 0, 1 
                "SJ2" : 0               // The hardware address solder-jumper SJ2, Options: 0, 1
            },
            "gamepadtype" : "arcade",   // Sets the gamepad type. Options: "arcade", "mame", "snes", "none"
            "onlyOneGamepad" : false    // If true, registers only one gamepad instead of two
        }
    ]
}
```


### Setting the Type of Gamepad

To set the type of the gamepad you need to set the value of the element `gamepadtype`. You can choose between these values:

 - ```arcade```: Enables two game pads in the system and maps the GPIOs of the ControlBlock to these game pads.<br>
 ![ArcadeMapping](https://github.com/petrockblog/ControlBlockService2/raw/master/supplementary/ControlBlockLayoutArcade.png)
 - ```mame```: Enables a virtual keyboard and maps the GPIOs of the ControlBlock to this keyboard with a MAME layout.<br>
 ![MAMEMapping](https://github.com/petrockblog/ControlBlockService2/raw/master/supplementary/ControlBlockLayoutMAME.png)
 - ```snes```: Enables two game pads in the system and maps the attached SNES/NES controllers accordingly.<br>
 ![SNESMapping](https://github.com/petrockblog/ControlBlockService2/raw/master/supplementary/ControlBlockLayoutSNES.png)
You can also connect a non-latching __reset button__ to `Player-1, Input B`. If the button is pressed a virtual ESC-key press will be triggered as well as a simultaneous press of the start and select buttons for player 1.

 - ```genesis```: Enables two game pads in the system and maps the attached Genesis/Megadrive/Atari controllers accordingly.<br>
 ![GenesisMapping](https://github.com/petrockblog/ControlBlockService2/raw/master/supplementary/ControlBlockLayoutGenesis.png)
You can __switch to six-button__ controller by pressing the button combination `START, A, B, C, UP` at the same time.

### Using Only one Gamepad

If you want to connect only one gamepad to the ControlBlock you can set the element `onlyOneGamepad` to `true`: It enables only one gamepad in the system (e.g., if only Player-1 buttons are wired to the ControlBlock in your setup, this prevents a ghost gamepad from being selected as default player 2 in retroarch)


### Enabling or Disabling the Power Switch Functionality

To enable or disable the power switch functionality you can set the element `powerswitchOn` to `true` or `false`:

 - ```true```: Activates the handling of the power switch signals of the ControlBlock.
 - ```false```: Deactivates the handling of the power switch signals of the ControlBlock.


### Custom Actions at Shutdown

When the driver observes a shutdown signal from the ControlBlock, a shutdown Bash script is called. You can find and edit it at `/etc/controlblockswitchoff.sh`.


### 4-Player Extension with two ControlBlocks

The driver can handle up to two ControlBlocks. This means that you can stack two ControlBlock on top of each other to have inputs for four players. 

#### Setting Base Address with the Solder Jumpers

In order to use two ControlBlocks on top of each other, you need to change the base address of one of the ControlBlocks to a different value than the default one. The base address is used by the ControlBlock driver to identify and distinguish the two ControlBlocks from each other. The base address can be set with the solder jumpers SJ1 and SJ2. To change the base address, you need to _use a solder iron_ and set, e.g., SJ1 to "1". Make sure that only two of the three solder pads are connected with each other! The following image shows the solder jumpers:

![Solder jumpers SJ1 and SJ2 for setting the base address](https://github.com/petrockblog/ControlBlockService2/raw/master/supplementary/4playerCB3.jpg)

#### Interrupting the Signal Lines for the Power Switch on the Second ControlBlock

It is important that you interrupt the signal lines for the power switch to the second ControlBlock. If you do not interrupt the signals to the top ControlBlock, the system will shutdown immediately after the system start. To interrupt the signal lines you can snap off or bend the pins 11 and 12 on the bottom ControlBlock. The power switch functionality and all game pad functionalities are still given!  Here are two images that show how the pins could be bent:

![Bending pins for 4-player functionality, view 1](https://github.com/petrockblog/ControlBlockService2/raw/master/supplementary/4playerCB1.jpg)

![Bending pins for 4-player functionality, view 2](https://github.com/petrockblog/ControlBlockService2/raw/master/supplementary/4playerCB2.jpg)


#### Adapting the Configuration File for Four Players

The values of the solder jumpers have to be set in the configuration file with the elements `SJ1` and `SJ2`. Also, you have to enable the second ControlBlock by setting the element `enabled` for the second ControlBlock to `true`.

If you have set the solder jumper SJ1 to 1, a usual 4-player configuration that enables two ControlBlocks with arcade mode would look like this:
```
{
    "controlblocks" : [
        {
            "enabled" : true,          // Enables (=true) or disables (=false) the ControlBlock 
            "address" : {              // The address information of the first ControlBlock
                "SJ1" : 0,             // The hardware address solder-jumper SJ1. Options: 0, 1 
                "SJ2" : 0              // The hardware address solder-jumper SJ2, Options: 0, 1
            },
            "gamepadtype" : "arcade",  // Sets the gamepad type. Options: "arcade", "mame", "snes", "genesis", "none"
            "onlyOneGamepad" : false,  // If true, registers only one gamepad instead of two
            "powerswitchOn" : true     // Enables (=true) the power switch functionality. Options: true, false
        },
        {
            "enabled" : true,          // Enables (=true) or disables (=false) the second ControlBlock 
            "address" : {               // The address information of the second ControlBlock
                "SJ1" : 1,              // The hardware address solder-jumper SJ1. Options: 0, 1 
                "SJ2" : 0               // The hardware address solder-jumper SJ2, Options: 0, 1
            },
            "gamepadtype" : "arcade",   // Sets the gamepad type. Options: "arcade", "mame", "snes", "none"
            "onlyOneGamepad" : false    // If true, registers only one gamepad instead of two
        }
    ]
}
```


#### Four Player Hardware Setup Example

Here is an image that shows an exemplary 4-player hardware setup:

![Four Player Hardware Setup Example](https://github.com/petrockblog/ControlBlockService2/raw/master/supplementary/4playerCB4.jpg)

Things to note:

 1. The ControlBlock with the interrupted signal lines for the power switch is directly attached to the Raspberry Pi. The other ControlBlock is on top of that.
 2. If you want to use a power switch, you need to attach the switch and the optional LED to the "lower" ControlBlock, which is directly attached to the Raspberry Pi.
 3. The micro USB connector for the supply power is attached to the lower ControlBlock, which is directly attached to the Raspberry Pi.

## Troubleshooting

It is important to start with a well defined and working installation. Therefore, I suggest to start with a fresh Raspbian, RetroPie or whatever image and install the ControlBlock driver with only the power switch connected. Follow the steps [as described above for that.

If that works, you can test the functionality of the arcade button input pins by using a jumper wire that is connected to GND and contacting the various button pins. `jstest /dev/input/js0` gives you the so simulated button presses for player one and `jstest /dev/input/js1` gives you the simulated button presses for player two (You can exit `jstest` with `Ctrl-C`.

If you find that every input pin is working as expected start with connecting the controls in small steps. For example, first the joysticks, then the buttons for one player, then the ones for the other player. Use `jstest` after every smaller step to verify that things still work as expected.

### Checking the Raw GPIO of the Raspberry

To check that the GPIOs of the Raspberry Pi itself are working correctly, you can use the bash script `scripts/testRPiGPIO.sh`). You can start it with `./scripts/testRPiGPIO.sh`. Please follow the instructions that are printed to the shell.


<br><br>
__Have fun!__

-Florian [petrockblock.com](http://blog.petrockblock.com)
