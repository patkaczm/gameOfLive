#pragma once

#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QLCDNumber>

#include "GameBoard.hpp"

class GameWindow : public QWidget {
    Q_OBJECT
public:
    GameWindow(QWidget *parent);

private slots:
    void updateLCD(int live, int dead);

private:
    QLabel *createLabel(const QString &text);


    GameBoard* board;
    QPushButton* startButton;
    QPushButton* stopButton;
    QPushButton* randomizeButton;
    QLCDNumber *liveCounter;
    QLCDNumber *deadCounter;
};

