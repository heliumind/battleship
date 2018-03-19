QT += core network gui widgets

TARGET = BattleShip
TEMPLATE = app

SOURCES += \
	board.cpp \
	game.cpp \
	main.cpp \
	control.cpp \
    ship.cpp \
    messages.cpp \
    myclient.cpp \
    mytcpserver.cpp \
    button.cpp\
gui.cpp

HEADERS += \
	board.hpp \
	control.h \
        game.hpp \
        ship.hpp \
    datatypes.hpp \
    messages.h \
    myclient.h \
    mytcpserver.h \
    gui.h \
    button.h

CONFIG += c++14

#CONFIG += console

#CONFIG -= app_bundle

FORMS += \
    gui.ui
