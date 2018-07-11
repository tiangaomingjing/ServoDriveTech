#include "messageserver.h"
#include "clientsocket.h"

MessageServer::MessageServer(QObject *parent) : QTcpServer(parent)
{

}

MessageServer::~MessageServer() {
    qDebug()<<"Also Released!";
}

void MessageServer::incomingConnection(int socketID) {
    qDebug()<<"incoming connection";
    m_socket = new ClientSocket;
    connect(m_socket, SIGNAL(receiveStartMsg()), this, SIGNAL(getStartMsg()));
    connect(m_socket, SIGNAL(receiveCloseMsg()), this, SIGNAL(getCloseMsg()));
    m_socket->setSocketDescriptor(socketID);
}

void MessageServer::replyMsg(QByteArray block) {
    m_socket->replyMessage(block);
}
