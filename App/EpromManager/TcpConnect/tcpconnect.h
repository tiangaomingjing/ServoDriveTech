#ifndef TCPCONNECT_H
#define TCPCONNECT_H

#include <QObject>
#include <QTcpSocket>


class TcpConnect : public QObject
{
    Q_OBJECT
public:
    explicit TcpConnect(QByteArray block);
    void connectToServer();
    void stopConnection();

signals:

public slots:
private:
    void closeConnection();
private:
    QTcpSocket tcpSocket;
    quint16 nextBlockSize;
    QByteArray m_block;
private slots:
    void sendRequest();
    void connectionClosedByServer();
    void updateInformation();
    void error();
};

#endif // TCPCONNECT_H
