#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "mycoin.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:

    PlayScene(int index);
    int levelIndex;
    //重写paintEvent事件
    void paintEvent(QPaintEvent *);

    int arr[4][4];
    MyCoin * mycoin[4][4];

signals:
    void playSceneBack();

};

#endif // PLAYSCENE_H
