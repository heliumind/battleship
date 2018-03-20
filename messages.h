#ifndef SHOT_H
#define SHOT_H


#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include "datatypes.hpp"

//class for the first message the parameters

class Message
{
public:
    Message( uint8_t cmd, uint8_t dlc);
    virtual ~Message() = default;

             const uint8_t _cmd;
             const uint8_t _dlc;
};


class Parameter: public Message
{
public:
    Parameter(uint8_t cmd,uint8_t dlc);

    uint8_t _field_x = 0x0A;
    uint8_t _field_y = 0x0A;
    uint8_t _n_battleship = 0x00;
    uint8_t _n_cruiser = 0x00;
    uint8_t _n_destroyer = 0x00;
    uint8_t _n_submarine = 0x00;


    //slot for interface with logic
//public slots:

//    void getParameterData(uint8_t x_field, uint8_t y_field, uint8_t n_b, uint8_t n_c, uint8_t n_d, uint8_t n_s);
};

//clas for the second message; question gamestart

class GameStart: public Message
{
public:

    GameStart(uint8_t cmd,uint8_t dlc);

};


//class for the third message; the shot
class Shot: public Message
{
public:

    Shot(uint8_t cmd,uint8_t dlc);

    //coordinates have to change!!
    uint8_t _coordinates_x = 0x00;
    uint8_t _coordinates_y = 0x00;

};

class AnswerGame: public Message
{
public:
    AnswerGame(uint8_t cmd,uint8_t dlc);

    // status has to change!
    uint8_t _status = 0x00;
};

//class for the fifth message; the shot answer
class ShotAnswer: public Message
{
public:

    ShotAnswer(uint8_t cmd,uint8_t dlc);


    uint8_t _status = 0x00;
    position _position;
    //void getStatus(uint8_t status_logic);

};

class IdentificationGroup: public Message
{
public:

    IdentificationGroup(uint8_t cmd,uint8_t dlc);


    uint8_t _groupNumber = 0x00;

};


#endif // SHOT_H
