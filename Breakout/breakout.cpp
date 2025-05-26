#include <QLabel>
#include <QApplication>
#include <QErrorMessage>
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

void Breakout::checkCollision(){
    if (ball->geometry().bottom() > height()){ //공이 아래로 가면 게임 종료
        killTimer(timerId);

        QErrorMessage *message = new QErrorMessage();
        message->showMessage("you died");
    }

    int j=0;
    for (int i=0; i< NO_OF_BRICKS; i++)
        if(bricks[i]->isHidden()) j++;

    if ( j == NO_OF_BRICKS ){
        killTimer(timerId);

        QErrorMessage *message = new QErrorMessage();
        message->showMessage("you win");
        qDebug("You Win!");
    }

    /* paddle(사용자)와의 충돌 처리*/
    if ((ball->geometry()).intersects(paddle->geometry())){ //ball이 paddle와 intersects(교집합, 즉 충돌)
        int paddleLPos = paddle->geometry().left();
        int ballLPos = ball->geometry().left();
        int first = paddleLPos + 8;
        int second = paddleLPos + 16;
        int third = paddleLPos + 24;
        int fourth = paddleLPos + 32;

        /*paddle 맞은 부분에 따라 공의 반사되는 방향 조정*/
        if (ballLPos<first) xDir = -1, yDir = -1;
        if (ballLPos>=first&& ballLPos < second) xDir = -1, yDir *= -1;
        if (ballLPos>= second && ballLPos < third) xDir=0, yDir = -1;
        if (ballLPos>= third && ballLPos < fourth) xDir=1, yDir = -1;
        if (ballLPos > fourth) xDir =1, yDir =-1;
    }

    /*블록 충돌 처리*/
    for (int i=0; i < NO_OF_BRICKS; i++){
        if ((ball->geometry()).intersects(bricks[i]->geometry())){
            int ballLeft = ball->geometry().left();
            int ballHeight = ball->geometry().height();
            int ballWidth = ball->geometry().width();
            int ballTop = ball->geometry().top();

            /*현재 블록 위치 계산*/
            QPoint pointRight (ballLeft + ballWidth + 1, ballTop);
            QPoint pointLeft(ballLeft - 1, ballTop);
            QPoint pointTop(ballLeft, ballTop-1);
            QPoint pointBottom(ballLeft, ballTop+ballHeight+1);

            if(!bricks[i]->isHidden()){ /*공과 블럭의 충돌 검사*/
                if(bricks[i]->geometry().contains(pointRight)) xDir = -1;
                else if (bricks[i]->geometry().contains(pointLeft)) xDir = 1;
                if(bricks[i]->geometry().contains(pointTop)) yDir = 1;
                else if (bricks[i]->geometry().contains(pointBottom)) yDir = -1;

                bricks[i]->setHidden(true);
            }
        }
    }
}



/*timer로 화면 그려준다*/
void Breakout::timerEvent(QTimerEvent *e){
    Q_UNUSED(e);
    moveObjects();
    checkCollision();
}

/*공의 움직임*/
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
