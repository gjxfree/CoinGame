#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include "playscene.h"

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);

    //重写paintEvent事件
    void paintEvent(QPaintEvent *);
    PlayScene * playScene = nullptr;

signals:
    //自定义的信号告诉主场景，点击返回
    void chooseSceneBack();

};

#endif // CHOOSELEVELSCENE_H
