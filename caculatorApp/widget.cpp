#include "widget.h"

#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QErrorMessage>

Widget::Widget(QWidget *parent)
    : QWidget(parent), m_isFirst(true)
{

    /*dispplay, button 배치로 ui그리기*/
    /*display 설정*/
    display = new QLabel("0", this); //Label값 0으로 초기화해주고 화면에 띄움
    display->setAlignment(Qt::AlignRight | Qt::AlignVCenter); //계산기 오른쪽 정렬

    display->setStyleSheet("font-size: 24px; background-color: white; border: 1px solid gray;");

    /*버튼과 버튼 grid layout*/
    QGridLayout *buttonLayout = new QGridLayout;

    QString labels[16] = {"7", "8", "9", "/",
                          "4", "5", "6", "x",
                          "1", "2", "3", "-",
                          "0", "C", "=", "+"};

    for (int i = 0; i < 16; ++i) {
        QPushButton *btn = new QPushButton(labels[i], this);
        btn->setFixedSize(50, 50);  // 버튼 크기 조정
        m_buttons.push_back(btn);

        // 4x4 그리드에 배치
        buttonLayout->addWidget(btn, i / WIDTH, i % WIDTH);
    }

    /*display랑 buttonlayout mainlayout위에 올려서 배치*/
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(display);       // mainLayout에 display 올리기
    mainLayout->addLayout(buttonLayout);    // 버튼 레이아웃 올리기
    setLayout(mainLayout);                // mainlayout띄우기

    setMinimumSize(250, 295);
    setMinimumSize(250,295);  //사이즈 고정
    setWindowTitle("Calculator"); //윈도우 타이틀바 생성
    /*---ui 그리기 끝---*/

    //connect로 연결
    for (int i=0; i<m_buttons.size(); i++){
        QString text = m_buttons[i]->text(); //
        if(text.length()==1 && text.at(0).isDigit())
            connect (m_buttons[i], &QPushButton::clicked, this, &Widget::setNum);
        else connect (m_buttons[i], &QPushButton::clicked, this, &Widget::setOp);
    }
}

Widget::~Widget() { //소멸자
    delete display;
    m_buttons.clear();
}

void Widget::setNum() //숫자 입력받는 함수
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    QString digit = btn->text();  // 눌린 버튼의 숫자 가져오기

    if (m_isFirst || display->text() == "0") {
        display->setText(digit);  // 처음이면 숫자만 입력
        m_isFirst = false; //m_isFirst를 false로 바꿔줌

    } else {
        display->setText(display->text() + digit);  // 이어붙이기
    }
}


void Widget::setOp()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    QString op = btn->text();

    if (op == "C") { //초기화
        display->setText("0");
        m_num1.clear();
        m_op.clear();
        m_isFirst = true;
    }
    else if (op == "=") { //눌리면 계산 수행
        if (m_num1.isEmpty() || m_op.isEmpty())
            return;

        QString num2 = display->text();
        double a = m_num1.toDouble();
        double b = num2.toDouble();
        double result = 0;

        if (m_op == "+") result = a + b;
        else if (m_op == "-") result = a - b;
        else if (m_op == "x") result = a * b;
        else if (m_op == "/") {
            if (b==0) showErrorMessage();
            else result =  a / b ;
        }
        display->setText(QString::number(result)); //숫자를 QString으로 변경
        m_num1.clear();
        m_op.clear();
        m_isFirst = true;
    }
    else { // C, = 제외하고 나머지니까 연산자 눌렸을 때
        m_num1 = display->text(); // 현재 화면 값 저장
        m_op = op;                // 연산자 저장
        m_isFirst = true;         // true로 바꿔서 새롭게 숫자 입력받아야함
    }

}

void Widget::showErrorMessage(){
    QErrorMessage *divZeroError = new QErrorMessage(this);
    divZeroError->showMessage("can't divide zero");
    divZeroError->exec();
}


