#-------------------------------------------------
#
# Project created by QtCreator 2015-03-10T15:34:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Panja
TEMPLATE = app

CONFIG += c++11
QMAKE_CXXFLAGS+= -std=c++11
QMAKE_LFLAGS +=  -std=c++11

SOURCES += main.cpp\
    ptreetextitem.cpp \
    ptextedit.cpp \
    pspellchecker.cpp \
    mainwindow.cpp \
    pstatsdialog.cpp \
    pconfirmclose.cpp

HEADERS  += \
    ptreetextitem.h \
    ptextedit.h \
    pspellchecker.h \
    mainwindow.h \
    pstatsdialog.h \
    pconfirmclose.h

FORMS    += \
    mainwindow.ui \
    pstatsdialog.ui \
    pconfirmclose.ui
