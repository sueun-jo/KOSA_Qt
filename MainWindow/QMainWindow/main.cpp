#include "qteditor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtEditor w;
    w.resize(800, 800);
    w.show();
    return a.exec();
}
