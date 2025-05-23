#include "widget.h"

#include <QApplication>
#include <QLabel>

#ifdef Q_OS_MACOS
#define kor(str) QStirng::fromUtf8(str)
#else
#define kor(str) QString::fromLocal8Bit(str)
#endif
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QLabel *hellolabel = new QLabel ("<font color=blue> 안녕 <ㅑ>Qt!</i></font>", 0);
    hellolabel->show();
    hellolabel->resize(75,35);


    return app.exec();
}
