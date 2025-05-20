//#include "widget.h"
#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPushButton quit("Quit", nullptr);
    quit.resize(75, 35);
    quit.show();

    //QObject::connect(sender, SIGNAL(signal), receiver, SLOT(slot));
    QObject::connect(&quit, SIGNAL(clicked()), &a, SLOT(quit()));

    return a.exec();
}
