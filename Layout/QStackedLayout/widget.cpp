#include "widget.h"
#include <QStackedLayout>
#include <QHBoxLayout>
#include <QDial>
#include <QLabel>
#include <QCalendarWidget>
#include <QTextEdit>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QDial *dial = new QDial(this);
    dial-> setRange(0, 2);

    QLabel *label = new QLabel("Stack 1", this);
    QCalendarWidget *calendarWidget = new QCalendarWidget (this);
    QTextEdit *textEdit = new QTextEdit("Stack3", this);

    QStackedLayout *stackedLayout = new QStackedLayout();
    stackedLayout->addWidget(label);
    stackedLayout->addWidget(calendarWidget);
    stackedLayout->addWidget(textEdit);
    //layout에 각 요소 배치

    connect(dial, &QDial::valueChanged, stackedLayout, &QStackedLayout::setCurrentIndex);
    //sender: dial, SIGNAL: valueChanged, receiver: stackedLayout, SLOT: setCurrentIndex

    QHBoxLayout *hBoxLayout = new QHBoxLayout(this);
    hBoxLayout -> addWidget(dial);
    hBoxLayout -> addLayout(stackedLayout);

    setLayout(hBoxLayout);

}

Widget::~Widget() {}
