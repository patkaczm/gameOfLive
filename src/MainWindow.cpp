#include "MainWindow.hpp"

#include <QtWidgets>

MainWindow::MainWindow() {
    gw = new GameWindow(this);
    setCentralWidget(gw);
    setFixedSize(minimumSize());
}