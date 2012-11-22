#include <QtGui/QApplication>
#include "steuerung.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Steuerung w;
    w.show();
    
    return a.exec();
}
