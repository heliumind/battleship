QT += core network widgets

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
    mytcpserver.cpp

HEADERS += \
	board.hpp \
	control.h \
        game.hpp \
        ship.hpp \
    datatypes.hpp \
    messages.h \
    myclient.h \
    mytcpserver.h

CONFIG += c++14

CONFIG += console

CONFIG -= app_bundle

FORMS +=
