#!/bin/bash
# dependencies
sudo apt-get install libusb-dev libqt4-dev
# compile
qmake && make
# copy binary
sudo cp fbd /usr/local/bin
# copy configs
sudo cp org.openice.fbd.service /usr/share/dbus-1/system-services/
sudo cp org.openice.fbd.conf    /etc/dbus-1/system.d/
sudo cp 99-fusionbrain.rules    /etc/udev/rules.d/

# should be ready!
echo You can now try
echo dbus-send --session --print-reply --dest="org.openice.fbd" /org/openice/fbd org.openice.fbd.fusionbrain.SetSingleOutput int32:1 boolean:true
