#!/bin/bash

function addSPIBcmModule() {
    echo -e "Making sure that SPI interface is enabled"

    # RPi 5 uses /boot/firmware/config.txt, older versions use /boot/config.txt
    if [ -f /boot/firmware/config.txt ]; then
        CONFIG_FILE="/boot/firmware/config.txt"
    else
        CONFIG_FILE="/boot/config.txt"
    fi

    grep -qxF 'dtparam=spi=on' "$CONFIG_FILE" || echo 'dtparam=spi=on' >> "$CONFIG_FILE"
    modprobe spi_bcm2835 2>/dev/null || true  # May not exist on RPi 5
}

# enable spi kernel module
touch /etc/modprobe.d/raspi-blacklist.conf
sed -i -e "s|^blacklist spi-bcm2708|#blacklist spi-bcm2708|g" /etc/modprobe.d/raspi-blacklist.conf
dtparam spi=on
addSPIBcmModule

# install ControlBlockService files
install -m 0755 controlblock.service /etc/systemd/system/
systemctl enable --now controlblock.service
