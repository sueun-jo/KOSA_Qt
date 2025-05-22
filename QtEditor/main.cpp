#include "qteditor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtEditor w;
    w.resize(1000, 1000);
    w.show();
    return a.exec();
}
