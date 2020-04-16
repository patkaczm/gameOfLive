#pragma once

#include <QMainWindow>
#include <QLabel>

#include "GameWindow.hpp"

class MainWindow: public QMainWindow {
    Q_OBJECT
public:
    MainWindow();

private:
    GameWindow* gw;
};

