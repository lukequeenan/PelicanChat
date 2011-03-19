#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStatusBar>
#include <QThread>

#include "joinserver.h"
#include "ui_joinserver.h"

#define BUFFER_LENGTH 160
#define JOIN_MESSAGE 1
#define TEXT_MESSAGE 2
#define REQUEST_LIST_MESSAGE 3

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QThread myThread;

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual void run();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    JoinServer joinServer_;
    QLabel *statusBarText_;

    // Connection data members
    int serverPort_;
    bool append_info_;
    QString serverIp_;
    QString myName_;
    QString message_;
    int mySocket_;

    // Private functions
    void setStatusBarText(const QString text);
    bool initializeConnectionToServer();
    void writeFile(const char* data);

private slots:
    void on_action_Record_to_File_toggled(bool );
    void on_action_Leave_Server_triggered();
    void on_action_Join_Server_triggered();
    void on_pushButtonSend_clicked();
    void on_sendBox_textChanged();
};

#endif // MAINWINDOW_H
