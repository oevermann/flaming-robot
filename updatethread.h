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
    explicit UpdateThread(Daten *data, QGraphicsScene *sceneEADI, QGraphicsScene *sceneCourse,int heightEADI, int widthEADI, int heightCourse, int widthCourse, QObject *parent = 0);
    void getFlightData();
    void drawEADI();
    void drawCourse();
    void run();
    
signals:
    void setPos(QString pos);
    void setGeschwindigkeit(QString speed);
    void dataChanged();
    
public slots:
    void stopSimulation();

private slots:
    void update();

private:
    double *flightdata;
    QMutex *mutex;
    QGraphicsScene *sceneEADI;
    QGraphicsScene *sceneCourse;
    Daten *data;
    int heightEADI;
    int widthEADI;
    int heightCourse;
    int widthCourse;
    bool stop;
    
};

#endif // UPDATETHREAD_H
