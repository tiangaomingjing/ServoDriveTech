#include "ivermatching.h"

IVerMatching::IVerMatching(QObject *parent) : QObject(parent)
{
  m_verLinkLists.clear();
}

IVerMatching::~IVerMatching()
{
  m_verLinkLists.clear();
}
bool IVerMatching::check(const VerInfo &verinfo)
{
  if(m_verLinkLists.isEmpty())
    fillVerLinkLists(m_verLinkLists);
  QString matLink=QString("C%1-V%2-F%3-P%4").arg(verinfo.c).arg(verinfo.v).arg(verinfo.f).arg(verinfo.p);
  return m_verLinkLists.contains(matLink);
}

QStringList *IVerMatching::verLinkLists()
{
  if(m_verLinkLists.isEmpty())
    fillVerLinkLists(m_verLinkLists);
  return &m_verLinkLists;
}
