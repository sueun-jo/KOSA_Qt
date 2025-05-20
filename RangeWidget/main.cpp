#include "widget.h"

#include <QApplication>
#include <QSlider>
#include <QStyleFactory>

#include <QProgressBar>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget w;

    QProgressBar bar(&w);
    bar.setGeometry(10, 10, 150, 20);

    QSlider slider(&w);
    slider.setGeometry(10, 40, 150, 20 );
    slider.setOrientation(Qt::Horizontal);

    QObject::connect(&slider, SIGNAL(valueChanged(int)), &bar, SLOT(setValue(int)));
    w.show();



    return a.exec();
}
