#include "daten.h"
#include <QDebug>

//legt die Anfangswerte fest
Daten::Daten(QObject *parent) :
    QObject(parent)
{
    this->roll = 100;
    this->nick = 100;
    this->yaw = 100;
    this->accelerate = 100;
    anzahl = 11;
    flugdaten = new double[anzahl];
    rollmutex = new QMutex();
    yawmutex = new QMutex();
    nickmutex = new QMutex();
    acceleratemutex = new QMutex();
    flightdatamutex = new QMutex();
    for (int i = 0; i < anzahl; i++)
    {
        flugdaten[i] = 0;
    }
}

//legt die Anfangswerte fest
Daten::Daten(int roll, int nick, int yaw, int accelerate,QObject *parent)
{
    this->roll = roll;
    this->nick = nick;
    this->yaw = yaw;
    this->accelerate = accelerate;
    anzahl = 11;
    flugdaten = new double[anzahl];
    rollmutex = new QMutex();
    yawmutex = new QMutex();
    nickmutex = new QMutex();
    acceleratemutex = new QMutex();
    flightdatamutex = new QMutex();
    for (int i = 0; i < anzahl; i++)
    {
        flugdaten[i] = 0;
    }
}

//setzt den Roll-Winkel
void Daten::setRoll(int value)
{
    QMutexLocker locker(rollmutex);
    if ((roll + value < 200) && (roll + value > 0))
        roll += value;
    emit Daten::dataChanged();
}

//setzt den Nick-Winkel
void Daten::setNick(int value)
{
    QMutexLocker locker(nickmutex);
    if ((nick + value < 200) && (nick + value > 0))
        nick += value;
    emit Daten::dataChanged();
}

//setzt den Gier-Winkel bzw. Yaw-Winkel
void Daten::setYaw(int value)
{
    QMutexLocker locker(yawmutex);
    if ((yaw + value < 200) && (yaw + value > 0))
        yaw += value;
    emit Daten::dataChanged();
}

//setzt die Beschleunigung
void Daten::setAccelerate(int value)
{
    QMutexLocker locker(acceleratemutex);
    if ((accelerate + value < 200) && (accelerate + value > 0))
        accelerate += value;
    emit Daten::dataChanged();
}

//setzdie Flugdaten an i-ter Position ins Array ein
void Daten::setFlugdaten(int i, double value)
{
    QMutexLocker locker(flightdatamutex);
    flugdaten[i] = value;
    emit Daten::dataChanged();
}

//gibt den Roll-Winkel zurück
int Daten::getRoll()
{
    QMutexLocker locker(rollmutex);
    return roll;
}

//gibt den Nick-Winkel zurück
int Daten::getNick()
{
    QMutexLocker locker(nickmutex);
    return nick;
}

//gibt den Gier-Winkel Yaw-Winkel zurück
int Daten::getYaw()
{
    QMutexLocker locker(yawmutex);
    return yaw;
}

//gibt den Wert der Beschleunigung zurück
int Daten::getAccelerate()
{
    QMutexLocker locker(acceleratemutex);
    return accelerate;
}

//gibt die Flugdaten an i-ter Position zurück
double Daten::getFlugdaten(int i)
{
    QMutexLocker locker(flightdatamutex);
    return flugdaten[i];
}

//gibt die Größe des Array zurück
int Daten::getAnzahl()
{
    QMutexLocker locker(flightdatamutex);
    return anzahl;
}

//Werte in Ausgangsposition bringen
void Daten::reset()
{
    QMutexLocker locker1(rollmutex);
    QMutexLocker locker2(nickmutex);
    QMutexLocker locker3(yawmutex);
    QMutexLocker locker4(acceleratemutex);
    roll = 100;
    nick = 100;
    yaw = 100;
}
