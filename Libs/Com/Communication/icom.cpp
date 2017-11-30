#include "icom.h"
#include "icom_p.h"

COM_USE_NAMESPACE

//private class
IComPrivate::IComPrivate()
{

}
IComPrivate::~IComPrivate()
{

}

ICom::ICom(const string &objectName):d_ptr(new IComPrivate())
{
  Q_D(ICom);
  d->q_ptr=this;
  d->m_objectName=objectName;
  d->m_comType=ICOM_TYPE_PCDEBUG;

}
ICom::~ICom()
{
  delete d_ptr;
}

string ICom::iComObjectName(void) const
{
  Q_D(const ICom);
  return d->m_objectName;
}

IComType ICom::iComType(void) const
{
  Q_D(const ICom);
  return d->m_comType;
}

ICom::ICom(IComPrivate &d):d_ptr(&d)
{
  d_ptr->q_ptr=this;
}


