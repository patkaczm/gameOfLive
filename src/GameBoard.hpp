#pragma once

#include <QFrame>
#include <QBasicTimer>

class GameBoard: public QFrame {
    Q_OBJECT
public:
    GameBoard(QWidget *parent);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    void randomize();

signals:
    void updated(int live, int dead);

public slots:
    void start();
    void stop();

protected:
    void paintEvent(QPaintEvent*);
    void timerEvent(QTimerEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    void calculateNextFrame();

    enum {width=80, height=40};
    int state[82][42]{};
    QBasicTimer timer;
    bool isStarted;
};
