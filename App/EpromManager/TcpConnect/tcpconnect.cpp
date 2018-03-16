#include "tcpconnect.h"
#include <QDataStream>
#include <QFile>
#include <QHostAddress>

TcpConnect::TcpConnect()
{
    //connect(&tcpSocket, SIGNAL(connected()), this, SLOT(sendRequest()));
    connect(&tcpSocket, SIGNAL(disconnected()), this, SLOT(connectionClosedByServer()));
    connect(&tcpSocket, SIGNAL(readyRead()), this, SLOT(updateInformation()));
    connect(&tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error()));
    //m_block = block;
}

void TcpConnect::connectToServer() {
    tcpSocket.connectToHost(QHostAddress::LocalHost, 6178);
    nextBlockSize = 0;
}

void TcpConnect::sendRequest(QByteArray block) {
    qDebug()<<"send request";
    tcpSocket.write(block);
}

void TcpConnect::updateInformation() {
    qDebug()<<"update";
    QDataStream in(&tcpSocket);
    in.setVersion(QDataStream::Qt_5_5);
    if (nextBlockSize == 0) {
        if(tcpSocket.bytesAvailable() < sizeof(quint16)) {
                return;
        }
        in >> nextBlockSize;
    }
    if (tcpSocket.bytesAvailable() < nextBlockSize) {
        return;
    }

    QString typeName;
    QString modeName;
    QString comType;
    QString dspNum;
    in >> modeName>>typeName>>comType>>dspNum;
    qDebug()<<"mode"<<modeName;
    qDebug()<<"type"<<typeName;
    qDebug()<<"com"<<comType;
    QStringList list;
    list<<modeName<<typeName<<comType<<dspNum;
    nextBlockSize = 0;
    emit receiveConfig(list);
}

void TcpConnect::connectionClosedByServer() {
    tcpSocket.close();
}

void TcpConnect::stopConnection() {
    tcpSocket.close();
}

void TcpConnect::error() {
    tcpSocket.close();
}

