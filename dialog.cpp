 #include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->clientAdress->setText("localhost");
    ui->clientPort->setText("1234");
}

Dialog::~Dialog()
{
    delete ui;
}
//führt das Signal setserver aus durch den ie Server-Adresse und der Server-Port an die Steuerung übertragen werden
void Dialog::setServerData()
{
    emit setServer(ui->clientAdress->text(),ui->clientPort->text().toInt());
}

//führt die Funktion setServerData aus und schließt den Dialog
void Dialog::on_okButton_clicked()
{
    setServerData();
    close();
}

//schließt den Dialog
void Dialog::on_abbrechenButton_clicked()
{
    close();
}
