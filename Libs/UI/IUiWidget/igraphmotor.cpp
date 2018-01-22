#include "igraphmotor.h"
#include "igraphmotor_p.h"
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
