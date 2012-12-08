#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "steuerung.h"


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

signals:
    void setServer(QString, int);


private slots:
    void setServerData();

    void on_okButton_clicked();

    void on_abbrechenButton_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
