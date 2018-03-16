#ifndef MESSAGESERVER_H
#define MESSAGESERVER_H

#include <QObject>
#include <QTcpServer>

class ClientSocket;

class MessageServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MessageServer(QObject *parent = 0);
    ~MessageServer();

    void replyMsg(QByteArray block);

signals:
    void getStartMsg();
    void getCloseMsg();
public slots:

private:
    void incomingConnection(int socketID);
private:
    ClientSocket *m_socket;
};

#endif // MESSAGESERVER_H
