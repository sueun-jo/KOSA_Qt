#ifndef PADDLE_H
#define PADDLE_H

#include <QWidget>
#include <QLabel>
class Paddle : public QWidget
{
    Q_OBJECT
public:
    Paddle(QWidget *parent = nullptr);

private:
    void paintEvent(QPaintEvent*) override;

signals:
};

#endif // PADDLE_H
