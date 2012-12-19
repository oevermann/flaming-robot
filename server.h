#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QDebug>
#include "serverthread.h"
#include "daten.h"

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(Daten *data, QObject *parent = 0);
    ~Server();
    void startServer();

protected:
    void incomingConnection(int socketDescriptor);

private:
    Daten *data;
};

#endif // SERVER_H
