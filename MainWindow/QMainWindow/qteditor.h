#ifndef QTEDITOR_H
#define QTEDITOR_H

#include <QMainWindow>
class QLabel;
class QAction;
class QMdiArea;
class QTextEdit;
class QFontComboBox;
class QDoubleSpinBox;

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

    QMdiArea *mdiArea;
    QFontComboBox *fontComboBox;
    QDoubleSpinBox *sizeSpinBox;


public slots:
    QTextEdit *newFile();

    // void newFile();
    void open();
    void save();
    void saveAs();
    void quit();

    void alignText();

    void aboutProgram();
    void openFile();
    void saveFile();
    void saveAsFile();

    void setColor();
    void print();



};


#endif // QTEDITOR_H
