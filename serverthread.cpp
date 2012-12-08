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

    //QMutexLocker locker(&mutex);

    qDebug() << socketDescriptor << "Data in" << in;

    QString ein = QString(in);

    if (ein.startsWith("LAT:"))
    {
        //geographische Breite
        data->setFlugdaten(0, ein.mid(4, ein.length()-1).toDouble());
        qDebug() << ein.mid(4, ein.length()-1).toDouble();
    }
    else if (ein.startsWith("LON:"))
    {
        //geographische Länge
        data->setFlugdaten(1, ein.mid(4, ein.length()-1).toDouble());
        qDebug() << ein.mid(4, ein.length()-1).toDouble();
    }
    else if (ein.startsWith("PIT:"))
    {
        //Winkel im die Querachse
        data->setFlugdaten(2, ein.mid(4, ein.length()-1).toDouble());
        qDebug() << ein.mid(4, ein.length()-1).toDouble();
    }
    else if (ein.startsWith("BNK:"))
    {
        //Winkel um die Längsachse
        data->setFlugdaten(3, ein.mid(4, ein.length()-1).toDouble());
        qDebug() << ein.mid(4, ein.length()-1).toDouble();
    }
    else if (ein.startsWith("THG:"))
    {
        //Winkel um die Hochachse bezogen auf geographisch Nord
        data->setFlugdaten(4, ein.mid(4, ein.length()-1).toDouble());
        qDebug() << ein.mid(4, ein.length()-1).toDouble();
    }
    else if (ein.startsWith("TCS:"))
    {
        //Flugrichtung bezogen auf geographisch Nord
        data->setFlugdaten(5, ein.mid(4, ein.length()-1).toDouble());
        qDebug() << ein.mid(4, ein.length()-1).toDouble();
    }
    else if (ein.startsWith("ALT:"))
    {
        //Höhe
        data->setFlugdaten(6, ein.mid(4, ein.length()-1).toDouble());
        qDebug() << ein.mid(4, ein.length()-1).toDouble();
    }
    else if (ein.startsWith("TAS:"))
    {
        //Geschwindigkeit gegenüber Luft
        data->setFlugdaten(7, ein.mid(4, ein.length()-1).toDouble());
        qDebug() << ein.mid(4, ein.length()-1).toDouble();
    }
    else if (ein.startsWith("GSP:"))
    {
        //Geschwindigkeit über Grund
        data->setFlugdaten(8, ein.mid(4, ein.length()-1).toDouble());
        qDebug() << ein.mid(4, ein.length()-1).toDouble();
    }
    else if (ein.startsWith("WVE:"))
    {
        //Windrichtung bezogen auf geographisch Nord
        data->setFlugdaten(9, ein.mid(4, ein.length()-1).toDouble());
        qDebug() << ein.mid(4, ein.length()-1).toDouble();
    }
    else if (ein.startsWith("WSP:"))
    {
        //Windgeschwindigkeit
        data->setFlugdaten(10, ein.mid(4, ein.length()-1).toDouble());
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
