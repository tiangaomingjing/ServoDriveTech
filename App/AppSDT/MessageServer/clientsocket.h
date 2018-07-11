#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QObject>
#include <QTcpSocket>

class ClientSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit ClientSocket(QObject *parent = 0);
    ~ClientSocket();

    void replyMessage(QByteArray block);

signals:
    void receiveStartMsg();
    void receiveCloseMsg();
public slots:
private:
    quint16 nextBlockSize;
private:

private slots:
    void readClient();
};

#endif // CLIENTSOCKET_H
