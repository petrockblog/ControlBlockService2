!#/usr/bin 

# ensure that all needed OS packages are installed
apt-get install -y git cmake g++-4.9 doxygen

# download the driver sources from the repository to the local machine
git clone --recursive https://github.com/petrockblog/ControlBlockService2.git

# change into the driver directory
pushd ControlBlockService2

# create a folder that will contain all build artefacts and change into that folder
mkdir build
cd build

# create Makefiles
cmake ..

# build driver binary
make

# install the binary
make install

# install the driver as a service
make installservice

# change back into the original folder
popd
