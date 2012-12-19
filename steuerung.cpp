#include "steuerung.h"
#include "ui_steuerung.h"
#include <QDebug>

/**
    Die Klasse erstellt den Hauptframe und intialisiert alle benötigten Variablen
*/

Steuerung::Steuerung(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Steuerung)
{
    key = new bool[9];
    data = new Daten();

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
    ui->graphicsView->show();

    ui->komp_graphicsView->setScene(&scenekomp);
    ui->komp_graphicsView->show();

    ui->wind_graphicsView->setScene(&scenewind);
    ui->wind_graphicsView->show();

    simulation = new UpdateThread(data, &scene, &scenekomp, &scenewind);

    QObject::connect(simulation,SIGNAL(setPos(const QString &)),this,SLOT(setPos(const QString &)));
    QObject::connect(simulation,SIGNAL(setAirspeed(const QString &)),this,SLOT(setAirspeed(const QString &)));
    QObject::connect(simulation,SIGNAL(setGroundspeed(const QString &)),this,SLOT(setGroundspeed(const QString &)));
    QObject::connect(simulation,SIGNAL(setHeight(const QString &)),this,SLOT(setHeight(const QString &)));
}


Steuerung::~Steuerung()
{
    delete ui;
    //delete[] data;
    delete data;
}

//öffnet den Dialog für den Verbindungsaufbau
void Steuerung::on_actionVerbindung_triggered()
{
    Dialog verbindung;
    verbindung.setModal(true);
    QObject::connect(&verbindung,SIGNAL(setServer(QString,int)),this,SLOT(setClient(QString,int)));
    verbindung.exec();
}

//beendet das Programm
void Steuerung::on_actionSchlie_en_triggered()
{
    close();
}

void Steuerung::on_actionInfo_triggered()
{

}

//beendet die Simulation
void Steuerung::on_start_clicked()
{
    client->connectSocket(clientAddress, port);
    simulation->start();
}

void Steuerung::on_stop_clicked()
{
    client-disconnect();
    simulation->quit();
}

//ist ein slot der von dem Signal setServer der Klasse Dialog aufgerufen wird
//und legt die Verbindungsdaten zum Simulator fest
void Steuerung::setClient(QString address, int port)
{
    this->clientAddress = address;
    this->port = port;
}


//ist ein slot der von dem Signal connectionError der Klasse client aufgerufen wird
//und öffnet eine MessageBox bei fehlerhaftem Verbindungsaufbau
void Steuerung::connectionError(QString error)
{
    QMessageBox *msgBox = new QMessageBox(QMessageBox::Critical,"Error", error,QMessageBox::Ok);
    msgBox->exec();
}

//ändert den Text im Positions textfeld
void Steuerung::setPos(const QString &pos)
{
    ui->position_text->setText(pos);
}

//ändert den Text im Geschwindigkeit über Luft textfeld
void Steuerung::setAirspeed(const QString &airspeed)
{
    ui->airspeed_text->setText(airspeed);
}

//ändert den Text im Geschwindigkeit über Grund textfeld
void Steuerung::setGroundspeed(const QString &groundspeed)
{
    ui->groundspeed_text->setText(groundspeed);
}

//ändert den Text im Höhen textfeld
void Steuerung::setHeight(const QString &height)
{
    ui->height_text->setText(height);
}

/*
  --------------------------------------------------------------------------------------------------
  Tastaturabfrage und RuderDaten aendern
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

    setControlData();
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

    setControlData();
}

void Steuerung::setControlData()
{
   if (key[0])
   {
       //hoch
       data->setNick(1);
   }

   if (key[1])
   {
       //runter
       data->setNick(-1);
   }

   if (key[2])
   {
       //links
       data->setRoll(1);
   }

   if (key[3])
   {
       //rechts
       data->setRoll(-1);
   }

   if (key[4])
   {
       data->setYaw(1);
   }

   if (key[5])
   {
       data->setYaw(-1);
   }

   if (key[6])
   {
       data->setAccelerate(1);
   }

   if (key[7])
   {
       data->setAccelerate(-1);
   }

   if (key[8])
   {
       data->reset();
   }
}
