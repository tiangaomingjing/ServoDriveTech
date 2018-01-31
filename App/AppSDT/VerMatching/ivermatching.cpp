#include "ivermatching.h"

IVerMatching::IVerMatching(QObject *parent) : QObject(parent)
{
  m_verLinkLists.clear();
}

IVerMatching::~IVerMatching()
{
  m_verLinkLists.clear();
}
bool IVerMatching::check(quint32 p, quint32 c, quint32 v, quint32 f)
{
  if(m_verLinkLists.isEmpty())
    fillVerLinkLists(m_verLinkLists);
  QString matLink=QString("P%1-C%2-V%3-F%4").arg(p).arg(c).arg(v).arg(f);
  return m_verLinkLists.contains(matLink);
}

QStringList *IVerMatching::verLinkLists()
{
  if(m_verLinkLists.isEmpty())
    fillVerLinkLists(m_verLinkLists);
  return &m_verLinkLists;
}
