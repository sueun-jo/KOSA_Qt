#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QDir;
class QListWidget;
class QListWidgetItem;
class QLineEdit;
class QTextEdit;
class QMenu;
class QContextMenuEvent;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    /*컨텍스트 메뉴를 위한 이벤트 핸들러*/
    void contextMenuEvent(QContextMenuEvent*);

private:
    void refreshDir();

    QDir *directory;
    QListWidget *dirListWidget;
    QLineEdit *filenameLineEdit;
    QTextEdit *outputEdit;
    QMenu  *m_menu;

public slots:
    void selectItem(QListWidgetItem *);
    void changeDir();
    void copyFile();
    void makeDir();
    void removeDir();
    void renameDir();
};
#endif // WIDGET_H
