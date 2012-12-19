#include "updatethread.h"

UpdateThread::UpdateThread(Daten *data, QGraphicsScene *sceneEADI, QGraphicsScene *sceneCourse, QGraphicsScene *sceneWind,QObject *parent) :
    QThread(parent)
{
    this->data = data;
    this->sceneEADI = sceneEADI;
    this->sceneCourse = sceneCourse;
    this->sceneWind = sceneWind;
    this->sceneEADI->setSceneRect(-180, -180,360 ,360);
    this->sceneCourse->setSceneRect(-25,-25,50 ,50);
    this->sceneWind->setSceneRect(-25,-25,50 ,50);
    this->stop = false;
    this->oldpit = 0;
    this->oldbnk = 0;
    this->oldthg = 0;
    this->oldtcs = 0;
    this->oldwve = 0;
    this->oldwsp = 0;
}

//startet den Thread und ruft die Funktionen drawEadi,drawCourse und drawWind aus
//danach wird der Thread 100 Millisekunden schlafen gelegt
void UpdateThread::run()
{
    while(!stop)
    {
        try
        {
            oldpit = data->getFlugdaten(2);
            oldbnk = data->getFlugdaten(3);
            oldthg = data->getFlugdaten(4);
            oldtcs = data->getFlugdaten(5);
            oldwve = data->getFlugdaten(9);
            oldwsp = data->getFlugdaten(10);
        }
        catch(...)
        {

        }
        drawEADI();
        drawCourse();
        drawWind();

        QString lat;
        QString lon;
        if (data->getFlugdaten(0) >= 0)
            lat = " E ";
        else
            lat = " W ";

        if (data->getFlugdaten(1) >= 0)
            lon = " N ";
        else
            lon = " S ";

        emit setPos(QString::number(data->getFlugdaten(0)) + lat + QString::number(data->getFlugdaten(1)) + lon );
        emit setAirspeed(QString::number(data->getFlugdaten(7)) + " Kn");
        emit setGroundspeed(QString::number(data->getFlugdaten(8)) + " Kn");
        emit setHeight(QString::number(data->getFlugdaten(6)) + " Kn");

        msleep(100);
    }
}

//zeichnet die Scene für den künstlichen Horizont
void UpdateThread::drawEADI()
{
    sceneEADI->clear();

    QBrush background(Qt::blue);
    sceneEADI->setBackgroundBrush(background);

    QGraphicsPolygonItem *polygonItem = new QGraphicsPolygonItem(
                QPolygonF( QVector<QPointF>() << QPointF( -360, -oldpit )
                           << QPointF( -360, 360 ) << QPointF( 360, 360 )
                           << QPointF( 360, -oldpit ) ), 0, sceneEADI );
    polygonItem->setBrush( Qt::green );
    polygonItem->rotate(oldbnk);
}

//zeichnet die Scene für den Kurs
void UpdateThread::drawCourse()
{


    sceneCourse->clear();
    QGraphicsPolygonItem *polygonItem = new QGraphicsPolygonItem(
                QPolygonF( QVector<QPointF>() << QPointF( -10, -20)
                           << QPointF( -5, -20 ) << QPointF( -5, +30 )
                           << QPointF( +5, +30 ) << QPointF( +5, -20 )
                           << QPointF( +10, -20 ) << QPointF( 0, -30) ), 0, sceneCourse );
    polygonItem->setBrush( Qt::blue );
    polygonItem->rotate(oldthg);

    QGraphicsPolygonItem *polygonItem1 = new QGraphicsPolygonItem(
                QPolygonF( QVector<QPointF>() << QPointF( -10, -20)
                           << QPointF( -5, -20 ) << QPointF( -5, +30 )
                           << QPointF( +5, +30 ) << QPointF( +5, -20 )
                           << QPointF( +10, -20 ) << QPointF( 0, -30) ), 0, sceneCourse );
    polygonItem1->setBrush( Qt::red );
    polygonItem1->rotate(oldtcs);
}

//zeichnet die Scene für die Windanzeige
void UpdateThread::drawWind()
{
    sceneWind->clear();
    QGraphicsPolygonItem *polygonItem = new QGraphicsPolygonItem(
                QPolygonF( QVector<QPointF>() << QPointF( -10, -20)
                           << QPointF( -5, -20 ) << QPointF( -5, +30 )
                           << QPointF( +5, +30 ) << QPointF( +5, -20 )
                           << QPointF( +10, -20 ) << QPointF( 0, -30) ), 0, sceneWind );
    polygonItem->setBrush( Qt::blue );
    polygonItem->rotate(oldwve+180);

    QString text = QString::number(oldwsp);
    text = text + " kn";
    QGraphicsTextItem *textItem = new QGraphicsTextItem(text, 0, sceneWind);
    textItem->setPos(-20,30);
}

//stopt die Simulation
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



