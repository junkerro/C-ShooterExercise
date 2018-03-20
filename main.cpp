#include <QCoreApplication>
#include "Network/ServerEngine.h"
#include "Network/ClientEngine.h"
#include "Game/Game.h"
#include <QHostAddress>
#include <QString>
#include <iostream>
#include <string>
#include <thread>
#include <QObject>
#include <QTimer>

using namespace std;

int Menu();
void RunClient(QCoreApplication* app);
void RunServer(QCoreApplication* app);

thread* gameThread = nullptr;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int eingabe = 1;

    //while (eingabe != 0) {
        eingabe = Menu();
        switch (eingabe) {
        case 1: {
            RunServer(&a);
            break;
        }
        case 2:
            RunClient(&a);
            break;
        case 3:
            cout << "CIAO!";
            eingabe = 0;
            break;
        default: cout << "Wählen Sie ein der oben aufgeführten Optionen aus";
        }
    //}

    return a.exec();
}


int Menu() {
    int eingabe;
    cout << endl << "#####################" << endl;
    cout << "Menue:" << endl;
    cout << "(1) Start Game!" << endl;
    cout << "(2) Connect to Game" << endl;
    cout << "(3) Quit..." << endl;
    cout << "#####################" << endl;
    cout << "Eingabe:";
    cin >> eingabe;
    cout << "#####################" << endl;
    return eingabe;
}

void RunClient(QCoreApplication* app)
{
    // Will automtically be destroyed once the Application Class is destroyed
    auto client = new ClientEngine(app);
    string hostAddress;
    cout << "To where do you want to connect? ";

    cin.ignore();
    getline(cin,hostAddress);

    cout << "Connecting to " << hostAddress << endl;
    client->Connect(QHostAddress(QString(hostAddress.data())),8888);
}

void RunServer(QCoreApplication* app)
{
    //Creating and initializing the Server
    auto initPkg = new InitPacket(50,25);
    initPkg->Build();
    auto server = new ServerEngine(initPkg);
    server->BeginHosting(8888);

    auto gameTask = new Game(server,app);

    QObject::connect(gameTask, SIGNAL(finished()), app, SLOT(quit()));

    gameThread = new thread([&] {gameTask->PlayGame();});
}
































