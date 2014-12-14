# -------------------------------------------------
# Project created by QtCreator 2009-04-20T12:05:50
# -------------------------------------------------
QT += dbus
QT -= gui
TARGET = fbd
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
unix:LIBS += -lusb

QTDIR_build:REQUIRES="contains(QT_CONFIG, small-config)"

unix:BIN_DIR = $$DESTDIR/usr/bin
unix:DATA_DIR = $$DESTDIR/usr/share/$${TARGET}
unix:target.path = $$BIN_DIR

dbus.files = FusionBrain.conf
unix:dbus.path = $$DESTDIR/etc/dbus-1/system.d/

unix:data.path = $${DATA_DIR}
data.files = fbddbus.xml LICENCE.txt

unix:INSTALLS += target
unix:INSTALLS += dbus
unix:INSTALLS += data

SOURCES += main.cpp \
    fbddbus.cpp \
    fb.cpp \
    fbd.cpp \
    fblib.cpp
HEADERS += fbddbus.h \
    fb.h \
    fbd.h \
    fblib.h
OTHER_FILES += fbddbus.xml \
    FusionBrain.conf \
    LICENSE.txt
