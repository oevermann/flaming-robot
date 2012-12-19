#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include "daten.h"

class ServerThread : public QThread
{
    Q_OBJECT

public:
    explicit ServerThread(int ID,Daten *data, QObject *parent = 0);
    ~ServerThread();
    void run();
    
signals:
    void error(QTcpSocket::SocketError socketerror);

public slots:
    void readyRead();
    void disconnected();

private:
    Daten *data;
    QTcpSocket *socket;
    int socketDescriptor;
};

#endif // SERVERTHREAD_H
