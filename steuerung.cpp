#include "steuerung.h"
#include "ui_steuerung.h"
#include "dialog.h"
#include <QDebug>

Steuerung::Steuerung(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Steuerung)
{
    ui->setupUi(this);
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
   if (event->key() ==  Qt::Key_W)
   {
       qDebug() << "rauf";
   }

   if (event->key() ==  Qt::Key_S)
   {
       qDebug() << "runter";
   }

   if (event->key() ==  Qt::Key_A)
   {
       qDebug() << "links";
   }

   if (event->key() ==  Qt::Key_D)
   {
       qDebug() << "rechts";
   }

   if (event->key() ==  Qt::Key_H)
   {
       qDebug() << "schneller";
   }

   if (event->key() ==  Qt::Key_L)
   {
       qDebug() << "langsamer";
   }
}


