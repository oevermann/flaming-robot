#include "client.h"

//nimmt das datenobjekt entgegen und legt einen tcpSocket an
Client::Client(Daten *data,QObject *parent) :
    QObject(parent)
{
    this->data = data;
    tcpSocket = new QTcpSocket(this);
    connected = false;
    QObject::connect(this,SIGNAL(socketConnected()),this,SLOT(sendMessage()));
}

Client::~Client()
{
    tcpSocket->close();
    delete data;
    delete tcpSocket;
}

//Verbindungsaufbau zu host unter Adresse: address und mit dem Port: port
void Client::connectSocket(QString address, int port)
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

    if(tcpSocket->state() == QTcpSocket::ConnectedState)
    {
        connected = true;
        emit socketConnected();
    }
    else
    {
        emit connectionError("Es konnte keine Verbindung zum Server aufgebaut werden.");
    }
}

//startet den Thread zum senden der Steuerdaten
void Client::sendMessage()
{
    if (connected)
    {
        thread = new ClientThread(tcpSocket,data);
        connect(thread, SIGNAL(finished()),this,SLOT(deleteLater()));
        thread->start();
    }
}

//schließt die Verbindung zum Host
void Client::disconnect()
{
    thread->stop();
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
}



