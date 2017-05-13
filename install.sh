!#/usr/bin 

# ensure that all needed OS packages are installed
apt-get install -y git cmake g++-4.9 doxygen || (c=$?; echo "Error during installation of APT packages"; (exit $c))

# download the driver sources from the repository to the local machine
git clone --recursive https://github.com/petrockblog/ControlBlockService2.git || (c=$?; echo "Error while downloading the repository"; (exit $c))

# change into the driver directory
pushd ControlBlockService2 || (c=$?; echo "Error while changing into the folder ControlBlockService2"; (exit $c))

# create a folder that will contain all build artefacts and change into that folder
mkdir build || (c=$?; echo "Error while creating build folder"; (exit $c))
cd build || (c=$?; echo "Error while changing into the folder build"; (exit $c))

# create Makefiles
cmake .. || (c=$?; echo "Error while generating Makefiles"; (exit $c))

# build driver binary
make || (c=$?; echo "Error during building binary"; (exit $c))

# install the binary
make install || (c=$?; echo "Error during installation of binary"; (exit $c))

# install the driver as a service
make installservice || (c=$?; echo "Error during installation of service"; (exit $c))

# change back into the original folder
popd
