#include "widget.h"

#include <QDir>                 //디렉토리 조작을 위한 헤더파일
#include <QFile>                //파일조작을 위한 헤더파일
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QVBoxLayout>
#include <QTextEdit>            //파일 내용과 결과 표시를 위해
#include <QMenu>                //컨텍스트 메뉴를 위한 헤더파일
#include <QContextMenuEvent>
#include <QApplication>
#include <QMessageBox>
#include <QTextStream>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    directory = new QDir("."); //현재 디렉토리 내용 저장하는 객체

    /*메뉴를 위한 액션들 정의*/
    QAction *mkdirAction = new QAction("&Make Directory", this);
    connect (mkdirAction, SIGNAL(triggered()), SLOT(makeDir()));

    QAction *copyAction = new QAction("&Copy", this);
    connect (copyAction, SIGNAL(triggered()), SLOT(copyFile()));

    QAction *removeAction = new QAction("&Remove", this);
    connect (removeAction, SIGNAL(triggered()), SLOT(removeDir()));

    QAction *renameAction = new QAction("&Copy", this);
    connect (renameAction, SIGNAL(triggered()), SLOT(renameDir()));

    QAction *quitAction = new QAction("&Copy", this);
    connect (quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    /* 액션을 메뉴에 추가 */
    m_menu = new QMenu(this);
    m_menu->addSection("&Directory");
    m_menu->addAction(mkdirAction);
    m_menu->addSeparator();
    m_menu->addSection("&File");
    m_menu->addAction(copyAction);
    m_menu->addAction(removeAction);
    m_menu->addAction(renameAction);
    m_menu->addSeparator();
    m_menu->addAction(quitAction);

    /*화면에 표시될 위젯들을 정의하고 레이아웃*/

    dirListWidget = new QListWidget(this);
    filenameLineEdit = new QLineEdit(this);

    outputEdit = new QTextEdit(this);
    outputEdit->setReadOnly(true);

    QPushButton *actionButton = new QPushButton("Action", this);
    actionButton->setMenu(m_menu); /*팝업메뉴 설정*/

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(dirListWidget);
    layout->addWidget(filenameLineEdit);
    layout->addWidget(actionButton);
    layout->addWidget(outputEdit);

    /*시그널과 슬롯을 연결*/

    connect(dirListWidget, SIGNAL(itemClicked(QListWidgetItem*)), SLOT (selectItem(QListWidgetItem*)));
    connect(dirListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), SLOT (changeDir()));
    refreshDir(); //현재 디렉토리의 내용을 QListWidget에 표시

}

Widget::~Widget() {} //소멸자

void Widget::refreshDir(){ //디렉토리 갱신
    dirListWidget->clear(); //현재 QListWidget의 내용을 모두 삭제

    /*QDir 클래스에 저장된 현재 파일 목록을 QListWidget에 아이템으로 추가*/
    for (int index=0; index<directory ->entryList().count(); index++)
        dirListWidget->addItem(directory->entryList().at(index));
}

/*마우스 오른쪽 버튼 누르면 context 메뉴 표시*/
void Widget::selectItem(QListWidgetItem* item){
    filenameLineEdit->setText(item->text());
}

/*파일 복사*/
void Widget::copyFile(){
    QString filename = directory -> absoluteFilePath(
        dirListWidget->currentItem()->text());

    QFileInfo checkDir(filename);
    if(checkDir.isFile() && filenameLineEdit->text().length()){
        QString newFile = directory->absoluteFilePath(filenameLineEdit->text());
        QFile::copy(filename, newFile); //QFile의 static method 사용
    }
    directory -> refresh();
    refreshDir();
}

/* QListWidget을 더블클릭하면 호출*/
void Widget::changeDir(){
    /*현재 파일 경로를 절대 경로로 변경*/
    QString filename = directory -> absoluteFilePath(
        dirListWidget->currentItem()->text());

    QFileInfo checkDir(filename);
    if (checkDir.isDir()){ //디렉토리면 파일 이동 후 QListWidget 갱신
        directory -> cd(filename);
        directory -> refresh();
        refreshDir();
    }
}

void Widget::makeDir(){ //디렉토리 생성
    if (filenameLineEdit->text().length()){
        directory->mkdir(filenameLineEdit->text());
        directory->refresh(); //QDir클래스는 현재 디렉토리 정보 캐싱
        refreshDir();
    }
}

void Widget::removeDir(){
    if(filenameLineEdit->text().length() && dirListWidget->currentItem() != NULL){
        QString filename = directory -> absoluteFilePath(
            dirListWidget->currentItem()->text());
        QFileInfo checkDir(filename);
        if(checkDir.isDir())
            directory->rmdir(filenameLineEdit->text());
        else if (checkDir.isFile())
            QFile::remove(filename);
        directory->refresh();
        refreshDir();
    }
}

/*디렉토리나 파일 이름 변경*/
void Widget::renameDir(){
    if(filenameLineEdit->text().length() && dirListWidget->currentItem() != NULL){
        directory->rename(dirListWidget->currentItem()->text(), filenameLineEdit->text());
        directory->refresh();
        refreshDir();
    }
}

/*컨텍스트 메뉴 오픈*/

void Widget::contextMenuEvent(QContextMenuEvent *event){
    QWidget::contextMenuEvent(event);
    m_menu->exec(QCursor::pos());
}

