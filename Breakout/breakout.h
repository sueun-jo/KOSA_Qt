#ifndef BREAKOUT_H
#define BREAKOUT_H

#include <QWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QMediaPlayer>
#include "ball.h"
#include "brick.h"
#include "paddle.h"


class QLabel;

class Breakout : public QWidget
{
    Q_OBJECT
private:
    static const int NO_OF_BRICKS = 30;

    Ball *ball;
    Paddle *paddle;
    Brick *bricks[NO_OF_BRICKS];

    QMediaPlayer *bgPlayer;
    QMediaPlayer *effectPlayer;

    int timerId;
    int xDir, yDir;

protected:
    void keyPressEvent(QKeyEvent *) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void timerEvent(QTimerEvent*) override;
    void moveObjects();
    void checkCollision();

protected:
    static const int MOVE_SPEED = 3; //패들 이동 속도
public:
    Breakout(QWidget *parent = nullptr);
    ~Breakout();
};
#endif // BREAKOUT_H
