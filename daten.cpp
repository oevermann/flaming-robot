#include "daten.h"
#include <QDebug>

Daten::Daten(QObject *parent) :
    QObject(parent)
{
    //Daten(100, 100, 100, 100);
    this->roll = 100;
    this->nick = 100;
    this->yaw = 100;
    this->accelerate = 100;
    anzahl = 11;
    flugdaten = new double[anzahl];

    for (int i = 0; i < anzahl; i++)
    {
        flugdaten[i] = 0;
    }
}

Daten::Daten(int roll, int nick, int yaw, int accelerate,QObject *parent)
{
    this->roll = roll;
    this->nick = nick;
    this->yaw = yaw;
    this->accelerate = accelerate;
    anzahl = 11;
    flugdaten = new double[anzahl];

    for (int i = 0; i < anzahl; i++)
    {
        flugdaten[i] = 0;
    }
}

void Daten::setRoll(int value)
{
    if ((roll + value < 200) && (roll + value > 0))
        roll += value;
    qDebug() << roll;
    emit Daten::dataChanged();
}

void Daten::setNick(int value)
{
    if ((nick + value < 200) && (nick + value > 0))
        nick += value;
    qDebug() << nick;
    emit Daten::dataChanged();
}

void Daten::setYaw(int value)
{
    if ((yaw + value < 200) && (yaw + value > 0))
        yaw += value;
    qDebug() << yaw;
    emit Daten::dataChanged();
}

void Daten::setAccelerate(int value)
{
    if ((accelerate + value < 200) && (accelerate + value > 0))
        accelerate += value;
    qDebug() << accelerate;
    emit Daten::dataChanged();
}

void Daten::setFlugdaten(int i, double value)
{
    flugdaten[i] = value;
    emit Daten::dataChanged();
}

int Daten::getRoll()
{
    return roll;
}

int Daten::getNick()
{
    return nick;
}

int Daten::getYaw()
{
    return yaw;
}

int Daten::getAccelerate()
{
    return accelerate;
}

double Daten::getFlugdaten(int i)
{
    return flugdaten[i];
}

int Daten::getAnzahl()
{
    return anzahl;
}

void Daten::reset()
{
    roll = 100;
    nick = 100;
    yaw =100;
}
