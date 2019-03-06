#include "playground.h"
#include <QApplication>
#include <mwindow.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //PlayGround w;
    Mwindow w;
    w.resize(400,600);
    w.show();

    return a.exec();
}
