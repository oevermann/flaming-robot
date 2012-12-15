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
    void setPos(QString pos);
    void setAirspeed(QString airspeed);
    void setGroundspeed(QString groundspeed);
    void setHeight(QString height);
    
public slots:
    void stopSimulation();

private slots:

private:
    QGraphicsScene *sceneEADI;
    QGraphicsScene *sceneCourse;
    QGraphicsScene *sceneWind;
    Daten *data;
    bool stop;
    
};

#endif // UPDATETHREAD_H
