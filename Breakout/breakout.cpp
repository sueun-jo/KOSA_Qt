#include <QLabel>
#include <QApplication>

#include "breakout.h"

#define WIDTH 50
#define HEIGHT 12
#define SCR_WIDTH 300
#define SCR_HEIGHT 400

Breakout::Breakout(QWidget *parent)
    : QWidget(parent), xDir(1), yDir(-1)
{
    /* ball */
    ball = new QLabel(this);
    ball->setGeometry(SCR_WIDTH*0.8, SCR_HEIGHT*0.875, 10, 10);
    ball->setStyleSheet("QLabel {background-color:CornflowerBlue; border-radius:5px;}"); //ball만들기

    /* paddle */
    paddle = new QLabel(this);
    paddle->setGeometry(SCR_WIDTH*0.7, SCR_HEIGHT*0.9, WIDTH, HEIGHT );
    paddle->setStyleSheet("QLabel {background-color:lightgray;}");

    /* bricks */
    for (int y=0, i=0; y < 5; y++)
        for (int x=0; x<6; x++, i++){
            bricks[i] = new QLabel(this);
            bricks[i]->setStyleSheet("QLabel {background-color:AliceBlue; border:1px solid gray}");
            bricks[i]->setGeometry(x*WIDTH, y*HEIGHT+30, WIDTH, HEIGHT);
        }

    resize(SCR_WIDTH, SCR_HEIGHT);

    setMouseTracking(true);

    timerId = startTimer(10);
}

Breakout::~Breakout(){
    delete ball;
    delete paddle;

    for (int i=0; i < NO_OF_BRICKS; i++)
        delete bricks[i];
}

void Breakout::timerEvent(QTimerEvent *e){
    Q_UNUSED(e);
    moveObjects();
}

void Breakout::moveObjects(){
    ball->move(ball->x() + xDir, ball->y() + yDir);

    if ((ball->x() <= 0)|| (ball->x()+10 >=SCR_WIDTH)){ //경계검사
        xDir *= -1;
    }

    if (ball->y() <= 0) yDir = 1;
}

void Breakout::keyPressEvent(QKeyEvent *e){

    int x = paddle->x();

    switch(e->key()){
    case Qt::Key_Left:
        x -= MOVE_SPEED;
        if (x<0)
            x = 0;
        paddle->move(x, paddle->y());
        break;
    case Qt::Key_Right:
        x += MOVE_SPEED;
        if (x + WIDTH > width())
            x = width() - WIDTH;
        paddle->move(x, paddle->y());
        break;
    case Qt::Key_Escape:
        qApp->exit();
        break;
    default:
        QWidget::keyPressEvent(e);
    }
}

void Breakout::mouseMoveEvent(QMouseEvent *e){
    int x = e->pos().x();
    x = (x<0) ? 0 : (x+WIDTH>width())? width()-WIDTH:x; //경계검사
    paddle->move(x, paddle->y());
}
