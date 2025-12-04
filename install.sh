#!/bin/bash

# Function to check if the script is run with sudo
check_sudo() {
    if [[ "$(id -u)" -ne 0 ]]; then
        echo "Script must be run under sudo from the user you want to install for. Try 'sudo $0'"
        exit 1
    fi
}

# Function to update boot configuration
update_boot_config() {
    # RPi 5 uses /boot/firmware/config.txt, older versions use /boot/config.txt
    local FILE
    if [[ -f /boot/firmware/config.txt ]]; then
        FILE="/boot/firmware/config.txt"
    else
        FILE="/boot/config.txt"
    fi

    local LINE_TO_ENSURE="usb_max_current_enable=1"
    local LINE_TO_REPLACE="usb_max_current_enable=0"

    if grep -Fxq "$LINE_TO_ENSURE" "$FILE"; then
        echo "$FILE is up-to-date, no action taken."
    elif grep -Fxq "$LINE_TO_REPLACE" "$FILE"; then
        sed -i "s/^$LINE_TO_REPLACE/$LINE_TO_ENSURE/" "$FILE"
        echo "$FILE updated."
    else
        echo "$LINE_TO_ENSURE" | sudo tee -a "$FILE"
        echo "$FILE updated."
    fi
}

# Function to ensure all needed OS packages are installed
install_packages() {
    apt-get install -y git cmake g++ doxygen libc6 libc6-dev libgpiod-dev gpiod || {
        echo "Error during installation of APT packages"
        exit 1
    }
}

# Function to ensure we are within the ControlBlockService2 directory
ensure_directory() {
    local currentDirectory=${PWD##*/}
    if [[ $currentDirectory != "ControlBlockService2" ]]; then
        if [[ -d ControlBlockService2 ]]; then
            rm -rf ControlBlockService2
        fi
        git clone --recursive https://github.com/petrockblog/ControlBlockService2
        cd ControlBlockService2 || exit
    fi
}

# Function to ensure that the submodule data is available
update_submodules() {
    git submodule update --init --recursive
}

# Function to create a folder for build artifacts and change into that folder
prepare_build_directory() {
    if [[ -d build ]]; then
        rm -rf build
    fi
    mkdir build || {
        echo "Error while creating build folder"
        exit 1
    }
    pushd build || {
        echo "Error while changing into the folder build"
        exit 1
    }
}

# Function to create Makefiles and build the driver
build_driver() {
    cmake .. || {
        echo "Error while generating Makefiles"
        exit 1
    }
    make || {
        echo "Error during building binary"
        exit 1
    }
}

# Function to install the binary and the driver as a service
install_driver() {
    make install || {
        echo "Error during installation of binary"
        exit 1
    }
    make installservice || {
        echo "Error during installation of service"
        exit 1
    }
    sleep 3
}

# Function to perform sanity checks
perform_sanity_checks() {
    if [[ ! -f /usr/bin/controlblock ]]; then
        echo "[ERROR] The ControlBlock driver binary is not installed"
    else
        echo "[SUCCESS] The ControlBlock driver binary is installed"
    fi

    local isServiceRunning
    isServiceRunning=$(pgrep -x controlblock)
    if [[ -n $isServiceRunning ]]; then
        echo "[SUCCESS] The ControlBlock service is running"
    else
        echo "[ERROR] The ControlBlock service is not running"
    fi
}

# Main script execution
check_sudo
install_packages
ensure_directory
update_submodules
prepare_build_directory
build_driver
install_driver
perform_sanity_checks
update_boot_config

echo "You can find the configuration file at /etc/controlblockconfig.cfg"
