#include "updatethread.h"

UpdateThread::UpdateThread(Daten *data, QGraphicsScene *sceneEADI, QGraphicsScene *sceneCourse,int heightEADI, int widthEADI, int heightCourse, int widthCourse, QObject *parent) :
    QThread(parent)
{
    this->data = data;
    this->sceneEADI = sceneEADI;
    this->sceneCourse = sceneCourse;
    this->heightEADI = heightEADI;
    this->widthEADI = widthEADI;
    this->heightCourse = heightCourse;
    this->widthCourse = widthCourse;
    this->flightdata = new double[data->getAnzahl()];
    this->stop = false;

    QObject::connect(this,SIGNAL(dataChanged()),this,SLOT(update()));
}

void UpdateThread::run()
{
    while(!stop)
    {
        getFlightData();
        msleep(500);
    }
}

void UpdateThread::getFlightData()
{
    QMutexLocker locker(mutex);
    for (int i = 0; i < data->getAnzahl(); i++)
    {
        flightdata[i] = data->getFlugdaten(i);
    }
    emit dataChanged();
}

void UpdateThread::update()
{
    drawEADI();
    drawCourse();
    emit setPos("test1");
    emit setGeschwindigkeit("test2");
}


void UpdateThread::drawEADI()
{
    sceneEADI->clear();
    int l = 10;
    int r = 10;

    QGraphicsPolygonItem *polygonItem = new QGraphicsPolygonItem(
                QPolygonF( QVector<QPointF>() << QPointF( 0, 0 )
                           << QPointF( 0, l ) << QPointF( widthEADI-10, r )
                           << QPointF( widthEADI-10, 0 ) ), 0, sceneEADI );
    polygonItem->setBrush( Qt::blue );

    QGraphicsPolygonItem *polygonItem2 = new QGraphicsPolygonItem(
                QPolygonF( QVector<QPointF>() << QPointF( 0, l )
                           << QPointF( 0, heightEADI-10 ) << QPointF( widthEADI-10, heightEADI-10 )
                           << QPointF( widthEADI-10, r ) ), 0, sceneEADI );
    polygonItem2->setBrush( Qt::green );


    QGraphicsLineItem *lineItem = new QGraphicsLineItem(0, l, widthEADI-10, r, 0, sceneEADI );
    lineItem->setPen(QPen(Qt::white));
}

void UpdateThread::drawCourse()
{
    sceneCourse->clear();
    int l = 10;
    int r = 10;

    QGraphicsPolygonItem *polygonItem = new QGraphicsPolygonItem(
                QPolygonF( QVector<QPointF>() << QPointF( 0, 0 )
                           << QPointF( 0, l ) << QPointF( widthCourse-10, r )
                           << QPointF( widthCourse-10, 0 ) ), 0, sceneCourse );
    polygonItem->setBrush( Qt::blue );

    QGraphicsPolygonItem *polygonItem2 = new QGraphicsPolygonItem(
                QPolygonF( QVector<QPointF>() << QPointF( 0, l )
                           << QPointF( 0, heightCourse-10 ) << QPointF( widthCourse-10, heightCourse-10 )
                           << QPointF( widthCourse-10, r ) ), 0, sceneCourse );
    polygonItem2->setBrush( Qt::green );


    QGraphicsLineItem *lineItem = new QGraphicsLineItem(0, l, widthCourse-10, r, 0, sceneCourse );
    lineItem->setPen(QPen(Qt::white));
}

void UpdateThread::stopSimulation()
{
    stop = true;
}



