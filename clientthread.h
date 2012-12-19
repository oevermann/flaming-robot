#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include "daten.h"


class ClientThread : public QThread
{
    Q_OBJECT

public:
    explicit ClientThread(QTcpSocket* socket,Daten *data,QObject *parent = 0);
    ~ClientThread();
    void run();
    void stop();
    void sendMessage();

private:
    QTcpSocket *socket;
    bool execute;
    Daten *data;
};

#endif // CLIENTTHREAD_H
