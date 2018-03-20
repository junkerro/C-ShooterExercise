#include "ServerEngine.h"
#include <QAbstractSocket>
#include <iostream>
#include "Initpacket.h"
#include "Datapacket.h"

using namespace std;


ServerEngine::ServerEngine(InitPacket* initPkg, QObject* parent) :
    QObject(parent)
{
    tcpServer_ = new QTcpServer();
    connect(tcpServer_,SIGNAL(newConnection()), this, SLOT(acceptConnection()));
    connect(this,SIGNAL(SendData(const char*,int)),this,SLOT(SendDataSlot(const char*,int)));
    activeClients_ = new vector<QTcpSocket*>();

    initPkg_ = initPkg;
}

ServerEngine::~ServerEngine()
{
    tcpServer_->close();
    delete tcpServer_;
    foreach (QTcpSocket* socket, *activeClients_) {
        socket->close();
        delete socket;
    }
    delete activeClients_;
}


void ServerEngine::BeginHosting(short const port)
{
    tcpServer_->listen(QHostAddress::AnyIPv4, port);

}

bool ServerEngine::IsRunning()
{
    return tcpServer_->isListening();
}

void ServerEngine::BroadcastMessage(const char * const data, int const length)
{
    emit SendData(data,length);
}

void ServerEngine::CheckForNewConnections()
{
    cout << "Has pending connections: " << tcpServer_->hasPendingConnections();
    while (tcpServer_->hasPendingConnections()) {
        acceptConnection();
    }
}


void ServerEngine::acceptConnection()
{
    cout << "Client Connected";
    QTcpSocket* socket = tcpServer_->nextPendingConnection();
    activeClients_->push_back(socket);
    connect(socket, &QTcpSocket::disconnected, [=](){ this->removeConnection(socket);});
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),[=](QAbstractSocket::SocketError socketError){ this->removeConnection(socket);});

    socket->write(reinterpret_cast<char*>(initPkg_->GetBuffer()->data()),9);
}

void ServerEngine::removeConnection(QTcpSocket *socket)
{
    if(socket == nullptr)
        return;

    auto iter = find(activeClients_->begin(),activeClients_->end(),socket);

    if(iter == activeClients_->end())
        return;

    cout << "Client Disconnected";


    activeClients_->erase(iter);
}

void ServerEngine::SendDataSlot(const char *data, const int length)
{
    auto pkg = new DataPacket(new vector<uint8_t>(data,data+length));
    pkg->Build();

    if(!activeClients_->empty())
        for(int i = 0; i < activeClients_->size(); i++)
        {
            activeClients_->data()[i]->write(reinterpret_cast<char*>(pkg->GetBuffer()->data()), pkg->GetBuffer()->size());
        }

    delete pkg;
}









































