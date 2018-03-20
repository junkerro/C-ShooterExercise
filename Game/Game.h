#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include <iostream>
#include "charbuffer.h"
#include "Figure.h"
#include <QObject>
#include <QCoreApplication>

class Game : public QObject
{
    Q_OBJECT

public:
    explicit Game(ServerEngine* server,QCoreApplication* parent = 0);
    ~Game(){}

public slots:
    void PlayGame();

signals:
    void finished();

private:
    ServerEngine* server_ = nullptr;

    void EndgameScreen();
    void GameLoop(Player *_player, vector <Figure*> &_enemies, CharBuffer *_buffer);
    void CreateEnemies(vector <Figure*> &_enemies, CharBuffer *_buffer);
    void CreateObstacles(CharBuffer *_buffer);

};

#endif // GAME_H
