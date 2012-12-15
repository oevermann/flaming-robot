#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QMutex>
#include <QMutexLocker>
#include "daten.h"


class ClientThread : public QThread
{
    Q_OBJECT
    QTcpSocket *socket;
    bool execute;
    Daten *data;

public:
    explicit ClientThread(QTcpSocket* socket,Daten *data,QObject *parent = 0);
    ~ClientThread();
    void run();
    void stop();
    void sendMessage();

signals:

public slots:

};

#endif // CLIENTTHREAD_H
