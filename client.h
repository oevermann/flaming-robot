#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include "clientthread.h"
#include "daten.h"

class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client(Daten* data,QObject *parent = 0);
    ~Client();
    void connectSocket(QString address, int port);

signals:
    void socketConnected();
    void connectionError(QString error);

public slots:
    void disconnect();

private slots:
    void sendMessage();

private:
    QTcpSocket *tcpSocket;
    ClientThread *thread;
    Daten *data;
    bool connected;
};

#endif // CLIENT_H
