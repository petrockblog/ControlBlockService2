#!/bin/bash

# check, if sudo is used
if [[ "$(id -u)" -ne 0 ]]; then
    echo "Script must be run under sudo from the user you want to install for. Try 'sudo $0'"
    exit 1
fi

# ensure that all needed OS packages are installed
apt-get install -y git cmake g++-4.9 doxygen || (c=$?; echo "Error during installation of APT packages"; (exit $c))

# make sure that the submodule data is available
git submodule update --init --recursive

if [[ -d build ]]; then
    rm -rf build
fi

# create a folder that will contain all build artefacts and change into that folder
mkdir build || (c=$?; echo "Error while creating build folder"; (exit $c))
pushd build || (c=$?; echo "Error while changing into the folder build"; (exit $c))

# create Makefiles
cmake .. || (c=$?; echo "Error while generating Makefiles"; (exit $c))

# ensure that no old instance of the driver is running and installed
make uninstallservice
make uninstall

# build driver binary
make || (c=$?; echo "Error during building binary"; (exit $c))

# install the binary
make install || (c=$?; echo "Error during installation of binary"; (exit $c))

# install the driver as a service
make installservice || (c=$?; echo "Error during installation of service"; (exit $c))

# change back into the original folder
popd

# sanity checks
# check that the binary is installed
if [[ ! -f /usr/bin/controlblock ]]; then
    echo "[ERROR] The ControlBlock driver binary is not installed"
else
    echo "[SUCCESS] The ControlBlock driver binary is installed"
fi

# check that the service is running
ps -ef | grep controlblockservice | grep -v grep
[ $?  -eq "0" ] && echo "[SUCCESS] The ControlBlock service is running" || echo "[ERROR] The ControlBlock service is not running"

echo "You can find the configuration file at /etc/controlblockconfig.cfg".

