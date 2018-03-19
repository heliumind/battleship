#ifndef SHOT_H
#define SHOT_H


#include <iostream>

//class for the first message the parameters

class Message
{
public:
    Message( const uint8_t _cmd_parameter,
             const uint8_t _dlc_parameter);

    const uint8_t _cmd_parameter = 0x01;
    const uint8_t _dlc_parameter = 0x06;

};


class Parameter: public Message
{
public:
    Parameter(const uint8_t _cmd_parameter,
              const uint8_t _dlc_parameter);

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

class GameStart
{
public:

    GameStart();
    uint8_t _cmd = 0x02;
    //was noch?
};


//class for the third message; the shot
class Shot : public Message
{
public:

    Shot();
    uint8_t _cmd = 0x02;
    uint8_t _dlc = 0x02;
    //coordinates have to change!!
    uint8_t _coordinates_x = 0x00;
    uint8_t _coordinates_y = 0x00;

};

class AnswerGame
{
public:
    AnswerGame();
    uint8_t _cmd = 0x10;
    uint8_t _dlc = 0x01;
    // status has to change!
    uint8_t _status = 0x00;
};

//class for the fifth message; the shot answer
class ShotAnswer
{
public:

    ShotAnswer();
    uint8_t _cmd = 0x11;
    uint8_t _dlc = 0x03; //variable!!!
    uint8_t _status = 0x00;
    uint8_t _coordinates_x = 0x00;
    uint8_t _coordinates_y = 0x00;

    void getStatus(uint8_t status_logic);

};

class IdentificationGroup
{
public:
    IdentificationGroup();
    uint8_t _cmd = 0x80;
    uint8_t _dlc = 0x01;
    uint8_t _groupNumber = 0x00;

};


#endif // SHOT_H
