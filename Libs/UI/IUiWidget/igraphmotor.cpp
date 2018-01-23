#include "igraphmotor.h"
#include "igraphmotor_p.h"
#include "boxitemmapping.h"

#include <QDebug>

IGraphMotorPrivate::IGraphMotorPrivate()
{

}
IGraphMotorPrivate::~IGraphMotorPrivate()
{

}

IGraphMotor::IGraphMotor(QWidget *parent) : IGraph(*(new IGraphMotorPrivate),parent)
{

}
IGraphMotor::~IGraphMotor()
{
  qDebug()<<"IGraphMotor destruct-->";
}

IGraphMotor::IGraphMotor(IGraphMotorPrivate &d, QWidget *parent):IGraph(d,parent)
{

}
