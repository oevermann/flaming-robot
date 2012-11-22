#include "steuerung.h"
#include "ui_steuerung.h"
#include "dialog.h"

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
