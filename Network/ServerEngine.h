#pragma once

#include <memory>
#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>
#include "Initpacket.h"
#include <QSharedPointer>

using namespace std;

class ServerEngine : protected QObject
{
  Q_OBJECT
public:
    explicit ServerEngine(InitPacket* initPkg, QObject* parent = 0);
	~ServerEngine();

	void BeginHosting(short port);
	bool IsRunning();
	void BroadcastMessage(char const * const data, int const length);
    void CheckForNewConnections();

private:
    QTcpServer* tcpServer_;
	vector<QTcpSocket*>* activeClients_;
    InitPacket* initPkg_;

signals:
    void SendData(char const * data, int const length);

private slots:
	void acceptConnection();
	void removeConnection(QTcpSocket* socket);
    void SendDataSlot(char const * data, int const length);


};

