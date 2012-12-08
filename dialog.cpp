#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{

    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setServerData()
{
    emit setServer(ui->clientAdress->text(),ui->clientPort->text().toInt());
}

void Dialog::on_okButton_clicked()
{
    setServerData();
    close();
}

void Dialog::on_abbrechenButton_clicked()
{
    close();
}
