#include "ide.h"
#include <QApplication>
#include <QtPlugin>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IDE w;
    w.show();

    return a.exec();
}
