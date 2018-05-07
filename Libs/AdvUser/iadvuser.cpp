#include "iadvuser.h"
#include "iadvuser_p.h"
#include "gtutils.h"
#include "sevdevice.h"

#include <QSettings>
#include <QDebug>

#define ADVUSR_START_INI "advusr.ini"

QString IAdvUserPrivate::m_usrPath = GTUtils::customPath() + "advusr/";

IAdvUserPrivate::IAdvUserPrivate():m_name("iadvuser"),m_isModify(false)
{

}

IAdvUserPrivate:: ~IAdvUserPrivate()
{

}

IAdvUser::IAdvUser(const QString &advUserName, QWidget *parent): QWidget(parent),d_ptr(new IAdvUserPrivate)
{
    d_ptr->q_ptr = this;
    d_ptr->m_name = advUserName;
}

IAdvUser::~IAdvUser()
{
    delete d_ptr;
}

IAdvUser::IAdvUser(const QString &advUserName, IAdvUserPrivate &dd, QWidget *parent):QWidget(parent),d_ptr(&dd)
{
    d_ptr->q_ptr = this;
    d_ptr->m_name = advUserName;
}

bool IAdvUser::isModify()
{
    Q_D(const IAdvUser);
    return d->m_isModify;
}

void IAdvUser::setModify(bool modify)
{
    Q_D(IAdvUser);
    d->m_isModify = modify;
}

void IAdvUser::saveDataToFile(const QString &group, const QString &key, const QVariant &value)
{
    Q_D(const IAdvUser);
    QString path = d->m_usrPath + ADVUSR_START_INI;
    QSettings settings(path, QSettings::IniFormat);
    settings.beginGroup(group);
    settings.setValue(key, value);
    settings.endGroup();
}

QVariant IAdvUser::dataFromFile(const QString &group, const QString &key, const QVariant &defaultValue)
{
    Q_D(const IAdvUser);
    QString path = d->m_usrPath + ADVUSR_START_INI;
    QSettings settings(path,QSettings::IniFormat);
    QVariant vd;
    settings.beginGroup(group);
    vd=settings.value(key,defaultValue);
    settings.endGroup();
    return vd;
}

QString IAdvUser::name()
{
    Q_D(IAdvUser);
    return d->m_name;
}

bool IAdvUser::execute()
{
    Q_D(IAdvUser);
    bool ok=true;
      if(d->m_isModify)
      {
        ok = advUserActive();
        qDebug()<<d->m_name<<"execute";
        if(!ok)
          respondErrorExecute();
        else
          d->m_isModify=false;
      }
      return ok;
}

bool IAdvUser::saveSettings()
{
    writeAdv();
    return true;
}

