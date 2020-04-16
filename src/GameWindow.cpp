#include "GameWindow.hpp"

#include <QGridLayout>

GameWindow::GameWindow(QWidget *parent) : QWidget(parent) {
    board = new GameBoard(this);

    QGridLayout *layout = new QGridLayout;

    startButton = new QPushButton(tr("Start"));
    startButton->setFocusPolicy(Qt::NoFocus);

    stopButton = new QPushButton(tr("Stop"));
    stopButton->setFocusPolicy(Qt::NoFocus);

    randomizeButton = new QPushButton(tr("Randomize"));
    randomizeButton->setFocusPolicy(Qt::NoFocus);

    liveCounter = new QLCDNumber(5);
    liveCounter->setSegmentStyle(QLCDNumber::Filled);

    deadCounter = new QLCDNumber(5);
    deadCounter->setSegmentStyle(QLCDNumber::Filled);

    layout->addWidget(createLabel("GameBoard"), 0, 0, 1, 4);
    layout->addWidget(board, 1, 0, 4, 4);
    layout->addWidget(startButton, 5, 0);
    layout->addWidget(stopButton, 6, 0);
    layout->addWidget(randomizeButton, 5, 1);

    layout->addWidget(createLabel("Live"), 1, 5);
    layout->addWidget(liveCounter, 2, 5);
    layout->addWidget(createLabel("Dead"), 3, 5);
    layout->addWidget(deadCounter, 4, 5);

    layout->setSizeConstraint(QLayout::SetFixedSize);

    setLayout(layout);

    connect(randomizeButton, &QPushButton::clicked, board, &GameBoard::randomize);
    connect(startButton, &QPushButton::clicked, board, &GameBoard::start);
    connect(stopButton, &QPushButton::clicked, board, &GameBoard::stop);
    connect(board, &GameBoard::updated, this, &GameWindow::updateLCD);
}

QLabel *GameWindow::createLabel(const QString &text) {
    auto label = new QLabel(text, this);
    label->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    return label;
}

void GameWindow::updateLCD(int live, int dead) {
    liveCounter->display(live);
    deadCounter->display(dead);
}
