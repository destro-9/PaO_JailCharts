#-------------------------------------------------
#
# Project created by QtCreator 2022-02-27T02:20:32
#
#-------------------------------------------------

QT       += core gui
QT       += charts
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = progetto
TEMPLATE = app

ROOT = $$PWD
EXEC = $${ROOT}/JailCharts
BUILD = $${EXEC}/build

DESTDIR = $${EXEC}
QMAKE_QMAKE = $${EXEC}
OBJECTS_DIR = $${BUILD}/obj
MOC_DIR = $${BUILD}/moc
RCC_DIR = $${BUILD}/rcc

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    data.cpp \
    values.cpp \
    table.cpp \
    model.cpp \
    chart.cpp \
    barchart.cpp \
    linechart.cpp \
    scatterchart.cpp \
    areachart.cpp \
    piechart.cpp \
    controller.cpp \
    newwindow.cpp \
    inputform.cpp \
    rename.cpp

HEADERS += \
        mainwindow.h \
    data.h \
    values.h \
    table.h \
    model.h \
    chart.h \
    barchart.h \
    linechart.h \
    scatterchart.h \
    areachart.h \
    piechart.h \
    controller.h \
    newwindow.h \
    inputform.h \
    rename.h

RESOURCES += \
    icon.qrc
