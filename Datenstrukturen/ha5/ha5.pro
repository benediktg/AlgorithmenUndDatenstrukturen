# QMake project file
TEMPLATE = app console
QT -= gui core
CONFIG += debug
TARGET = a.out

SOURCES += src/*.cpp

HEADERS += include/*.hpp
