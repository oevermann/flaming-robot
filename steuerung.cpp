#include "steuerung.h"
#include "ui_steuerung.h""
#include <QDebug>

Steuerung::Steuerung(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Steuerung)
{
    key = new bool[9];
    data = new Daten();//(100, 100, 100, 100);

    server = new Server(data);
    server->startServer();

    client = new Client(data);
    QObject::connect(client,SIGNAL(connectionError(QString)),this,SLOT(connectionError(QString)));

    int height = ui->graphicsView->height();
    int widht = ui->graphicsView->width();

//    simulation = new UpdateThread(data,scene,scene,height,width,height,width);

//    QObject::connect(simulation,SIGNAL(setGeschwindigkeit(QString)),this,SLOT(setGeschwindigkeit(QString)));
//    QObject::connect(simulation,SIGNAL(setPos(QString)),this,SLOT(setPos(QString)));



    for (int i = 0; i < 9; i++)
    {
        key[i] = false;
    }

    ui->setupUi(this);
    left = (ui->graphicsView->height()/3)*2;
    right = (ui->graphicsView->height()/3)*2;
    rotate = 0;
    //connect(server,SIGNAL(newConnection()),this,SLOT(keyPressEvent(QKeyEvent*)));

    drawScene(ui->graphicsView->height(), ui->graphicsView->width(),left ,right);
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
    QObject::connect(&verbindung,SIGNAL(setServer(QString,int)),this,SLOT(setClient(QString,int)));
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
    switch (event->key())
    {
        case Qt::Key_8:
            key[0] = true;
            break;

        case Qt::Key_2:
            key[1] = true;
            break;

        case Qt::Key_4:
            key[2] = true;
            break;

        case Qt::Key_6:
            key[3] = true;
            break;

        case Qt::Key_7:
            key[4] = true;
            break;

        case Qt::Key_1:
            key[5] = true;
            break;

        case Qt::Key_Plus:
            key[6] = true;
            break;

        case Qt::Key_Minus:
            key[7] = true;
        break;

        case Qt::Key_5:
            key[8] = true;
            break;
    }

    fly();
}

void Steuerung::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_8:
            key[0] = false;
            break;

        case Qt::Key_2:
            key[1] = false;
            break;

        case Qt::Key_4:
            key[2] = false;
            break;

        case Qt::Key_6:
            key[3] = false;
            break;

        case Qt::Key_7:
            key[4] = false;
            break;

        case Qt::Key_1:
            key[5] = false;
            break;

        case Qt::Key_Plus:
            key[6] = false;
            break;

        case Qt::Key_Minus:
            key[7] = false;
        break;

        case Qt::Key_5:
            key[8] = false;
            break;
    }


    fly();
}

void Steuerung::fly()
{
   scene.clear();

   if (key[0])
   {
       //hoch
       if((left+5) < ui->graphicsView->height()-5 && (right+5) < ui->graphicsView->height()-5)
       {
           left += 5;
           right += 5;
       }
       data->setNick(5);
   }

   if (key[1])
   {
       //runter
       if((left-5) > 30 && (left-5) > 30)
       {
           left -= 5;
           right -= 5;
       }
       data->setNick(-5);
   }

   if (key[2])
   {
       //links
       if((left+5) < ui->graphicsView->height()-10)
       {
            left += 5;
            right -= 5;
       }
       data->setRoll(5);
   }

   if (key[3])
   {
       //rechts
       if((right+5) < ui->graphicsView->height()-10)
       {
           left -= 5;
           right += 5;
       }
       data->setRoll(-5);
   }

   if (key[4])
   {

       data->setYaw(5);
   }

   if (key[5])
   {

       data->setYaw(-5);
   }

   if (key[6])
   {
       qDebug() << "schneller";
       data->setAccelerate(5);

   }

   if (key[7])
   {
       qDebug() << "langsamer";
       data->setAccelerate(-5);
   }

   if (key[8])
   {
       data->reset();
   }

   drawScene(ui->graphicsView->height(), ui->graphicsView->width(),left ,right);
   ui->graphicsView->setScene(&scene);
   ui->graphicsView->update();
}

void Steuerung::drawScene(int height, int width, int l, int r)
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


void Steuerung::on_start_clicked()
{
    client->connectSocket(clientAddress, port, "HLO:");
}

void Steuerung::setClient(QString address, int port)
{
    this->clientAddress = address;
    this->port = port;
}

void Steuerung::connectionError(QString error)
{
    QMessageBox *msgBox = new QMessageBox(QMessageBox::Critical,"Error", error,QMessageBox::Ok);
    msgBox->exec();
}
