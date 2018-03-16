#include "messages.h"
#include <iostream>

Message::Message( const uint8_t cmd_parameter,
                  const uint8_t dlc_parameter)
    :_cmd_parameter(cmd_parameter), _dlc_parameter(dlc_parameter)
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

