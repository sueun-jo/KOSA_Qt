#ifndef QTEDITOR_H
#define QTEDITOR_H

#include <QMainWindow>

class QAction;
class QTextEdit;

class QtEditor : public QMainWindow
{
    Q_OBJECT

public:
    QtEditor(QWidget *parent = nullptr);
    ~QtEditor();

private:

    template <typename T>
    QAction *makeAction(QString icon, QString text, T shortCut, \
                        QString toolTip, QObject* recv, const char* slot);

    template <typename T, typename Functor>
    QAction *makeAction(QString icon, QString text, T shortCut,
                        QString toolTip, QObject* recv, Functor lambda);

    QTextEdit *textedit;

public slots:
    void newFile();
    void open();
    void save();
    void saveAs();
    void quit();

    void alignText();
};




#endif // QTEDITOR_H
