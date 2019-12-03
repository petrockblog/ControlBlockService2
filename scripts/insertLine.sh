#!/bin/bash

function addSPIBcmModule() {
    echo -e "Making sure that SPI interface is enabled"
    grep -qxF 'dtparam=spi=on' /boot/config.txt || echo 'dtparam=spi=on' >> /boot/config.txt
    modprobe spi_bcm2835
}

# enable spi kernel module
touch /etc/modprobe.d/raspi-blacklist.conf
sed -i -e "s|^blacklist spi-bcm2708|#blacklist spi-bcm2708|g" /etc/modprobe.d/raspi-blacklist.conf
addSPIBcmModule

# install ControlBlockService files
install -m 0755 controlblockservice /etc/init.d
update-rc.d controlblockservice defaults
/etc/init.d/controlblockservice start
