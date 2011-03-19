#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStatusBar>
#include <QThread>

#include "joinserver.h"
#include "ui_joinserver.h"
#include "listenthread.h"

#define BUFFER_LENGTH 160
#define NAME_LENGTH 15
#define JOIN_MESSAGE 1
#define TEXT_MESSAGE 2
#define REQUEST_LIST_MESSAGE 3

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void dataReceived(QString data);

private:
    Ui::MainWindow *ui;
    JoinServer joinServer_;
    QLabel *statusBarText_;

    // Connection data members
    int serverPort_;
    bool append_info_;
    bool isConnected_;
    QString serverIp_;
    QString myName_;
    QString message_;
    int mySocket_;
    ListenThread listenThread_;

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
