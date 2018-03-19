#include "messages.h"
#include <iostream>

//Message::Message( const uint8_t cmd_parameter,
//                  const uint8_t dlc_parameter)
//    :_cmd_parameter(cmd_parameter), _dlc_parameter(dlc_parameter)
//{

//}

Message::Message()
{

}

Parameter::Parameter(const uint8_t cmd_parameter, const uint8_t dlc_parameter)
    : Message(cmd_parameter, dlc_parameter)
{

}

GameStart::GameStart()
{

}

Shot::Shot()
    : Message(0x03, 0x02)
{

}

AnswerGame::AnswerGame()
{

}

ShotAnswer::ShotAnswer()
{

}

IdentificationGroup::IdentificationGroup()
{

}

