#include "updatethread.h"

UpdateThread::UpdateThread(Daten *data, QGraphicsScene *sceneEADI, QGraphicsScene *sceneCourse, QGraphicsScene *sceneWind,QObject *parent) :
    QThread(parent)
{
    this->data = data;
    this->sceneEADI = sceneEADI;
    this->sceneCourse = sceneCourse;
    this->sceneWind = sceneWind;
    this->stop = false;
    mutex = new QMutex();
}

void UpdateThread::run()
{
    while(!stop)
    {
        QMutexLocker locker(mutex);
        //getFlightData();
        drawEADI();
        drawCourse();
        drawWind();
        emit setPos(QString::number(data->getFlugdaten(0)) + " Grad " + QString::number(data->getFlugdaten(0)) + "Grad" );
        emit setAirspeed(QString::number(data->getFlugdaten(7)) + " kn");
        emit setGroundspeed(QString::number(data->getFlugdaten(8)) + " kn");
        emit setHeight(QString::number(data->getFlugdaten(6)) + " kn");
        msleep(50);
    }
}

void UpdateThread::drawEADI()
{

    sceneEADI->clear();
    sceneEADI->setSceneRect(0, -180,100 ,360);

    QBrush background(Qt::blue);
    sceneEADI->setBackgroundBrush(background);

    QGraphicsPolygonItem *polygonItem = new QGraphicsPolygonItem(
                QPolygonF( QVector<QPointF>() << QPointF( -360, -(data->getFlugdaten(2)) )
                           << QPointF( -360, 360 ) << QPointF( 360, 360 )
                           << QPointF( 360, -(data->getFlugdaten(2)) ) ), 0, sceneEADI );
    polygonItem->setBrush( Qt::green );
    polygonItem->rotate(data->getFlugdaten(3));
}

void UpdateThread::drawCourse()
{
    sceneCourse->setSceneRect(-25,-25,50 ,50);

    sceneCourse->clear();
    QGraphicsPolygonItem *polygonItem = new QGraphicsPolygonItem(
                QPolygonF( QVector<QPointF>() << QPointF( -10, -20)
                           << QPointF( -5, -20 ) << QPointF( -5, +30 )
                           << QPointF( +5, +30 ) << QPointF( +5, -20 )
                           << QPointF( +10, -20 ) << QPointF( 0, -30) ), 0, sceneCourse );
    polygonItem->setBrush( Qt::blue );
    polygonItem->rotate(data->getFlugdaten(4));

    QGraphicsPolygonItem *polygonItem1 = new QGraphicsPolygonItem(
                QPolygonF( QVector<QPointF>() << QPointF( -10, -20)
                           << QPointF( -5, -20 ) << QPointF( -5, +30 )
                           << QPointF( +5, +30 ) << QPointF( +5, -20 )
                           << QPointF( +10, -20 ) << QPointF( 0, -30) ), 0, sceneCourse );
    polygonItem1->setBrush( Qt::red );
    polygonItem1->rotate(data->getFlugdaten(5));
}

void UpdateThread::drawWind()
{
    sceneWind->setSceneRect(-25,-25,50 ,50);

    sceneWind->clear();
    QGraphicsPolygonItem *polygonItem = new QGraphicsPolygonItem(
                QPolygonF( QVector<QPointF>() << QPointF( -10, -20)
                           << QPointF( -5, -20 ) << QPointF( -5, +30 )
                           << QPointF( +5, +30 ) << QPointF( +5, -20 )
                           << QPointF( +10, -20 ) << QPointF( 0, -30) ), 0, sceneWind );
    polygonItem->setBrush( Qt::blue );
    polygonItem->rotate(data->getFlugdaten(9));
    QString text = QString::number(data->getFlugdaten(10));
    text = text + " kn";
    QGraphicsTextItem *textItem = new QGraphicsTextItem(text, 0, sceneWind);
    textItem->setPos(-20,30);
}

void UpdateThread::stopSimulation()
{
    stop = true;
}

UpdateThread::~UpdateThread()
{
    delete sceneEADI;
    delete sceneCourse;
    delete sceneWind;
    delete data;
}



