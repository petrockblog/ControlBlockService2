installservice:
	if [ ! -f /etc/modprobe.d/raspi-blacklist.conf ]; then touch /etc/modprobe.d/raspi-blacklist.conf; fi;
	sed -i -e "s|^blacklist spi-bcm2708|#blacklist spi-bcm2708|g" /etc/modprobe.d/raspi-blacklist.conf
	./insertLine.sh

	install -m 0755 controlblockservice /etc/init.d
	update-rc.d controlblockservice defaults
	/etc/init.d/controlblockservice start

uninstallservice:
	/etc/init.d/controlblockservice stop
	update-rc.d controlblockservice remove
	-rm /etc/init.d/controlblockservice
