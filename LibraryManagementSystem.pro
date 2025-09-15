#-------------------------------------------------
#
# Project created by Mani Dlamini #46176926
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# Source files for the application only
SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

# Link with the LibraryUtils library
INCLUDEPATH += $$PWD/LibraryUtils
DEPENDPATH += $$PWD/LibraryUtils

# Output folder of LibraryUtils
debug {
    LIBS += -L$$PWD/build-LibraryUtils-Desktop_Qt_5_3_0_MinGW_32bit-Debug/debug -lLibraryUtils
} else {
    LIBS += -L$$PWD/build-LibraryUtils-Desktop_Qt_5_3_0_MinGW_32bit-Release/release -lLibraryUtils
}
