#-------------------------------------------------
#
# Project created by QtCreator 2018-03-14T15:57:43
#
#-------------------------------------------------

QT       += core
QT       -= gui

# greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BattleShip
TEMPLATE = app


SOURCES += main.cpp\
           ship.cpp\
           board.cpp\
           game.cpp

HEADERS += datatypes.hpp\
           ship.hpp\
           board.hpp\
           game.hpp

CONFIG  += c++14
CONFIG  += console

CONFIG  -= app_bundle
