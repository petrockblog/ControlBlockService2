#!/bin/bash
echo -e "Making sure that spi-dev is contained in /etc/modules ..."
if [[ -z $(cat /boot/config.txt | grep "dtparam=spi=on") ]]; then
	sed -i '$a dtparam=spi=on' /boot/config.txt
fi
modprobe spi_bcm2835
