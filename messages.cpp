#include "messages.h"
#include <iostream>

Message::Message(uint8_t cmd, uint8_t dlc)
    : _cmd(cmd), _dlc(dlc)
{

}



Parameter::Parameter(uint8_t cmd,uint8_t dlc)
    : Message(cmd, dlc)
{

}

GameStart::GameStart(uint8_t cmd,uint8_t dlc)
    : Message(cmd, dlc)
{

}

Shot::Shot(uint8_t cmd,uint8_t dlc)
    : Message(cmd, dlc)
{

}

AnswerGame::AnswerGame(uint8_t cmd,uint8_t dlc)
    : Message(cmd, dlc)
{

}

ShotAnswer::ShotAnswer(uint8_t cmd,uint8_t dlc)
    : Message(cmd, dlc)
{

}

IdentificationGroup::IdentificationGroup(uint8_t cmd,uint8_t dlc)
    : Message(cmd, dlc)
{

}

Chat::Chat(uint8_t cmd, uint8_t dlc)
    :Message(cmd, dlc)
{

}
