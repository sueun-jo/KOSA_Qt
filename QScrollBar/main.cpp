// #include "widget.h"

// #include <QApplication>
// #include <QScrollArea>
// #include <QScrollBar>
// #include <QLabel>

// int main(int argc, char *argv[])
// {
//     QApplication a(argc, argv);

//     QLabel *label = new QLabel ("220125001201931012342134123412342");
//     QScrollArea* scrollArea = new QScrollArea;
//     scrollArea-> setBackgroundRole(QPalette::Dark);
//     scrollArea-> setWidget(label);
//     scrollArea-> resize(60, 30);
//     scrollArea->show();

//     QScrollBar *slider = scrollArea-> horizontalScrollBar();
//     slider->setValue(slider->maximum());

//     return a.exec();
// }


// Qdial 예제
// #include "widget.h"
// #include <QDial>
// #include <QApplication>

// int main(int argc, char* argv[]){
//     QApplication a(argc, argv);

//     QDial *dial = new QDial();
//     dial-> setWrapping(true);
//     dial-> setNotchesVisible(true);
//     dial-> setNotchTarget(10);
//     dial->show();


//     return a.exec();
// }

// //QSpinBox
// #include <QApplication>
// #include <QSpinBox>

// int main(int argc, char* argv[]){
//     QApplication a(argc, argv);

//     QSpinBox *spinBox = new QSpinBox();
//     spinBox->setRange(0, 10);
//     spinBox->setSuffix("%");
//     spinBox->setWrapping(true);
//     spinBox->setSpecialValueText("Percent");
//     spinBox->show();

//     return a.exec();
// }


// #include <QTime>
// #include <QTimeEdit>
// #include <QDate>
// #include <QDateEdit>
// #include <QApplication>

// int main(int argc, char* argv[]){

//     QApplication a(argc, argv);
//     QTimeEdit *timeEdit = new QTimeEdit(0);
//     timeEdit->setTime(QTime::currentTime());
//     timeEdit->show();

//     QDateEdit *dateEdit = new QDateEdit(QDate::currentDate(), 0);
//     dateEdit->setCalendarPopup(true);
//     dateEdit->show();

//     return a.exec();
// }


// //QLineEdit 예제
// #include <QApplication>
// #include <QLineEdit>

// int main(int argc, char *argv[]){
//     QApplication a (argc, argv);

//     QLineEdit *lineEdit = new QLineEdit();
//     lineEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);
//     lineEdit->setInputMask("000");
//     lineEdit->setPlaceholderText("input the number");
//     lineEdit->show();

//     return a.exec();
// }

//QComboBox 위젯
#include <QApplication>
#include <QComboBox>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    QComboBox *comboBox = new QComboBox();
    comboBox-> addItem("KDE");
    comboBox-> addItem("GNOME");
    comboBox-> addItem("FVWM");
    comboBox-> addItem ("CDE");
    comboBox->setEditable(true);
    comboBox-> show();

    return a.exec();
}
