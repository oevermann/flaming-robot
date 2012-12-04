#ifndef STEUERUNG_H
#define STEUERUNG_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QtGui>
#include <QMutexLocker>
#include "daten.h"
#include "server.h"

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
    void on_actionInfo_triggered();

    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);

    void on_start_clicked();

private:
    Ui::Steuerung *ui;
    QGraphicsScene scene;
    Daten *data;
    QMutexLocker *mutex;
    Server *server;
    int rotate;
    int left;
    int right;
    void drawScene(int height, int width, int left, int right);
    void fly();
    bool key[];

};

#endif // STEUERUNG_H
