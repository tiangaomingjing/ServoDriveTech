#include "igraphmotor.h"
#include "igraphmotor_p.h"
#include "boxitemmapping.h"

#include <QDebug>

IGraphMotorPrivate::IGraphMotorPrivate():
  m_dev(NULL),
  m_treeWidget(NULL),
  m_mapping(new BoxItemMapping)
{

}
IGraphMotorPrivate::~IGraphMotorPrivate()
{
   delete m_mapping;
}

IGraphMotor::IGraphMotor(QWidget *parent) : QWidget(parent),
  d_ptr(new IGraphMotorPrivate)
{
  d_ptr->q_ptr=this;
}
IGraphMotor::~IGraphMotor()
{
  qDebug()<<"IGraphMotor destruct-->";
  delete d_ptr;
}

IGraphMotor::IGraphMotor(IGraphMotorPrivate &d, QWidget *parent):QWidget(parent),d_ptr(&d)
{
  d_ptr->q_ptr=this;
}
