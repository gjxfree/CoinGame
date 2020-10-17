#include "mainsence.h"
#include "ui_mainsence.h"
#include <QPainter>
#include <mypushbutton.h>
#include <QDebug>
#include <QTimer>
#include <QSound>

MainSence::MainSence(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainSence)
{
    ui->setupUi(this);

    this->setFixedSize(320,588);    //设置固定大小
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));   //设定图标
    this->setWindowTitle("翻金币主场景");

    //点击退出，关闭程序
    connect(ui->actionQuit,&QAction::triggered,this,&QWidget::close);

    //开始按钮
    MyPushButton *startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move((this->width()-startBtn->width())*0.5,this->height()*0.7);

    QSound * sound = new QSound(":/res/TapButtonSound.wav",this);


    connect(cls,&ChooseLevelScene::chooseSceneBack,this,[=](){
        this->setGeometry(cls->geometry());
        cls->hide();
        this->show();
    });
    connect(startBtn,&MyPushButton::clicked,[=](){
       qDebug() << "点击了开始" << Qt::endl;
       sound->play();
       startBtn->zoom1();
       startBtn->zoom2();
       QTimer::singleShot(500,this,[=](){

           cls->setGeometry(this->geometry());
           this->hide();
           cls->show();

       });
    });



}

void MainSence::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/MenuSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);


}











MainSence::~MainSence()
{
    delete ui;
}

