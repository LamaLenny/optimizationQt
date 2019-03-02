#-------------------------------------------------
#
# Project created by QtCreator 2019-02-20T18:23:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = opt
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    Stop_cr.cpp \
    rand_search.cpp \
    my_vector.cpp \
    FUN_vec.cpp \
    F_R_optimize.cpp \
    com_rand.cpp \
    painter.cpp

HEADERS += \
        mainwindow.h \
    brent.hpp \
    Stop_cr.h \
    rand_search.h \
    my_vector.h \
    mainwindow.h \
    FUN_vec.h \
    F_R_optimize.h \
    com_rand.h \
    painter.h \
    Args.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
