#!/bin/bash
# remove binary
sudo rm /usr/local/bin/fbd
# remove configs
sudo rm /usr/share/dbus-1/system-services/org.openice.fbd.service
sudo rm /etc/dbus-1/system.d/org.openice.fbd.conf
sudo rm /etc/udev/rules.d/99-fusionbrain.rules

# done
echo Finished removing fbd and all config files
