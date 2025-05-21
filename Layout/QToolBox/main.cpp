#include "widget.h"

#include <QApplication>
#include <QToolBox>
#include <QDial>
#include <QCalendarWidget>
#include <QTextEdit>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QToolBox toolbox;
    toolbox.resize(300, 380);
    toolbox.show();

    QDial dial (&toolbox);
    QCalendarWidget calendarWidget(&toolbox);
    QTextEdit textEdit ("QTextEdit", &toolbox);
    toolbox.addItem(&dial, "Page &1");
    toolbox.addItem(&calendarWidget, "Page &2");
    toolbox.addItem(&textEdit, "Page &3");

    return app.exec();
}
