#include "Game.h"
#include "charbuffer.h"
#include "Figure.h"
#include "Player.h"
#include "HorizontalEnemy.h"
#include "VerticalEnemy.h"
#include "DiagonalEnemy.h"
#include "conio.h"
#include <time.h> 
#include "Network/ServerEngine.h"
#include <QObject>
#include <QEventLoop>
#include <QCoreApplication>

void Game::EndgameScreen()
{
    cout << "#####################" << endl;
    cout << "#                   #" << endl;
    cout << "#  Are u a Wizard?  #" << endl;
    cout << "#                   #" << endl;
    cout << "#####################" << endl;
}

void Game::GameLoop(Player *_player, vector <Figure*> &_enemies, CharBuffer *_buffer) {
    cout << "GameLoop" << endl;
    char input = ' ';

    system("cls");
    _buffer->Render();

    while (input != 'p') {		// Loop
        input = getch();

        //-------------------------------------------------
        for (unsigned i = 0; i <_enemies.size(); i++) {
            _enemies.at(i)->Movement();
        }


        //------------------------------------------------
        if (_player->Control(input, _enemies)) {
            input = 'p';
            break;
        }


        //-----------------------------------------------------
        for (unsigned i = 0; i < _player->GetProjectiles().size(); i++) {
            _player->GetProjectiles().at(i)->Movement(_enemies);
        }



        //---------------------------------------------------
        _buffer->Render();
        if (_enemies.size() == 0) {
            input = 'p';
            system("cls");
            EndgameScreen();
            break;
        }



    }
}


void Game::CreateEnemies(vector <Figure*> &_enemies, CharBuffer *_buffer){

    int hor=1, ver=1, dia=1;

    cout << "Anzahl Horizontaler Gegner: ";
    cin >> hor;

    cout << "Anzahl Vertikaler Gegner: ";
    cin >> ver;

    cout << "Anzahl Diagonale Gegner: ";
    cin >> dia;

    for (int i = 0; i < hor; i++) {
        _enemies.push_back( new HorizontalEnemy('H', _buffer));
    }

    for (int i = 0; i < ver; i++) {
        _enemies.push_back(new VerticalEnemy('V', _buffer));
    }

    for (int i = 0; i < dia; i++) {
        _enemies.push_back(new DiagonalEnemy('D', _buffer));
    }
}

Game::Game(ServerEngine* server, QCoreApplication *parent)
    : QObject(parent)
{
    server_ = server;
}

void Game::PlayGame()
{

    CharBuffer* buffer = new CharBuffer(server_,50, 25);
    Player *player = new Player('P', buffer);
    vector <Figure*> enemies;
    srand(time(NULL));
    CreateEnemies(enemies, buffer);
    CreateObstacles(buffer);
    GameLoop(player, enemies, buffer);


    delete buffer;
    delete player;

    emit finished();
}


void Game::CreateObstacles(CharBuffer *_buffer) {
    int x = _buffer->GetSizeX() - 4;
    int y = _buffer->GetSizeY() - 4;
    int count = (_buffer->GetSizeX() * _buffer->GetSizeY()) / 50;

    for (int i = 0; i < count; i++) {
        _buffer->SetCharAt(rand() % x + 2, rand() % y + 2, '#');
    }
}
























