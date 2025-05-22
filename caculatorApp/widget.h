#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <Vector>

class QLabel;
class QPushButton;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    QLabel *display; //화면
    QVector <QPushButton*> m_buttons; //Vector 사용
    QString m_num1, m_op; //두번째 값은 QLabel객체에 나와있음
    bool m_isFirst; //버튼 처음 눌렸을 때 체크하는 것
    const qint32 WIDTH = 4; //버튼 4*4 16으로 구성할 것임

public slots:
    void setNum(); //숫자 설정하는 함수
    void setOp(); //연산자 설정하는 함수
    void showErrorMessage(); //에러메세지 보여주기

};


#endif // WIDGET_H
