#include "server.h"
#include <QDebug>


Server::Server(Daten *data, QObject *parent) :
    QTcpServer(parent)
{
    this->data = data;
}

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
