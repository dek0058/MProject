#include "MProjectServer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MProjectServer w;
    w.show();
    return a.exec();
}
