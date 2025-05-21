#include "widget.h"
#include <QGroupBox>
#include <QFormLayout>
#include <QtWidgets>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QStringList labels;
    labels << "&IP Address" << "&Mac Address" << "&Date";
    QLineEdit* lineEdit[3];
    QFormLayout *formLayout = new QFormLayout;
    for (int i=0; i<3; i++){
        lineEdit[i] = new QLineEdit(this);
        formLayout -> addRow(labels.at(i), lineEdit[i]);
    }

    QGroupBox *groupBox = new QGroupBox ("&name Group", this);
    groupBox-> move(5, 5);
    groupBox-> setLayout(formLayout);

    resize(groupBox->sizeHint().width()+10, groupBox->sizeHint().height()+10);
}

Widget::~Widget() {}
