#include "clientthread.h"

//anlegen des sockets und der daten

ClientThread::ClientThread(QTcpSocket* socket,Daten *data, QObject *parent) :
    QThread(parent)
{
    this->data = data;
    this->socket = socket;
    this->execute = true;
}
//start des Threads und ausführen der funktion sendMessage()
void ClientThread::run()
{
    while(execute)
    {
        sendMessage();
        msleep(600);
    }
}
//bitweise addition der Steuerdaten und senden zum Host
void ClientThread::sendMessage()
{
    quint32 out = 0;
    out = data->getRoll();
    out = out << 8;
    out |= data->getNick();
    out = out << 8;
    out |= data->getYaw();
    out = out << 8;
    out |= data->getAccelerate();

    QByteArray *block = new QByteArray;
    block-> setNum(out);
    socket-> write(*block);

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

