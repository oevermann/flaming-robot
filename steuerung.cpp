#include "steuerung.h"
#include "ui_steuerung.h"
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


    for (int i = 0; i < 9; i++)
    {
        key[i] = false;
    }

    ui->setupUi(this);

    ui->graphicsView->setScene(&scene);
    ui->graphicsView->setSceneRect(0, -180,100 ,360);
    ui->graphicsView->show();

    ui->komp_graphicsView->setScene(&scenekomp);
    ui->komp_graphicsView->show();

    ui->wind_graphicsView->setScene(&scenewind);
    ui->wind_graphicsView->show();

    simulation = new UpdateThread(data, &scene, &scenekomp, &scenewind);

    QObject::connect(simulation,SIGNAL(setPos(QString)),this,SLOT(setPos(QString)));
    QObject::connect(simulation,SIGNAL(setAirspeed(QString)),this,SLOT(setAirspeed(QString)));
    QObject::connect(simulation,SIGNAL(setGroundspeed(QString)),this,SLOT(setGroundspeed(QString)));
    QObject::connect(simulation,SIGNAL(setHeight(QString)),this,SLOT(setHeight(QString)));
}

Steuerung::~Steuerung()
{
    delete ui;
    delete data;
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

void Steuerung::on_start_clicked()
{
    client->connectSocket(clientAddress, port, "HLO:");
    simulation->start();
//    scene.moveToThread(simulation);
//    scenekomp.moveToThread(simulation);
//    scenewind.moveToThread(simulation);
}

void Steuerung::on_stop_clicked()
{
    client->disconnect();
    simulation->quit();
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

void Steuerung::setPos(QString pos)
{
    ui->position_text->setText(pos);
}

void Steuerung::setAirspeed(QString airspeed)
{
    ui->airspeed_text->setText(airspeed);
}

void Steuerung::setGroundspeed(QString groundspeed)
{
    ui->groundspeed_text->setText(groundspeed);
}

void Steuerung::setHeight(QString height)
{
    ui->height_text->setText(height);
}


/*
  --------------------------------------------------------------------------------------------------
  Tastaturabfrage und Daten aendern
  --------------------------------------------------------------------------------------------------
*/

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
       data->setAccelerate(5);

   }

   if (key[7])
   {
       data->setAccelerate(-5);
   }

   if (key[8])
   {
       data->reset();
   }
}
