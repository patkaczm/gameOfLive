#include "GameBoard.hpp"

#include <QPainter>
#include <QDateTime>
#include <QMouseEvent>
#include <iostream>

GameBoard::GameBoard(QWidget *parent) : QFrame(parent), isStarted(false) {
    setFrameStyle( QFrame::Box );
    setMaximumSize(QSize(400, 200));
    setMinimumSize(QSize(400, 200));
}

QSize GameBoard::sizeHint() const {
    return QSize(width * 15 + frameWidth() * 2,
                 height * 15 + frameWidth() * 2);
}

QSize GameBoard::minimumSizeHint() const {
    return QSize(width * 15 + frameWidth() * 2,
                 height * 15 + frameWidth() * 2);
}

void GameBoard::paintEvent(QPaintEvent * pe) {
    QFrame::paintEvent( pe );

    QPainter p( this );

    int fw = QFrame::frameSize().width();
    int fh = QFrame::frameSize().height();

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (state[i + 1][j + 1]) {
                p.fillRect(fw / width * i , fh / height * j, fw / width, fh / height, QColor("black"));
            }
        }
    }

}

void GameBoard::randomize() {
    if (isStarted) {
        return;
    }
    qsrand(QDateTime::currentMSecsSinceEpoch() / 1000);
    for (int i = 1; i < width + 1; i++) {
        for (int j = 1; j < height + 1; j++) {
            int s = qrand() % 10;
            state[i][j] = s > 5 ? 1 : 0;
        }
    }
    this->update();
}

void GameBoard::start() {
    if (isStarted) {
        return;
    }
    timer.start(200, this);
    isStarted = true;
}

void GameBoard::timerEvent(QTimerEvent *event) {
    calculateNextFrame();
}

void GameBoard::stop() {
    if (!isStarted) {
        return;
    }
    timer.stop();
    isStarted = false;
}

void GameBoard::calculateNextFrame() {
    //@todo how to keep state better?
    int nextFrame[82][42]{};

    for (int i = 1; i < width + 1; i++) {
        for (int j = 1; j < height + 1; j++) {
            int neighbours = 0;
            for (int k = i - 1; k < i + 2; k++) {
                for (int l = j - 1; l < j + 2; l++) {
                    neighbours += state[k][l];
                }
            }
            neighbours -= state[i][j];
            nextFrame[i][j] = state[i][j];
            if (state[i][j]) {
                if (neighbours  < 2 || neighbours > 3) {
                    nextFrame[i][j] = 0;
                }
            } else {
                if (neighbours == 3) {
                    nextFrame[i][j] = 1;
                }
            }
        }
    }
    int live{}, dead{};

    for (int i = 1; i < width + 1; i++) {
        for (int j = 1; j < height + 1; j++) {
            state[i][j] = nextFrame[i][j];
            state[i][j] ? ++live : ++dead;
        }
    }
    update();
    emit updated(live, dead);
}

void GameBoard::mousePressEvent(QMouseEvent *event) {
    int cellX = event->localPos().x() / 5;
    int cellY = event->localPos().y() / 5;

    std::cout << event->localPos().x() << " " << cellX << "\n"
              << event->localPos().y() << " " << cellY << "\n";

    state[cellX + 1][cellY + 1] = state[cellX + 1][cellY + 1] ? 0 : 1;
    update();
}
