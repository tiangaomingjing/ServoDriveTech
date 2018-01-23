#include "igraphmotor.h"
#include "igraphmotor_p.h"
#include "boxitemmapping.h"

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

IGraphMotor::IGraphMotor(QWidget *parent) : QWidget(parent)
{
  d_ptr->q_ptr=this;
}
IGraphMotor::~IGraphMotor()
{

}

IGraphMotor::IGraphMotor(IGraphMotorPrivate &d, QWidget *parent):QWidget(parent),d_ptr(&d)
{
  d_ptr->q_ptr=this;
}
