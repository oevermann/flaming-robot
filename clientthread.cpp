#include "clientthread.h"

ClientThread::ClientThread(QTcpSocket* socket,Daten *data, QObject *parent) :
    QThread(parent)
{
    this->data = data;
    //mutex = new mutex;
    this->socket = socket;
    this->execute = true;
}

void ClientThread::run()
{
    while(execute)
    {
        sendMessage();
        msleep(500);
    }
}

void ClientThread::sendMessage()
{
    QMutexLocker locker(mutex);
    QString message1 = "Hallo";
    QByteArray *block = new QByteArray;
    block->append(message1);
    socket->write(*block);
    delete block;
}

void ClientThread::stop()
{
    execute = false;
}

