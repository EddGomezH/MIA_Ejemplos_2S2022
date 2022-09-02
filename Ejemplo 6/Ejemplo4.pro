QT += core
QT -= gui

CONFIG += c++11

TARGET = Ejemplo4
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    nodo.cpp \
    scanner.cpp \
    parser.cpp \
    analizador.cpp \
    comando.cpp

DISTFILES += \
    ALexico.l \
    ASintactico.y

HEADERS += \
    nodo.h \
    scanner.h \
    parser.h \
    analizador.h \
    comando.h
