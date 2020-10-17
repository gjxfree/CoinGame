#ifndef MAINSENCE_H
#define MAINSENCE_H

#include <QMainWindow>
#include "chooselevelscene.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainSence; }
QT_END_NAMESPACE

class MainSence : public QMainWindow
{
    Q_OBJECT

public:
    MainSence(QWidget *parent = nullptr);
    ~MainSence();

    //重写paintEvent事件
    void paintEvent(QPaintEvent *);

    ChooseLevelScene * cls = new ChooseLevelScene();


private:
    Ui::MainSence *ui;
};
#endif // MAINSENCE_H
