#include <QTextEdit>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QKeySequence>
#include <QApplication>
#include <QToolBar>
#include <QFontComboBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QStatusBar>
#include <QDockWidget>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QColorDialog>
#include <QPrinter>
#include <QPrintDialog>

#include "qteditor.h"

QtEditor::QtEditor(QWidget *parent)
    : QMainWindow(parent)
{
    mdiArea = new QMdiArea(this);
    setCentralWidget(mdiArea);

#if 0 //edit메뉴를 수정한 후 0으로 변경
    QTextEdit *testedit = new QtextEdit(this);
    //setCentralWidget(mdiArea);
    mdiArea->addSubWindow(textedit);
#else
    QTextEdit *textedit = newFile(); //생성자의 제일 마지막으로 이동
#endif

    /*QDockWidget*/
    QWidget *w = new QWidget(this);
    QLabel *label = new QLabel ("Dock Widget", w);
    QDockWidget *dock = new QDockWidget ("Dock Widget", this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    dock->setWidget(w);

    QMenuBar *menubar = new QMenuBar(this);
    setMenuBar(menubar);

    /*filemenu 그룹*/
    QAction *newAct = makeAction (":/images/new.png", tr("&New"), QKeySequence::New,
                                 tr("make new file"), this, SLOT(newFile()));
    QAction *openAct = makeAction(":/images/open.png", tr("&Open"), QKeySequence::Open,
                                  tr("open a file"), this, SLOT(open()));
    QAction *saveAct = makeAction(":/images/save.png", tr("&Save"), tr("Ctrl+S"),
                                  tr("save a file"), this, SLOT(save()));
    QAction *saveAsAct = makeAction(":/images/saveAs.png", tr("&Save As"), QKeySequence::SaveAs,
                                  tr("save as a file"), this, SLOT(saveAs()));
    QAction *quitAct = makeAction (":/images/quit.png", tr("&Quit"), tr("Ctrl+Q"),
                                  tr("Quit this program"), qApp, SLOT(quit()));
    QAction *printAct = makeAction("printiconurl", tr("&Print"), QKeySequence::Print,
                                   tr("print a file"), this, SLOT(print()));

    QMenu *fileMenu = menubar->addMenu("&File"); //FileMenu추가

    /*filemenu 내에 있는 애들*/
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addAction(printAct);
    fileMenu->addAction(quitAct);


    /*edit menu group aciton*/
    QAction *undoAct = makeAction(":/images/undo.png", tr("&Undo"), QKeySequence::Undo,
                                  tr("Undo"), textedit, SLOT(undo()));
    QAction *redoAct = makeAction(":/images/redo.png", tr("&Redo"), QKeySequence::Redo,
                                  tr("Redo"), textedit, SLOT(redo()));
    QAction *copyAct = makeAction("copy.png", tr("&Copy"), tr("Ctrl+C"),
                                  tr(":/images/copy"), textedit, SLOT(copy()));
    QAction *cutAct = makeAction("cut.png", tr("&Cut"), QKeySequence::Cut,
                                  tr(":/images/cut"), textedit, SLOT(cut()));
    QAction *pasteAct = makeAction("paste.png", tr("&Paste"), tr("Ctrl+V"),
                                  tr(":/images/paste"), textedit, SLOT(paste()));
    QAction *zoomInAct = makeAction("zoomin.png", tr("&ZoomIn"), QKeySequence::ZoomIn,
                                   tr(":/images/zoomIn"), textedit, SLOT(zoomIn()));
    QAction *zoomOutAct = makeAction("zoomout.png", tr("&ZoomOut"), QKeySequence::ZoomOut,
                                   tr(":/images/zoomOut"), textedit, SLOT(zoomOut()));

    /*editmenu 추가하고 editmenu아래로 그룹원들 넣어주기*/
    QMenu *editMenu = menubar->addMenu("&Edit");
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addSeparator(); //구분자 추가
    editMenu->addAction(copyAct);
    editMenu->addAction(cutAct);
    editMenu->addAction(pasteAct);
    editMenu->addSeparator(); //구분자
    editMenu->addAction(zoomInAct);
    editMenu->addAction(zoomOutAct);

    /*Format메뉴에 QAction들*/
    QAction *alignCenterAct = makeAction(":/images/centeralign", tr("&Center"), QKeySequence(),
                                         tr("AlignCenter"), this, SLOT(alignText()));
    QAction *alignLeftAct = makeAction(":/images/leftalign", tr("&Left"), QKeySequence(),
                                       tr("Align Left"), this, SLOT(alignText()));
    QAction *alignRightAct = makeAction(":/images/rightalign", tr("&Right"), QKeySequence(), tr("Align Right"),
                                        this, SLOT(alignText()));

    QAction *colorAct = makeAction(":/images/color.png", tr("Set Color"), QKeySequence(),
                                   tr("Set text color"), this, [=]() {
                                       setColor();  // 여기서 리턴값은 안 써도 괜찮음
                                   });
    /* Format */
    QMenu *formatMenu = menubar->addMenu("&Format");
    QMenu *alignMenu= formatMenu->addMenu("&Align");
    QMenu *colorMenu = formatMenu->addMenu("&Color");

    alignMenu->addAction(alignCenterAct); // Format -> Aling -> center
    alignMenu->addAction(alignLeftAct); //alignleft
    alignMenu->addAction(alignRightAct); //alignright
    colorMenu->addAction(colorAct);

    /*Window 메뉴*/

    QAction *cascadeAct = makeAction("cascadeimageurl", tr("&Cascade"), QKeySequence(),
                                     tr("cascade"), mdiArea, SLOT(cascadeSubWindows()));
    QAction *tileAct = makeAction("tileimageurl", tr("&Tile"), QKeySequence(),
                                     tr("tile"), mdiArea, SLOT(tileSubWindows()));
    QMenu *windowMenu = menubar->addMenu("&Window"); //window메뉴 추가한거임
    windowMenu->addAction(cascadeAct);
    windowMenu->addAction(tileAct);

    /* Help menu */
    QMenu *helpMenu = menubar->addMenu("&Help");
    QMenu *aboutMenu = helpMenu->addMenu("&About");

    QAction *aboutAct = makeAction("", tr("About Qt"), QKeySequence(), tr("Show About Qt"), this, SLOT(aboutProgram()));
    aboutMenu->addAction(aboutAct);

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


    QMenu *toolbarMenu = windowMenu->addMenu("&Toolbar");
    toolbarMenu->addAction(fileToolBar->toggleViewAction());
    toolbarMenu -> addAction(dock->toggleViewAction());  /*QDockWidget tollbarMenu*/

    fontComboBox = new QFontComboBox(this);
    connect(fontComboBox, SIGNAL(currentFontChanged(QFont)), SLOT(setTextFont(QFont)));
    sizeSpinBox = new QDoubleSpinBox(this);
    connect(sizeSpinBox, SIGNAL(valueChanged(double)), SLOT(setTextSize(qreal)));

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
    connect(act, &QAction::triggered, this, lambda);
    return act;
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

void QtEditor::aboutProgram(){
    QMessageBox::about(this, "About Program",
                       "This is a Qt Text Editor made by Sueun.\nVersion 1.0\nPowered by Qt.");
}

QTextEdit *QtEditor::newFile(){
    qDebug("Make New File");
    QTextEdit *textedit = new QTextEdit;
    mdiArea -> addSubWindow(textedit);
    textedit->show();
    return textedit;
}


/*alignText 사용자 정의 슬롯 정의구현*/
void QtEditor::alignText(){

    /*기존 align 코드*/
    // QAction *action = qobject_cast<QAction*> (sender());
    // if(action->text().contains("Left", Qt::CaseInsensitive))
    //     textedit->setAlignment(Qt::AlignLeft);
    // else if(action->text().contains("Center", Qt::CaseInsensitive))
    //     textedit->setAlignment(Qt::AlignCenter);
    // else if(action->text().contains("Right", Qt::CaseInsensitive))
    //     textedit->setAlignment(Qt::AlignRight);

    QAction *action = qobject_cast<QAction*>(sender());
    QMdiSubWindow *subWindow = mdiArea->currentSubWindow();
    if (subWindow != nullptr){
    QTextEdit *textedit = dynamic_cast<QTextEdit*>(subWindow->widget());
    if(action->text().contains("Left", Qt::CaseInsensitive))
        textedit->setAlignment(Qt::AlignLeft);
    else if(action->text().contains("Center", Qt::CaseInsensitive))
        textedit->setAlignment(Qt::AlignCenter);
    else if(action->text().contains("Right", Qt::CaseInsensitive))
        textedit->setAlignment(Qt::AlignRight);
    }
}

// void QtEditor::setTextSize(qreal size){
//     QTextEdit *
// }

void QtEditor::openFile(){
    QString filename = QFileDialog::getOpenFileName(this, "Select file to open",
                                                    QDir::home().dirName(), "Text File(*.txt *.html *.c *.cpp *.h)");
    qDebug() << filename;
}

void QtEditor::saveFile(){
    QString filename = QFileDialog::getSaveFileName(this, "Select file to save",
                                                    ".", "Text File(*.txt *.html *.c *.cpp *.h)");
    qDebug() << filename;
}


void QtEditor::saveAsFile(){
    QString filename = QFileDialog::getSaveFileName(this, "Select file to save as",
                                                    ".", "Text File(*.txt *.html *.c *.cpp *.h)");
    qDebug() << filename;
}

void QtEditor::setColor(){
    QTextEdit *textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    QColor color = QColorDialog::getColor(textedit->textColor(), this);
    if(color.isValid()) textedit->setTextColor(color);
}

void QtEditor::print(){
    QPrinter printer (QPrinter::HighResolution);
    printer.setFullPage(true);
    QPrintDialog printDialog(&printer, this);
    if(printDialog.exec()==QDialog::Accepted){
        QTextEdit* textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
        textedit->print(&printer);
    }

}
