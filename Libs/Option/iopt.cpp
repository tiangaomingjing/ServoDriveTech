#include "iopt.h"
#include "iopt_p.h"

#include <QDebug>

IOptPrivate::IOptPrivate():m_name("iopt"),m_isModify(false)
{

}

IOptPrivate:: ~IOptPrivate()
{

}

IOpt::IOpt(const QString &optName, QWidget *parent) : QWidget(parent),d_ptr(new IOptPrivate)
{
  d_ptr->q_ptr=this;
  d_ptr->m_name=optName;
}
IOpt::~IOpt()
{

}

IOpt::IOpt(const QString &optName, IOptPrivate&dd, QWidget *parent):QWidget(parent),d_ptr(&dd)
{
  d_ptr->q_ptr=this;
  d_ptr->m_name=optName;
}

QString IOpt::name() const
{
  Q_D(const IOpt);
  return d->m_name;
}

bool IOpt::isModify() const
{
  Q_D(const IOpt);
  return d->m_isModify;
}
void IOpt::setModify(bool modify)
{
  Q_D(IOpt);
  d->m_isModify=modify;
}
bool IOpt::execute()
{
  Q_D(IOpt);
  bool ok=true;
  if(d->m_isModify)
  {
    ok=optActive();
    qDebug()<<d->m_name<<"execute";
    d->m_isModify=false;
  }
  return ok;
}
