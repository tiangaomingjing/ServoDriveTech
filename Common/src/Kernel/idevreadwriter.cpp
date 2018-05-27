#include "idevreadwriter.h"
#include "gtutils.h"
#include "qttreemanager.h"

IDevReadWriter::IDevReadWriter(QObject *parent):QObject(parent)
{
  m_comTypeNameMap.insert(0,QString("PcDebug"));
  m_comTypeNameMap.insert(1,QString("RnNet"));
  m_comTypeNameMap.insert(2,QString("TcP/Ip"));
  m_comTypeNameMap.insert(3,QString("Offline"));
}

