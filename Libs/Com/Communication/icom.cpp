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

ICom::ICom(IComPrivate &dd):d_ptr(&dd)
{
  d_ptr->q_ptr=this;
}


