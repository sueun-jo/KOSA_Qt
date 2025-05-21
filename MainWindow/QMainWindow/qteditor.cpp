#include "qteditor.h"
#include <QTextEdit>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QKeySequence>
#include <QApplication>
#include <QIcon>
#include <QToolBar>
#include <QFontComboBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QStatusBar>

QtEditor::QtEditor(QWidget *parent)
    : QMainWindow(parent)
{
    textedit = new QTextEdit(this);
    setCentralWidget(textedit);
    QMenuBar *menubar = new QMenuBar(this);
    setMenuBar(menubar);

    /*filemenu 그룹*/
    QAction *newAct = makeAction ("new.png", tr("&New"), QKeySequence::New,
                                 tr("make new file"), this, SLOT(newFile()));
    QAction *openAct = makeAction("open.png", tr("&Open"), QKeySequence::Open,
                                  tr("open a file"), this, SLOT(open()));
    QAction *saveAct = makeAction("save.png", tr("&Save"), tr("Ctrl+S"),
                                  tr("save a file"), this, SLOT(save()));
    QAction *saveAsAct = makeAction("saveAs.png", tr("&Save As"), QKeySequence::SaveAs,
                                  tr("save as a file"), this, SLOT(saveAs()));
    QAction *quitAct = makeAction ("quit.png", tr("&Quit"), tr("Ctrl+Q"),
                                  tr("Quit this program"), qApp, SLOT(quit()));

    QMenu *fileMenu = menubar->addMenu("&File"); //FileMenu추가
    /*filemenu 내에 있는 애들*/
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addAction(quitAct);

    /*edit menu group aciton*/
    QAction *undoAct = makeAction("undo.png", tr("&Undo"), QKeySequence::Undo,
                                  tr("Undo"), textedit, SLOT(undo()));
    QAction *redoAct = makeAction("redo.png", tr("&Redo"), QKeySequence::Redo,
                                  tr("Redo"), textedit, SLOT(redo()));
    QAction *copyAct = makeAction("copy.png", tr("&Copy"), tr("Ctrl+C"),
                                  tr("Copy"), textedit, SLOT(copy()));
    QAction *cutAct = makeAction("cut.png", tr("&Cut"), QKeySequence::Cut,
                                  tr("Cut"), textedit, SLOT(cut()));
    QAction *pasteAct = makeAction("paste.png", tr("&Paste"), tr("Ctrl+V"),
                                  tr("Paste"), textedit, SLOT(paste()));
    QAction *zoomInAct = makeAction("zoomin.png", tr("&ZoomIn"), QKeySequence::ZoomIn,
                                   tr("ZoomIn"), textedit, SLOT(zoomIn()));
    QAction *zoomOutAct = makeAction("zoomout.png", tr("&ZoomOut"), QKeySequence::ZoomOut,
                                   tr("ZoomOut"), textedit, SLOT(zoomOut()));

    /*editmenu 추가하고 editmenu아래로 그룹원들 넣어주기*/
    QMenu *editMenu = menubar->addMenu("&Edit");
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addSeparator(); //구분자 추가
    editMenu->addAction(copyAct);
    editMenu->addAction(cutAct);
    editMenu->addAction(pasteAct);
    editMenu->addSeparator();
    editMenu->addAction(zoomInAct);
    editMenu->addAction(zoomOutAct);

    /*Format메뉴에 QAction들*/
    QAction *alignCenterAct = new QAction("&Center", this);

    /*Format메뉴를 추가할게용*/
    QMenu *formatMenu = menubar->addMenu("&Format");
    QMenu *alignMenu= formatMenu->addMenu("&Align");
    alignMenu->addAction(alignCenterAct);

    /*format-aling-connect-test*/
    //(1) connect(alignCenterAct, SIGNAL(triggered()), textedit, SLOT(setAlignment(Qt::AlignCenter)));
    // (2) connect(alignCenterAct, SIGNAL(triggered(Qt::AlignCenter)), textedit, SLOT(setAlignment(Qt::AlignCenter)));
    connect(alignCenterAct, &QAction::triggered, this,[=]{textedit->setAlignment(Qt::AlignCenter);});





    /*Status Bar*/
    QStatusBar *statusbar = statusBar();
    QLabel *statusLabel = new QLabel(tr("Qt Editor"), statusbar); //status bar 이름 지어주기
    statusLabel->setObjectName("StatusLabel");
    statusbar->addPermanentWidget(statusLabel);
    statusbar->showMessage("started", 1500);

    /*Tool Bar*/
    QToolBar *fileToolBar = addToolBar("&File");
    fileToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    fileToolBar->addAction(newAct);

    fileToolBar->addSeparator();
    fileToolBar->addAction(quitAct);

    QMenu *windowMenu = menubar->addMenu("&Window");
    QMenu *toolbarMenu = windowMenu->addMenu("&Toolbar");
    toolbarMenu->addAction(fileToolBar->toggleViewAction());

    QFontComboBox *fontComboBox = new QFontComboBox(this);
    connect(fontComboBox, SIGNAL(currentFontChanged(QFont)), textedit, SLOT(setCurrentFont(QFont)));
    QDoubleSpinBox *sizeSpinBox = new QDoubleSpinBox(this);
    connect(sizeSpinBox, SIGNAL(valueChanged(double)), textedit, SLOT(setFontPointSize(qreal)));

    addToolBarBreak(); //다음툴바 아랫줄 위치

    QToolBar *formatToolbar = addToolBar("&Format");
    formatToolbar->addSeparator();
    formatToolbar->addWidget(fontComboBox);
    formatToolbar->addWidget(sizeSpinBox);

}

QtEditor::~QtEditor() {}

template <typename T>
QAction *QtEditor::makeAction(QString icon, QString text, T shortCut,
                              QString toolTip, QObject* recv, const char* slot)
{
    QAction *act = new QAction(text, this);
    if(icon.length()) act->setIcon(QIcon(icon));
    act->setShortcut(shortCut);
    act->setStatusTip(toolTip);
    connect(act, SIGNAL(triggered()), recv, slot);
    return act;
}

template <typename T, typename Functor>
QAction *QtEditor::makeAction(QString icon, QString text, T shortCut,
                              QString toolTip, QObject* recv, Functor lambda)
{
    QAction *act = new QAction(text, this);
    if(icon.length()) act->setIcon(QIcon(icon));
    QKeySequence keySequence(shortCut);
    act->setStatusTip(toolTip);
    connect(act, SIGNAL(triggered()), this, lambda);
    return act;
}


void QtEditor::newFile(){
    qDebug("Make New File");
}

void QtEditor::open(){
    qDebug("Open a file");
}

void QtEditor::save(){
    qDebug("save a file");
}

void QtEditor::saveAs(){
    qDebug("save as a file");
}

void QtEditor::quit(){
    qDebug("quit");
}

/*alignText 사용자 정의 슬롯 정의구현*/
void QtEditor::alignText(){
    QAction *action = qobject_cast<QAction*> (sender());
    if(action->text().contains("Left", Qt::CaseInsensitive))
        textedit->setAlignment(Qt::AlignLeft);
    else if(action->text().contains("Center", Qt::CaseInsensitive))
        textedit->setAlignment(Qt::AlignCenter);


}



