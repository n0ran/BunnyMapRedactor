#-------------------------------------------------
#
# Project created by QtCreator 2012-10-21T15:11:09
#
#-------------------------------------------------

QT       += core gui widgets xml

TARGET = BunnyMapRedactor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    helper.cpp \
    xml.cpp \
    plist.cpp \
    mapsizedialog.cpp

HEADERS  += mainwindow.h \
    helper.h \
    xml.h \
    plist.h \
    mapsizedialog.h \
    build.h

FORMS    += mainwindow.ui \
    mapsizedialog.ui

RESOURCES += \
    resources.qrc
