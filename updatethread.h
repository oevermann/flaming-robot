#ifndef UPDATETHREAD_H
#define UPDATETHREAD_H

#include <QThread>
#include "daten.h"
#include <QMutex>
#include <QMutexLocker>
#include <QtGui>

class UpdateThread : public QThread
{
    Q_OBJECT
public:
    explicit UpdateThread(Daten *data,QGraphicsScene *sceneEADI, QGraphicsScene *sceneCourse, QGraphicsScene *sceneWind, QObject *parent = 0);
    ~UpdateThread();
    void drawEADI();
    void drawCourse();
    void drawWind();
    void run();
    
signals:
    void setPos(const QString &pos);
    void setAirspeed(const QString &airspeed);
    void setGroundspeed(const QString &groundspeed);
    void setHeight(const QString &height);
    
public slots:
    void stopSimulation();

private slots:

private:
    QGraphicsScene *sceneEADI;
    QGraphicsScene *sceneCourse;
    QGraphicsScene *sceneWind;
    Daten *data;
    bool stop;
    double oldpit;
    double oldbnk;
    double oldthg;
    double oldtcs;
    double oldwve;
    double oldwsp;
};

#endif // UPDATETHREAD_H
