#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include "clientthread.h"
#include "daten.h"

class Client : public QObject
{
    Q_OBJECT
    QTcpSocket *tcpSocket;
    ClientThread *thread;
    Daten *data;
    bool connected;
public:
    explicit Client(Daten* data,QObject *parent = 0);
    ~Client();
    void connectSocket(QString address, int port, QString name);


signals:
    void socketConnected();
    void connectionError(QString error);

public slots:
    void disconnect();

private slots:
    void sendMessage();
};

#endif // CLIENT_H
