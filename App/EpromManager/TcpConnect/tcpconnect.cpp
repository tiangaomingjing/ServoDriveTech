#include "tcpconnect.h"
#include "globaldefine.h"
#include <QDataStream>
#include <QFile>

TcpConnect::TcpConnect(QByteArray block)
{
    connect(&tcpSocket, SIGNAL(connected()), this, SLOT(sendRequest()));
    connect(&tcpSocket, SIGNAL(disconnected()), this, SLOT(connectionClosedByServer()));
    connect(&tcpSocket, SIGNAL(readyRead()), this, SLOT(updateInformation()));
    connect(&tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error()));
    m_block = block;
}

void TcpConnect::connectToServer() {
    QString filePath = RESOURCE_FILE_PATH + "IPAddress.txt";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Fail";
        return;
    }
    QTextStream in(&file);
    QString line = "";
    QString portStr = "";
    while (!in.atEnd())
    {
        line = in.readLine();
        portStr = in.readLine();
    }
    file.close();
    qDebug()<<line;
    qDebug()<<portStr;
    quint16 port = portStr.toUShort();
    tcpSocket.connectToHost(line, port);
    nextBlockSize = 0;
}

void TcpConnect::updateInformation() {
    QDataStream in(&tcpSocket);

    forever {
        if (nextBlockSize == 0) {
            if (tcpSocket.bytesAvailable() < sizeof(quint16)) {
                break;
            }
            in>>nextBlockSize;
        }

        if (nextBlockSize == 0xFFFF) {
            closeConnection();
            break;
        }

        if (tcpSocket.bytesAvailable() < nextBlockSize) {
            break;
        }
        QString str;
        in >> str;
        qDebug()<<str;
        nextBlockSize = 0;
    }
}

void TcpConnect::stopConnection() {
    closeConnection();
}

void TcpConnect::connectionClosedByServer() {
    closeConnection();
}

void TcpConnect::error() {
    closeConnection();
}

void TcpConnect::closeConnection() {
    tcpSocket.close();
}

void TcpConnect::sendRequest() {
    tcpSocket.write(m_block);
}

