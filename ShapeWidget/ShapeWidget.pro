#-------------------------------------------------
#
# Project created by QtCreator 2010-07-22T16:00:46
#
#-------------------------------------------------

TARGET = demo5
TEMPLATE = app
QT       += core gui network

SOURCES += main.cpp\
        shapewidget.cpp \
    v4l2grab.cpp

HEADERS  += shapewidget.h \
    v4l2grab.h

RESOURCES += \
    res.qrc

OTHER_FILES += \
    deskicon.rc
RC_FILE = deskicon.rc




