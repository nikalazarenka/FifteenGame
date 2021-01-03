QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fifteen
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11\
            resources_big

SOURCES += \
        help.cpp \
        main.cpp \
        fifteen.cpp \
        records.cpp

HEADERS += \
        fifteen.h \
        help.h \
        records.h

FORMS += \
        fifteen.ui \
        help.ui \
        records.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
