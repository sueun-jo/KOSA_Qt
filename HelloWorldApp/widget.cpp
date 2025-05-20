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

    connect(quit, SIGNAL(clicked()), this, SLOT(slotQuit()));
    QLabel *label = new QLabel("<font color = blue> Hello Qt! </font>", this);
    label-> setGeometry(10, 50, 75, 35);
    label->setObjectName("label1");
    connect(quit, SIGNAL(clicked()), this, SLOT(slotQuit()));

}
void Widget::slotQuit(){
    qDebug("slotQuit");
    // qApp-> quit();
    // emit clicked(); //clicked()는 발생시키는 것 (emit)
    QLabel *label = findChild<QLabel *>("label1");
    qDebug("%s", qPrintable(label->metaObject()->className()));
    label->setText("World");
}
Widget::~Widget() {}
