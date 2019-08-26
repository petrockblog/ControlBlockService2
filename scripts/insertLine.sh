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

# install GPIO device tree overlay
apt-get install -q -y device-tree-compiler
dtc -@ -I dts -O dtb -o gpio_pull-overlay.dtb gpio_pull-overlay.dts
cp gpio_pull-overlay.dtb /boot/overlays
grep -qxF 'dtoverlay=gpio_pull' /boot/config.txt || echo 'dtoverlay=gpio_pull' >> /boot/config.txt

# install ControlBlockService files
install -m 0755 controlblockservice /etc/init.d
update-rc.d controlblockservice defaults
/etc/init.d/controlblockservice start

echo "!!! Please note that YOU NEED TO REBOOT to let the driver be effective. !!!"