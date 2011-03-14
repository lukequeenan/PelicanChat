#ifndef JOINSERVER_H
#define JOINSERVER_H

#include <QDialog>

namespace Ui {
    class JoinServer;
}

class JoinServer : public QDialog
{
    Q_OBJECT

public:
    explicit JoinServer(QWidget *parent = 0);
    ~JoinServer();

private:
    Ui::JoinServer *ui;
};

#endif // JOINSERVER_H
