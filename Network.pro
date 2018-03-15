QT += core
QT -= gui
QT += network

TARGET = Network
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    myclient.cpp \
    mytcpserver.cpp \
    main_test.cpp

HEADERS += \
    myclient.h \
    mytcpserver.h

