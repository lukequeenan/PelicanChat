#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStatusBar>

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
    QLabel *statusBarText_;

    // Connection information
    int mySocket_;

    void setStatusBarText(const QString text);

private slots:
    void on_action_Record_to_File_toggled(bool );
    void on_action_Leave_Server_triggered();
    void on_action_Join_Server_triggered();
};

#endif // MAINWINDOW_H
