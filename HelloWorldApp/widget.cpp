#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QPushButton *quit = new QPushButton("&Quit", this);
    quit-> move(10, 10);
    quit-> resize(75, 35);

    QLabel *label = new QLabel("<font color = blue> Hello Qt! </font>", this);
    label-> setGeometry(10, 50, 75, 35);

}

Widget::~Widget() {}
