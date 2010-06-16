TEMPLATE = app
TARGET = KeepStored
VERSION = 1.0.0
CONFIG += qt warn_on
QT += gui

# Debug

debug {
	CONFIG += console
}

# General configuration

MOC_DIR = auto/moc
UI_DIR = auto/ui
RCC_DIR = auto/resources
OBJECTS_DIR = bin
QMAKE_EXT_H = .hpp

SOURCES += src/main.cpp \
	src/gui/*.cpp \
	src/backend/*.cpp
HEADERS += src/gui/*.hpp \
	src/backend/*.hpp
FORMS +=
RESOURCES += resources/icons.qrc

