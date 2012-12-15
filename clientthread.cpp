#include "clientthread.h"

ClientThread::ClientThread(QTcpSocket* socket,Daten *data, QObject *parent) :
    QThread(parent)
{
    this->data = data;
    mutex = new QMutex();
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

    quint32 out = 0;
    out = data->getRoll();
    out = out << 8;
    out |= data->getNick();
    out = out << 8;
    out |= data->getYaw();
    out = out << 8;
    out |= data->getAccelerate();
    qDebug() << out;

    QByteArray *block = new QByteArray;
    block-> setNum(out);
    socket-> write(*block);
    socket-> flush();

    delete block;
}

void ClientThread::stop()
{
    execute = false;
}

ClientThread::~ClientThread()
{
    delete data;
}

