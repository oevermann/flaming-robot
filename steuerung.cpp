#include "steuerung.h"
#include "ui_steuerung.h"
#include "dialog.h"
#include <QDebug>

Steuerung::Steuerung(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Steuerung)
{

    ui->setupUi(this);
    left = (ui->graphicsView->height()/3)*2;
    right = (ui->graphicsView->height()/3)*2;
    rotate = 0;

    drawScene(scene, ui->graphicsView->height(), ui->graphicsView->width(),left ,right);
    ui->graphicsView->setScene(&scene);
    ui->graphicsView->show();

}

Steuerung::~Steuerung()
{
    delete ui;
}

void Steuerung::on_actionVerbindung_triggered()
{
    Dialog verbindung;
    verbindung.setModal(true);
    verbindung.exec();
}

void Steuerung::on_actionSchlie_en_triggered()
{
    close();
}

void Steuerung::on_actionInfo_triggered()
{

}

void Steuerung::keyPressEvent(QKeyEvent *event)
{
   scene.clear();

   if (event->key() ==  Qt::Key_W)
   {
       //hoch
       if((left+5) < ui->graphicsView->height()-5)
       {
           left += 5;
           right += 5;
       }
   }

   if (event->key() ==  Qt::Key_S)
   {
       //runter
       if((left+5) > 30)
       {
           left -= 5;
           right -= 5;
       }
   }

   if (event->key() ==  Qt::Key_A)
   {
       //links
       if((right+5) < ui->graphicsView->height()-10)
       {
           left -= 5;
           right += 5;
       }
   }

   if (event->key() ==  Qt::Key_D)
   {
       //rechts
       if((left+5) < ui->graphicsView->height()-10)
       {
            left += 5;
            right -= 5;
       }
   }

   if (event->key() ==  Qt::Key_H)
   {
       qDebug() << "schneller";
   }

   if (event->key() ==  Qt::Key_L)
   {
       qDebug() << "langsamer";
   }

   drawScene(scene, ui->graphicsView->height(), ui->graphicsView->width(),left ,right);
   ui->graphicsView->setScene(&scene);
   ui->graphicsView->update();
}



void Steuerung::on_pushButton_7_clicked()
{

}

void Steuerung::drawScene(QGraphicsScene &scene, int height, int width, int l, int r)
{
    QGraphicsPolygonItem *polygonItem = new QGraphicsPolygonItem(
                QPolygonF( QVector<QPointF>() << QPointF( 0, 0 )
                           << QPointF( 0, l ) << QPointF( width-10, r )
                           << QPointF( width-10, 0 ) ), 0, &scene );
    polygonItem->setBrush( Qt::blue );

    QGraphicsPolygonItem *polygonItem2 = new QGraphicsPolygonItem(
                QPolygonF( QVector<QPointF>() << QPointF( 0, l )
                           << QPointF( 0, height-10 ) << QPointF( width-10, height-10 )
                           << QPointF( width-10, r ) ), 0, &scene );
    polygonItem2->setBrush( Qt::green );


    QGraphicsLineItem *lineItem = new QGraphicsLineItem(0, l, ui->graphicsView->width()-10, r, 0, &scene );
    lineItem->setPen(QPen(Qt::white));

//        QGraphicsLineItem *lineItem1 = new QGraphicsLineItem(10, 10, ui->graphicsView->width()-25, 10, 0, &scene );
//        lineItem1->setPen(QPen(Qt::white));

//        QGraphicsLineItem *lineItem2 = new QGraphicsLineItem(30, 50, ui->graphicsView->width()-55, 50, 0, &scene );
//        lineItem2->setPen(QPen(Qt::white));

//        QGraphicsLineItem *lineItem3 = new QGraphicsLineItem(10, 90, ui->graphicsView->width()-25, 90, 0, &scene );
//        lineItem3->setPen(QPen(Qt::white));

//        QGraphicsLineItem *lineItem4 = new QGraphicsLineItem(30, 130, ui->graphicsView->width()-55, 130, 0, &scene );
//        lineItem4->setPen(QPen(Qt::white));

//        QGraphicsLineItem *lineItem5 = new QGraphicsLineItem(10, 170, ui->graphicsView->width()-25, 170, 0, &scene );
//        lineItem5->setPen(QPen(Qt::white));

//        QGraphicsLineItem *lineItem6 = new QGraphicsLineItem(30, 210, ui->graphicsView->width()-55, 210, 0, &scene );
//        lineItem6->setPen(QPen(Qt::white));

//        QGraphicsLineItem *lineItem7 = new QGraphicsLineItem(10, 250, ui->graphicsView->width()-25, 250, 0, &scene );
//        lineItem7->setPen(QPen(Qt::white));

//        QGraphicsLineItem *lineItem8 = new QGraphicsLineItem(30, 290, ui->graphicsView->width()-55, 290, 0, &scene );
//        lineItem8->setPen(QPen(Qt::white));

//        QGraphicsLineItem *lineItem9 = new QGraphicsLineItem(10, 330, ui->graphicsView->width()-25, 330, 0, &scene );
//        lineItem9->setPen(QPen(Qt::white));

}

