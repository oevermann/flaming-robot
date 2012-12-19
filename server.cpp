#include "server.h"
#include <QDebug>


Server::Server(Daten *data, QObject *parent) :
    QTcpServer(parent)
{
    this->data = data;
}

//prüft ob der port bereits belegt ist, wenn nicht wird der port blockiert und der server horcht auf diesem port
void Server::startServer()
{
    if(!this->listen(QHostAddress::Any,1235))
    {
        qDebug() << "Could not start Server";
    }
    else
    {
        qDebug() << "Listening";
    }
}
//bei Verbindungsaufbau wird diese Funktion aufgerufen diese startet einen Thread der die einkommenden Daten entgegennimmt und
//verarbeitet
void Server::incomingConnection(int socketDescriptor)
{
    qDebug() << socketDescriptor << "Connecting";
    ServerThread *thread = new ServerThread(socketDescriptor,data,this);
    connect(thread, SIGNAL(finished()),this,SLOT(deleteLater()));
    thread->start();
}

Server::~Server()
{
    delete data;
}
