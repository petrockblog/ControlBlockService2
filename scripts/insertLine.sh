#!/bin/bash

function addSPIBcmModule() {
    echo -e "Making sure that spi-dev is contained in /etc/modules ..."
    if [[ -z $(cat /boot/config.txt | grep "dtparam=spi=on") ]]; then
        sed -i '$a dtparam=spi=on' /boot/config.txt
    fi
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
