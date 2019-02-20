#-------------------------------------------------
#
# Project created by QtCreator 2015-01-15T15:55:50
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JasonQt_SerialPort
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        MainWindow.cpp \
    JasonQt/JasonQt_SerialPort.cpp

HEADERS  += MainWindow.h \
    JasonQt/JasonQt_SerialPort.h

FORMS    += MainWindow.ui
