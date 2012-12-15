#include "client.h"

Client::Client(Daten *data,QObject *parent) :
    QObject(parent)
{
    this->data = data;
    tcpSocket = new QTcpSocket(this);
    connected = false;
    connect(this,SIGNAL(socketConnected()),this,SLOT(sendMessage()));

}

Client::~Client()
{
    tcpSocket->close();
    delete data;
    delete tcpSocket;
}


void Client::connectSocket(QString address, int port, QString name)
{
    tcpSocket->abort();
    try
    {
        tcpSocket->connectToHost(address,port);
    }
    catch(...)
    {

    }

    tcpSocket->waitForConnected(500);

    if(tcpSocket->state() == QAbstractSocket::ConnectedState)
    {
        connected = true;
        emit socketConnected();
    }
    else
    {
        emit connectionError("Es konnte keine Verbindung zum Server aufgebaut werden.");
    }

}

void Client::sendMessage()
{
    if (connected)
    {
        thread = new ClientThread(tcpSocket,data);
        connect(thread, SIGNAL(finished()),this,SLOT(deleteLater()));
        thread->start();
    }
}

void Client::disconnect()
{
    thread->stop();
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
}



