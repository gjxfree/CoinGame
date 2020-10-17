#include "mypushbutton.h"
#include <QDebug>
#include <QPropertyAnimation>
MyPushButton::MyPushButton(QString normalImg, QString pressImg){
    this->normalImg = normalImg;
    this->pressImg = pressImg;

    QPixmap pix;
    bool ret = pix.load(normalImg);
    if(!ret){
        qDebug() << "图片加载失败" << Qt::endl;
        return;
    }
    //设置图片固定大小
    this->setFixedSize( pix.width(),pix.height());

    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px}");

    //设置图标
    this->setIcon(pix);

    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));

}

void MyPushButton::zoom1(){
    //创建动画对象
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    //设置动画的时间间隔
    animation->setDuration(200);

    //起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //结束位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //设置动画缓和曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //开始执行动画
    animation->start();

}

void MyPushButton::zoom2(){
    //创建动画对象
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    //设置动画的时间间隔
    animation->setDuration(200);

    //起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置动画缓和曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //开始执行动画
    animation->start();
}

void MyPushButton::mousePressEvent(QMouseEvent *e){
    if(this->pressImg !=""){
        QPixmap pix;
        bool ret = pix.load(this->pressImg);
        if(!ret){
            qDebug() << "图片加载失败" << Qt::endl;
            return;
        }
        //设置图片固定大小
        this->setFixedSize( pix.width(),pix.height());

        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px}");

        //设置图标
        this->setIcon(pix);

        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }

    return QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e){
    if(this->pressImg !=""){
        QPixmap pix;
        bool ret = pix.load(this->normalImg);
        if(!ret){
            qDebug() << "图片加载失败" << Qt::endl;
            return;
        }
        //设置图片固定大小
        this->setFixedSize( pix.width(),pix.height());

        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px}");

        //设置图标
        this->setIcon(pix);

        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    return QPushButton::mouseReleaseEvent(e);
}



