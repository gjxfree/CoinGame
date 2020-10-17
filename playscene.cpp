#include "playscene.h"
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include "mycoin.h"
#include "dataconfig.h"
#include <QPropertyAnimation>
#include <QSound>


PlayScene::PlayScene(int index){
    this->setWindowTitle("翻金币");
    this->levelIndex = index;
    this->setFixedSize(320,588);    //设置固定大小
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));   //设定图标

    QSound * sound = new QSound("",this);

    QMenuBar * bar = this->menuBar();
    this->setMenuBar(bar);
    QMenu * startMenu = bar->addMenu("开始");
    QAction * quitAction = startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,this,&QWidget::close);


    MyPushButton * btn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    btn->setParent(this);
    btn->move(this->width()-btn->width(),this->height()-btn->height());

    connect(btn,&MyPushButton::clicked,this,[=](){
        sound->play(":/res/BackButtonSound.wav");
        QTimer::singleShot(500,this,[=](){
            emit this->playSceneBack();
        });

    });

    QLabel * label = new QLabel();
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    QString str = QString("Level: %1").arg(this->levelIndex);
    label->setFont(font);
    label->setParent(this);
    label->setText(str);
    label->setGeometry(30,this->height()-50,120,50);

    dataConfig data;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->arr[i][j] = data.mData[this->levelIndex][i][j];
        }
    }

    QLabel * success = new QLabel();
    QPixmap pix;
    pix.load(":/res/LevelCompletedDialogBg.png");
    success->setGeometry(0,0,pix.width(),pix.height());
    success->setPixmap(pix);
    success->setParent(this);
    success->move((this->width()-pix.width())*0.5,-pix.height());



    //显示金币背景图案
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            QPixmap pix;
            pix.load(":/res/BoardNode.png");
            QLabel * label = new QLabel();
            label->setParent(this);
            label->setPixmap(pix);
            label->setFixedSize(pix.width(),pix.height());
            label->move(57 + i*50,200+j*50);

            //判断金币和银币的位置
            QString str;
            if(this->arr[i][j])
                str = ":/res/Coin0001.png";
            else
                str = ":/res/Coin0008.png";

            MyCoin * coin = new MyCoin(str);
            coin->setParent(this);
            coin->move(59+i*50,204+j*50);
            coin->posX = i;
            coin->posY = j;
            coin->flag = this->arr[i][j];

            mycoin[i][j] = coin;

            connect(coin,&MyCoin::clicked,this,[=](){
                sound->play(":/res/ConFlipSound.wav");
                coin->changeFlag();
                this->arr[i][j] = !this->arr[i][j];
                QTimer::singleShot(300,this,[=](){
                    if(coin->posX+1 <=3)
                    {
                        mycoin[coin->posX+1][coin->posY]->changeFlag();
                        arr[coin->posX+1][coin->posY] = arr[coin->posX+1][coin->posY]== 0 ? 1 : 0;
                    }
                    if(coin->posX-1>=0)
                    {
                        mycoin[coin->posX-1][coin->posY]->changeFlag();
                        arr[coin->posX-1][coin->posY] = arr[coin->posX-1][coin->posY]== 0 ? 1 : 0;
                    }
                    if(coin->posY+1<=3)
                    {
                        mycoin[coin->posX][coin->posY+1]->changeFlag();
                        arr[coin->posX][coin->posY+1] = arr[coin->posX+1][coin->posY]== 0 ? 1 : 0;
                    }
                    if(coin->posY-1>=0)
                    {
                        mycoin[coin->posX][coin->posY-1]->changeFlag();
                        arr[coin->posX][coin->posY-1] = arr[coin->posX+1][coin->posY]== 0 ? 1 : 0;
                    }
                    int goldenCoin = 0;
                    for (int i = 0; i < 16;i++ ) {
                        if(!mycoin[i/4][i%4]->flag)break;
                        goldenCoin++;
                    }
                    if(goldenCoin == 16){
                        qDebug() << "win";
                        sound->play(":/res/LevelWinSound.wav");
                        for (int i = 0; i < 16;i++ ) {
                            mycoin[i/4][i%4]->isEnable = false;

                            QPropertyAnimation *animation = new QPropertyAnimation(success,"geometry");
                            animation->setDuration(1000);
                            animation->setStartValue(QRect(success->x(),success->y(),success->width(),success->height()));
                            animation->setEndValue(QRect(success->x(),success->y()+175,success->width(),success->height()));
                            animation->setEasingCurve(QEasingCurve::OutBounce);
                            animation->start();


                        }
                    }



                });
            });

        }
    }




}

void PlayScene::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //画上图标
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);
}
