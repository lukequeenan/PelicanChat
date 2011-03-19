#ifndef LISTENTHREAD_H
#define LISTENTHREAD_H

#include <QThread>

#define BUFFER_LENGTH 160
#define JOIN_MESSAGE 1
#define TEXT_MESSAGE 2
#define REQUEST_LIST_MESSAGE 3

class ListenThread : public QThread
{
    Q_OBJECT
public:
    void run();
    void setSocket(int *socket);

signals:
    void textMessageReceived(QString data);

private:
    int *mySocket_;
};
#endif // LISTENTHREAD_H
