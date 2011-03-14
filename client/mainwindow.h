#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "joinserver.h"
#include "ui_joinserver.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    JoinServer joinServer_;

private slots:
    void on_action_Leave_Server_triggered();
    void on_action_Join_Server_triggered();
};

#endif // MAINWINDOW_H
