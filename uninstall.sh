!#/usr/bin 

# ensure that all needed OS packages are installed
apt-get install -y git cmake g++-4.9 doxygen

if [[ ! -d ControlBlockService2 ]]; then
	# download the driver sources from the repository to the local machine
	git clone --recursive https://github.com/petrockblog/ControlBlockService2.git
	# change into the driver directory
	pushd ControlBlockService2
else
	# change into the driver directory
	pushd ControlBlockService2
	# update sources to latest version
	git pull
fi


# create a folder that will contain all build artefacts and change into that folder
mkdir build
cd build

# create Makefiles
cmake ..

# install the binary
make uninstall

# install the driver as a service
make uninstallservice

# change back into the original folder
popd
