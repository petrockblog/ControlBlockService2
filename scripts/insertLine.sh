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
install -m 0755 controlblock.service /etc/systemd/system/
install -m 0755 controlblock-start.sh /usr/bin/
systemctl enable --now controlblock.service
