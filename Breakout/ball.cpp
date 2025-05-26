#include "ball.h"
#include <QPainter>
#define RADIUS 10

Ball::Ball(QWidget *parent) : QLabel(parent)
{
    resize(RADIUS, RADIUS);
    // setPixmap(QPixmap("ball.png").scaled(RADIUS, RADIUS));
    setStyleSheet("background-color:rgba(0, 0, 0, 0");  //투명 배경 설정
}


void Ball::paintEvent(QPaintEvent *e){
    Q_UNUSED(e);

    QPainter p(this);
    p.setPen(QColor(Qt::transparent));
    p.setBrush(QColor("cornflowerblue"));
    p.drawEllipse(0, 0, RADIUS, RADIUS);
}
