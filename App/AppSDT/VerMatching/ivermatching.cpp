#include "ivermatching.h"

IVerMatching::IVerMatching(QObject *parent) : QObject(parent)
{
  m_verLinkLists.clear();
}

IVerMatching::~IVerMatching()
{
  m_verLinkLists.clear();
}
IVerMatching::CheckStatus IVerMatching::check(const VerInfo &verinfo)
{
  CheckStatus sta=CHECK_STA_OK;
  bool hasLink=true;
  if(m_verLinkLists.isEmpty())
    fillVerLinkLists(m_verLinkLists);
  QString matLink=QString("C%1-V%2-F%3-P%4").arg(verinfo.c).arg(verinfo.v).arg(verinfo.f).arg(verinfo.p);
  hasLink=m_verLinkLists.contains(matLink);
  if(!hasLink)
  {
    if(hasComponent(verinfo))
      sta=CHECK_STA_NSUPPORT;
    else
      sta=CHECK_STA_SOFT_OLD;
  }
  return sta;
}

QStringList *IVerMatching::verLinkLists()
{
  if(m_verLinkLists.isEmpty())
    fillVerLinkLists(m_verLinkLists);
  return &m_verLinkLists;
}
