#include "ClientEngine.h"
#include <QIODevice>
#include <QAbstractSocket>
#include "Initpacket.h"
#include <iostream>
#include "Datapacket.h"

using namespace std;

ClientEngine::ClientEngine(QObject *parent) :
    QObject(parent)
{
    buffer_ = new CharBuffer();
    socket_ = new QTcpSocket(this);
    connect(socket_, SIGNAL(connected()), this, SLOT(Connected()));
    connect(socket_, SIGNAL(disconnected()), this, SLOT(HandleDisconnected()));
    connect(socket_, SIGNAL(readyRead()), this, SLOT(ReadyRead()));
}

ClientEngine::~ClientEngine()
{
    if(socket_ != nullptr)
        socket_->disconnect();

    delete buffer_;
}

void ClientEngine::Connect(const QHostAddress &addr, const ushort port)
{
    socket_->connectToHost(addr,port);
}

void ClientEngine::ReadyRead()
{
    auto qbyteArray = socket_->readAll();
    auto byteArray = new vector<uint8_t>(qbyteArray.begin(),qbyteArray.end());
    auto initPkg = InitPacket::ParsePacket(byteArray);

    if(initPkg == nullptr)
    {
        auto dataPkg = DataPacket::ParsePacket(byteArray);
        if(dataPkg == nullptr)
            return;

        buffer_->SetData(dataPkg->GetPayload());
        buffer_->Render();
    }
    else
    {
        buffer_->SetSize(initPkg->GetSizeX(),initPkg->GetSizeY());
    }

}

void ClientEngine::HandleDisconnected()
{
    cout << "Disconnected";
    socket_->close();
    delete socket_;
    exit(0);
}

void ClientEngine::Connected()
{
    cout << "Connected";
}






























