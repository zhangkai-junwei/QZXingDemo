#-------------------------------------------------
#
# Project created by QtCreator 2020-08-21T16:54:03
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qCamera
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    videiosurface.cpp

HEADERS  += dialog.h \
    videiosurface.h

FORMS    += dialog.ui

include(qzxing/src/QZXing.pri)

