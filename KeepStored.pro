TEMPLATE = app
TARGET = keep-stored
VERSION = 1.0.0
CONFIG += qt warn_on debug
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

unix {
	# FreeBSD and Mac OS X
	INCLUDEPATH += /usr/local/include
	INCLUDEPATH += /usr/local/include/libxml2
	INCLUDEPATH += /usr/local/include/xmlsec1
	INCLUDEPATH += /usr/include/libxml2
	INCLUDEPATH += /usr/include/xmlsec1
}

!windows {
	LIBS += -lxml2 \
					-lsystools \
					-lxmlsec1 \
					-lxmlsec1-openssl
}
