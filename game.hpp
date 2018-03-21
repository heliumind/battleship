#ifndef GAME_HPP
#define GAME_HPP

#include <QCoreApplication>
#include "datatypes.hpp"
#include "board.hpp"
#include "ship.hpp"
#include "messages.h"

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(QObject *parent = 0);
    Game(Game&&);
    Game(Game&) = default;
    bool    get_win() const;
    void    update_myturn();
    Board   getBoard() const;
    void    checkWin();
    // void    receiveShot(const coordinates point);
    // void    receiveShotAnswer(const uint8_t code, position location);
    void    restart();
    Board   _matchboard;
private:
    bool    _win;
//    Board   _matchboard;
    Board   _enemyboard;
    bool    _myturn;
    uint8_t _statuscode;
    coordinates _lastShot;
    bool _start;

signals:
    // logic -> gui
    void    sendMyturn(bool);
    void    sendWin(bool);
    void    updateField(coordinates point, int flag, bool own);
    void    shipDestroyed(int size);

    // logic -> network (Message to send)
    void    sendParameter(Parameter &msg);
    void    sendGameStart(GameStart &msg);
    void    sendShot(Shot &msg);
    void    sendAnswerGame(AnswerGame &msg);
    void    sendShotAnswer(ShotAnswer &msg);
    // void    MessageSent(Message* msg);

    // logic -> controller


public slots:
    // logic -> network
    // void    receiveParameter(Parameter &msg);
    void    receiveGameStart();
    void    receiveShot(Shot &msg);
    void    receiveAnswerGame(AnswerGame &msg);
    void    receiveShotAnswer(ShotAnswer &msg);
    // void    receiveMessage(Message* msg);

    // logic -> gui
    void    start();
    void    sendShotGui(const coordinates point);
    void    setship(const position location);
};

#endif // GAME_HPP
