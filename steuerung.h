#ifndef STEUERUNG_H
#define STEUERUNG_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QtGui>
#include <QMutexLocker>
#include "daten.h"
#include "dialog.h"
#include "server.h"
#include "client.h"
#include "updatethread.h"

namespace Ui {
class Steuerung;
}

class Steuerung : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Steuerung(QWidget *parent = 0);
    ~Steuerung();

public slots:
    void connectionError(QString error);
//    void setPos(QString pos);
//    void setGeschwindigkeit(QString speed);

private slots:
    void on_actionVerbindung_triggered();
    void on_actionSchlie_en_triggered();
    void on_actionInfo_triggered();

    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);

    void on_start_clicked();

    void setClient(QString address, int port);

private:
    Ui::Steuerung *ui;
    QGraphicsScene scene;
    Daten *data;
    QMutexLocker *mutex;
    Server *server;
    Client *client;
    QString clientAddress;
    UpdateThread *simulation;
    int port;
    int rotate;
    int left;
    int right;
    void drawScene(int height, int width, int left, int right);
    void fly();
    bool *key;

};

#endif // STEUERUNG_H
