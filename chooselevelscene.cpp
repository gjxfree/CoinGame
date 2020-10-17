#include "chooselevelscene.h"
#include <QPainter>
#include <QMenuBar>
#include "mypushbutton.h"
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include <QSound>

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    //设置固定大小
    this->setFixedSize(320,588);
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));   //设定图标
    this->setWindowTitle("翻金币主场景");
    QSound * sound = new QSound(":/res/TapButtonSound.wav",this);

    QMenuBar *bar = menuBar();
    setMenuBar(bar);
    QMenu * startMenu = bar->addMenu("开始");
    QAction * quitAction = startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,this,&QWidget::close);


    MyPushButton * btn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    btn->setParent(this);
    btn->move(this->width()-btn->width(),this->height()-btn->height());

    connect(btn,&MyPushButton::clicked,this,[=](){
        sound->play(":/res/BackButtonSound.wav");
        QTimer::singleShot(500,this,[=](){
           emit this->chooseSceneBack();
        });

    });


    //创建选择关卡的按钮
    for(int i = 0;i < 20;i++){
        MyPushButton * menuBtn = new MyPushButton(":/res/LevelIcon.png");
        QLabel * label = new QLabel;
        menuBtn->setParent(this);

        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setAlignment(Qt::AlignCenter);
        menuBtn->move(25+ i%4 * 70, 130 + i/4 * 70);
        label->move(25+ i%4 * 70, 130 + i/4 * 70);
        label->setText(QString::number(1+i));

        connect(menuBtn,&MyPushButton::clicked,this,[=](){
            if(playScene == nullptr){
                sound->play();
                playScene = new PlayScene(i+1);
                connect(playScene,&PlayScene::playSceneBack,this,[=](){
                    qDebug()<<"0k";
                    this->setGeometry(playScene->geometry());
                    this->show();
                    delete playScene;
                    playScene = nullptr;
                });
                playScene->setGeometry(this->geometry());
                this->hide();
                playScene->show();

            }
            QString str =QString("选择的是：%1").arg(i+1);
            qDebug() << str;
        });
        //设置鼠标穿透事件
        label->setAttribute(Qt::WA_TransparentForMouseEvents);


    }

}

void ChooseLevelScene::paintEvent(QPaintEvent *){
    //设置背景
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);
}
