#ifndef STEUERUNG_H
#define STEUERUNG_H

#include <QMainWindow>
#include <QKeyEvent>

namespace Ui {
class Steuerung;
}

class Steuerung : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Steuerung(QWidget *parent = 0);
    ~Steuerung();


private slots:
    void on_actionVerbindung_triggered();

    void on_actionSchlie_en_triggered();

    void keyPressEvent(QKeyEvent *);

    void on_actionInfo_triggered();

private:
    Ui::Steuerung *ui;
};

#endif // STEUERUNG_H
