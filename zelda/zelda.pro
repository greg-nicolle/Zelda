#-------------------------------------------------
#
# Project created by QtCreator 2014-10-01T16:04:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zelda
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    map.cpp \
    personnage.cpp \
    link.cpp \
    mechant.cpp \
    controler.cpp \
    item.cpp \
    mapitem.cpp

HEADERS  += widget.h \
    map.h \
    personnage.h \
    link.h \
    mechant.h \
    mapview.h \
    controler.h \
    item.h \
    mapitem.h

FORMS    += widget.ui
