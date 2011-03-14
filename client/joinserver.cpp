#include "joinserver.h"
#include "ui_joinserver.h"

JoinServer::JoinServer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JoinServer)
{
    ui->setupUi(this);
}

JoinServer::~JoinServer()
{
    delete ui;
}
