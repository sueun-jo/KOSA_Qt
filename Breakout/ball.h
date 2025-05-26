#ifndef BALL_H
#define BALL_H

#include <QWidget>
#include <QLabel>

class Ball : public QLabel
{
    Q_OBJECT
public:
    Ball(QWidget *parent = nullptr);

private:
    void paintEvent(QPaintEvent*) override;
// signals:
};

#endif // BALL_H
