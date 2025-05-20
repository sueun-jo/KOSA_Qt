#include "mainwindow.h"
#include <QApplication>



// //QLCDNumber 위젯 예제
// #include <QLCDNumber>
// int main(int argc, char *argv[])
// {
//     QApplication a(argc, argv);

//     QLCDNumber *lcd = new QLCDNumber();
//     lcd->setDecMode();
//     lcd-> setSegmentStyle(QLCDNumber::Flat);
//     lcd->display(2000);
//     //lcd->setDigitCount(15);
//     lcd->show();

//     //w.show();
//     return a.exec();
// }



// #include <QProgressBar>
// #include <Qtimer>
// int main(int argc, char *argv[]){
//     QApplication a(argc, argv);

//     QProgressBar *progBar = new QProgressBar();
//     progBar->show();

//     QTimer timer;
//     int n=0;
//     QObject::connect(&timer, &QTimer::timeout, [&]{progBar->setValue(++n%100);});
//     timer.start(20);
//     //progBar-> setInvertedAppearance(true);
//     //progBar->show();

//     return a.exec();

// }

#include <QTextBrowser>
#include <QUrl>

int main(int argc, char *argv[]){
    QApplication a (argc, argv);

    QTextBrowser *tb = new QTextBrowser();
    tb-> setSource(QUrl("index.html"));
    tb-> show();

    return a.exec();
}



