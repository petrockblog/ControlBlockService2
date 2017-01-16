ControlBlockService2
====================

[![Build Status](https://travis-ci.org/petrockblog/ControlBlockService2.svg?branch=master)](https://travis-ci.org/petrockblog/ControlBlockService2)

This is the driver for the petrockblock.com ControlBlock, which is an extension board for the Raspberry Pi (TM). The driver itself is denoted as _controlblock_ in the following. The driver provides a service for interacting with the power button signals as well as for mapping attached game controllers to corresponding game pad devices on the Raspberry Pi.

**Please note that this is the driver for revision 2.X of the ControlBlock. If you have a revision 1.X board, you need to use the [driver for that revision series](https://github.com/petrockblog/ControlBlockService).**

## Downloading

If you would like to download the latest version of _controlblock_ from [its Github repository](https://github.com/petrockblog/ControlBlockService2), you can use this command:
```bash
git clone --recursive https://github.com/petrockblog/ControlBlockService2.git
```

Note that the above command also takes care for downloading the included Git submodules.

## Prerequisites

To be able to successfully build ControlBlockService you need to have certain APT packages installed. You can make sure that you have the latest version of those packages with these commands:

```bash
sudo apt-get update
sudo apt-get upgrade -y
sudo apt-get install -y cmake g++-4.9 doxygen
```

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

The configuration file of _controlblock_ is located at __```/usr/local/etc/controlblockconfig.cfg```__. It uses JSON syntax for setting the the values of its configuration parameters.

The default configuration file looks like this:

```bash
{
    "controlblocks" : [
        {
            "enabled" : true,          // Enables (=true) or disables (=false) the ControlBlock 
            "address" : {              // The address information of the first ControlBlock
                "SJ1" : 0,             // The hardware address solder-jumper SJ1. Options: 0, 1 
                "SJ2" : 0              // The hardware address solder-jumper SJ2, Options: 0, 1
            },
            "gamepadtype" : "arcade",  // Sets the gamepad type. Options: "arcade", "mame", "snes", "none"
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

 You can also connect a latching __reset button__ to `Player-2, Input B`. If the button is pressed a virtual ESC-key press will be triggered.


### Only one Gamepad

If you want to connect only one gamepad to the ControlBlock you can set the element `onlyOneGamepad` to `true`: It enables only one gamepad in the system (e.g., if only Player-1 buttons are wired to the ControlBlock in your setup, this prevents a ghost gamepad from being selected as default player 2 in retroarch)


### 4-Player Extension

The driver can handle up to two ControlBlocks. This means that you can stack two ControlBlock on top of each other to have inputs for four players. To do so make sure that you set different addresses for each of the ControlBlocks. You can set the address of each ControlBlock by setting the two solder jumpers of each ControlBlock accordingly. The values of the solder jumpers have to be set in the configuration file with the elements `SJ1` and `SJ2`. Also, you have to enable the second ControlBlock by setting the element `enabled` for the second ControlBlock to `true`.


### Power Switch Functionality

To enable or disable the power switch functionality you can set the element `powerswitchOn` to `true` or `false`:

 - ```true```: Activates the handling of the power switch signals of the ControlBlock.
 - ```false```: Deactivates the handling of the power switch signals of the ControlBlock.


<br><br>
__Have fun!__

-Florian [petrockblock.com](http://blog.petrockblock.com)
