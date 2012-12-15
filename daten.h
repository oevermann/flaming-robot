#ifndef DATEN_H
#define DATEN_H

#include <QObject>
#include <QMutex>
#include <QMutexLocker>

class Daten : public QObject
{
    Q_OBJECT
    QMutex *mutex;
    int roll;
    int nick;
    int yaw;
    int accelerate;
    double *flugdaten;
    int anzahl;

public:
    explicit Daten(QObject *parent = 0);
    explicit Daten(int roll, int nick, int yaw, int accelerate, QObject *parent = 0);

    void setRoll(int value);
    void setNick(int value);
    void setYaw(int value);
    void setAccelerate(int value);
    void setFlugdaten(int i, double value);
    void reset();

    int getRoll();
    int getNick();
    int getYaw();
    int getAccelerate();
    double getFlugdaten(int i);
    int getAnzahl();

    
signals:
    void dataChanged();
public slots:

    
};

#endif // DATEN_H
