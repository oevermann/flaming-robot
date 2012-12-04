#include "serverthread.h"

ServerThread::ServerThread(int ID, Daten *data, QObject *parent):
    QThread(parent)
{
    this->socketDescriptor = ID;
    this->data = data;
}

void ServerThread::run()
{
    //thread starts here
    qDebug() << socketDescriptor << "Starting thread";

    socket = new QTcpSocket();
    if (!socket->setSocketDescriptor(this->socketDescriptor))
    {
        emit error(socket->error());
        return;
    }

    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()),Qt::DirectConnection);
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()),Qt::DirectConnection);

    qDebug() << socketDescriptor << "Client Connected";

    exec();
}

void ServerThread::readyRead()
{
    QByteArray in = socket->readAll();

    qDebug() << socketDescriptor << "Data in" << in;

    QString ein = QString(in);

    if (ein.startsWith("LAT:"))
    {
        //geographische Breite
        qDebug() << ein.mid(4, ein.length()-1).toDouble();
    }
    else if (ein.startsWith("LON:"))
    {
        //geographische Länge
        qDebug() << ein.mid(4, ein.length()-1).toDouble();
    }
    else if (ein.startsWith("PIT:"))
    {
        //Winkel im die Querachse
        qDebug() << ein.mid(4, ein.length()-1).toDouble();
    }
    else if (ein.startsWith("BNK:"))
    {
        //Winkel um die Längsachse
        qDebug() << ein.mid(4, ein.length()-1).toDouble();
    }
    else if (ein.startsWith("THG:"))
    {
        //Winkel um die Hochachse bezogen auf geographisch Nord
        qDebug() << ein.mid(4, ein.length()-1).toDouble();
    }
    else if (ein.startsWith("TCS:"))
    {
        //Flugrichtung bezogen auf geographisch Nord
        qDebug() << ein.mid(4, ein.length()-1).toDouble();
    }
    else if (ein.startsWith("ALT:"))
    {
        //Höhe
        qDebug() << ein.mid(4, ein.length()-1).toDouble();
    }
    else if (ein.startsWith("TAS:"))
    {
        //Geschwindigkeit gegenüber Luft
        qDebug() << ein.mid(4, ein.length()-1).toDouble();
    }
    else if (ein.startsWith("GSP:"))
    {
        //Geschwindigkeit über Grund
        qDebug() << ein.mid(4, ein.length()-1).toDouble();
    }
    else if (ein.startsWith("WVE:"))
    {
        //Windrichtung bezogen auf geographisch Nord
        qDebug() << ein.mid(4, ein.length()-1).toDouble();
    }
    else if (ein.startsWith("WSP:"))
    {
        //Windgeschwindigkeit
        qDebug() << ein.mid(4, ein.length()-1).toDouble();
    }
    else if (ein.startsWith("DMY:"))
    {
        //sende nichts
        qDebug() << ein.mid(4, ein.length()-1).toDouble();
    }
    else if (ein.startsWith("HLO:"))
    {
        //Hallo + optionale Nachricht
        qDebug() << ein.mid(4, ein.length()-1).toDouble();
    }
    else if (ein.startsWith("MSG:"))
    {
        //message
        qDebug() << ein.mid(4, ein.length()-1).toDouble();
    }
    else if (ein.startsWith("CLS:"))
    {
        //close + optionale Nachricht
        qDebug() << ein.mid(4, ein.length()-1).toDouble();
    }


    //socket->write(data);

}

void ServerThread::disconnected()
{
    qDebug() << socketDescriptor << "Disconnect";

    socket->deleteLater();
    exit(0);
}
