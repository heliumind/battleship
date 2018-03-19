QT += core 
QT += network
QT -= gui

TARGET = BattleShip
TEMPLATE = app

SOURCES += \
	board.cpp \
	game.cpp \
	main.cpp \
	control.cpp \
    ship.cpp

HEADERS += \
	messages.h \
	board.hpp \
	control.h \
        game.hpp \
        ship.hpp \
    datatypes.hpp

CONFIG += c++14
CONFIG += console

CONFIG -= app_bundle
