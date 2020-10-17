#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushButton(QPushButton *parent = nullptr);

    //构造函数 参数1 正常显示图片 参数2 按下后显示图片
    MyPushButton(QString normalImg,QString pressImg = "");
    QString normalImg;
    QString pressImg;

    //弹跳特效
    void zoom1();   //向下跳
    void zoom2();   //向上跳
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
signals:

};

#endif // MYPUSHBUTTON_H
