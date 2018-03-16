QT += core 
QT += network
QT -= gui

TARGET = BattleShip
TEMPLATE = app

SOURCES += mytcpserver.cpp \
	massages.cpp \
	board.cpp \
	game.cpp \
	main.cpp \
	control.cpp \
	myclient.cpp \
    ship.cpp

HEADERS += myclient.h \
	mytcpserver.h \
	messages.h \
	board.hpp \
	control.h \
        game.hpp \
        ship.hpp \
    datatypes.hpp

CONFIG += c++14
CONFIG += console

CONFIG -= app_bundle
