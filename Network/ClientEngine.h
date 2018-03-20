#pragma once

#include <QObject>
#include <QHostAddress>
#include <QTcpSocket>
#include "Game/charbuffer.h"


class ClientEngine : public QObject
{
  Q_OBJECT

public:
	explicit ClientEngine(QObject* parent = 0);
	~ClientEngine();

   void Connect(QHostAddress const & addr, ushort const port);


private:
   QTcpSocket* socket_;
   CharBuffer* buffer_;


private slots:
    void ReadyRead();
    void HandleDisconnected();
    void Connected();

};

