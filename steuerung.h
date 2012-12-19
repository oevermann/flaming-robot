#ifndef STEUERUNG_H
#define STEUERUNG_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QtGui>
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


private slots:
    void on_actionVerbindung_triggered();
    void on_actionSchlie_en_triggered();
    void on_actionInfo_triggered();

    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);

    void on_start_clicked();

    void setClient(QString address, int port);

    void setPos(const QString &pos);
    void setAirspeed(const QString &airspeed);
    void setGroundspeed(const QString &groundspeed);
    void setHeight(const QString &height);

    void on_stop_clicked();

private:
    Ui::Steuerung *ui;
    QGraphicsScene scene;
    QGraphicsScene scenekomp;
    QGraphicsScene scenewind;
    Daten *data;
    Server *server;
    Client *client;
    UpdateThread *simulation;
    QString clientAddress;
    int port;
    bool *key;
    void setControlData();
};

#endif // STEUERUNG_H
