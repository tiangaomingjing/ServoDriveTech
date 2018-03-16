#include "clientsocket.h"
#include <QDataStream>
#include <QDebug>

ClientSocket::ClientSocket(QObject *parent) : QTcpSocket(parent)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(readClient()));
    connect(this, SIGNAL(disconnected()), this, SLOT(deleteLater()));
    nextBlockSize = 0;
}

ClientSocket::~ClientSocket() {
    qDebug()<<"Released!";
}

void ClientSocket::readClient() {
    qDebug()<<"read client";
    QDataStream in(this);
    in.setVersion(QDataStream::Qt_5_5);
    if (nextBlockSize == 0) {
        if(bytesAvailable() < sizeof(quint16)) {
            return;
        }
        in >> nextBlockSize;
    }
    if (bytesAvailable() < nextBlockSize) {
        return;
    }
    QString msg;
    in >> msg;
    if (msg.compare("Start") == 0) {
        qDebug()<<"Receive start";
        emit receiveStartMsg();
    } else if (msg.compare("Close") == 0) {
        qDebug()<<"Receive close";
        emit receiveCloseMsg();
    }
    //emit sendDataToServer(list);
//    replyMessage();
//    QDataStream out(this);
//    out<<quint16(0xFFFF);
//    close();
}

//void ClientSocket::sendClose() {
//    replyMessage();
//    QDataStream out(this);
//    out<<quint16(0xFFFF);
//    close();
//}

void ClientSocket::replyMessage(QByteArray block) {
    qDebug()<<"wirte message";
    write(block);
}
