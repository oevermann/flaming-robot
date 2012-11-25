#ifndef STEUERUNG_H
#define STEUERUNG_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QtGui>

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

    void on_pushButton_7_clicked();

private:
    Ui::Steuerung *ui;
    QGraphicsScene scene;
    int rotate;
    int left;
    int right;
    void drawScene(QGraphicsScene &scene, int height, int width, int left, int right);
};

#endif // STEUERUNG_H
