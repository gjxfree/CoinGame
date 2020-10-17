#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = nullptr);
    MyCoin(QString btnImg);
    int posX;
    int posY;
    bool flag;
    void changeFlag();
    QTimer *timer1;
    QTimer *timer2;
    int min = 1;
    int max = 8;

    bool isAnimation = false;
    bool isEnable = true;

    void mousePressEvent(QMouseEvent *e);

signals:

};

#endif // MYCOIN_H
