#include "icom.h"
#include "icom_p.h"
#include "ServoDriverComDll.h"

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

errcode_t ICom::open(void (*processCallBack)(void *, short *), void *parameter)
{
    Q_D(const ICom);
    int16_t ret=GTSD_CMD_Open(processCallBack,parameter,d->m_comType);
    return ret;
}

errcode_t ICom::close()
{
    Q_D(const ICom);

    int16_t ret=GTSD_CMD_Close(d->m_comType);
    return ret;
}

NetCardInfo ICom::getNetCardInformation()
{
    NetCardInfo carInf;
    carInf=NetCardInfo(GTSD_CMD_GetNetCardMsg());
    return carInf;
}

errcode_t ICom::enableCRC(bool enable)
{
    //mode :1 force to on
    //mode: 2 force to off
    if(enable)
      GTSD_CMD_FroceCheckMode(1);
    else
      GTSD_CMD_FroceCheckMode(2);
    return 0;
}

ICom::ICom(IComPrivate &dd):d_ptr(&dd)
{
  d_ptr->q_ptr=this;
}


