#include "mycoin.h"
#include <QDebug>

MyCoin::MyCoin(QString btnImg){
    QPixmap pix;
    if(!pix.load(btnImg)){
        QString str = QString("图片 %1 加载失败").arg(btnImg);
        qDebug() << str;
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    connect(timer1,&QTimer::timeout,this,[=](){
       QPixmap pix;
       QString str = QString(":/res/Coin000%1.png").arg(this->min++);
       pix.load(str);

       this->setFixedSize(pix.width(),pix.height());
       this->setStyleSheet("QPushButton{border:0px}");
       this->setIcon(pix);
       this->setIconSize(QSize(pix.width(),pix.height()));
       if(this->min>this->max){
           this->min = 1;
           timer1->stop();
           this->isAnimation = false;
       }
    });

    connect(timer2,&QTimer::timeout,this,[=](){
       QPixmap pix;
       QString str = QString(":/res/Coin000%1.png").arg(this->max--);
       pix.load(str);

       this->setFixedSize(pix.width(),pix.height());
       this->setStyleSheet("QPushButton{border:0px}");
       this->setIcon(pix);
       this->setIconSize(QSize(pix.width(),pix.height()));
       if(this->min>this->max){
           this->max = 8;
           timer2->stop();
           this->isAnimation = false;
       }
    });


}


void MyCoin::changeFlag(){
    if(this->flag){
        timer1->start(30);
        this->flag = false;
    }else{
        timer2->start(30);
        this->flag = true;
    }
    this->isAnimation = true;
}


void MyCoin::mousePressEvent(QMouseEvent *e){
    if(this->isAnimation||!(this->isEnable)){
        return;
    }else {
        QPushButton::mousePressEvent(e);
    }
}


