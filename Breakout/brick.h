#ifndef BRICK_H
#define BRICK_H

#include <QWidget>
// #include <QLabel>
class Brick : public QWidget
{
    Q_OBJECT
public:
    Brick(QWidget *parent = nullptr);
private:
    void paintEvent(QPaintEvent*) override;
//signals:
};

#endif // BRICK_H
