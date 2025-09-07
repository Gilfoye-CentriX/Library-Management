#-------------------------------------------------
#
# Project created by Mani Dlamini #46176926
#
#-------------------------------------------------

QT       -= gui

TARGET = LibraryUtils
TEMPLATE = lib

# Enable C++11
CONFIG += c++11

# Allow both shared and static builds (default: shared)
# To build static: qmake CONFIG+=staticlib
# To build shared: qmake CONFIG+=shared
CONFIG += shared

# Export/import macro
DEFINES += LIBRARYUTILS_LIBRARY

# Source and header files for this library
SOURCES += \
    libraryutils.cpp \
    $$PWD/../book.cpp \
    $$PWD/../libraryitem.cpp \
    $$PWD/../magazine.cpp \
    $$PWD/../librarystorage.cpp

HEADERS += \
    libraryutils.h \
    $$PWD/../book.h \
    $$PWD/../libraryitem.h \
    $$PWD/../magazine.h \
    $$PWD/../librarystorage.h

# Include parent folder for headers
INCLUDEPATH += $$PWD/..

# Install path for Unix/Linux
unix {
    target.path = /usr/lib
    INSTALLS += target
}
