org.openice.fbd
===============
Use a [FusionBrain v4](http://youtu.be/F8DkHWhaEx8) on Linux, via d-sub.

Originally a mirror from https://svn.code.sf.net/p/linuxice/code/packages/fbd/

Per discussion on http://www.mp3car.com/fusion-brain/129622-fusion-brain-program-for-linux.html there are some steps undocumented in the repo. Will add as relevant files are also added.

Compile
=======
(for Ubuntu)

Ensure libusb0.1 is installed[1](http://www.mp3car.com/vbulletin/fusion-brain/129622-fusion-brain-program-for-linux.html#post1291726)

`sudo apt-get install libusb-dev libqt4-dev`

and compile

`qmake && make`


Copy `org.openice.fbd.service` to `/usr/share/dbus-1/system-services/org.openice.fbd.service`[2](http://www.mp3car.com/vbulletin/fusion-brain/129622-fusion-brain-program-for-linux-7.html#post1408437)


Copy `99-fusionbrain` to `/etc/udev/rules.d/99-fusionbrain`[2](http://www.mp3car.com/vbulletin/fusion-brain/129622-fusion-brain-program-for-linux-7.html#post1408437)


Copy `FusionBrain.conf` to `/etc/dbus-1/system.d/`[3](http://www.mp3car.com/fusion-brain/129622-fusion-brain-program-for-linux-3.html#post1322449)


From here, you should be able to plug in your Fusion Brain v3 and turn on output 1:

`dbus-send --session --print-reply --dest="org.openice.fbd" /org/openice/fbd org.openice.fbd.fusionbrain.SetSingleOutput int16:1 boolean:false`[4](http://www.mp3car.com/vbulletin/fusion-brain/129622-fusion-brain-program-for-linux-2.html#post1318001)