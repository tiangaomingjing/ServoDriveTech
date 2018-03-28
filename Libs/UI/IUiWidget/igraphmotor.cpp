#include "igraphmotor.h"
#include "igraphmotor_p.h"
#include "boxitemmapping.h"

#include <QDebug>

//IGraphMotor::IGraphMotor(QWidget *parent) : IGraph(*(new IGraphMotorPrivate),parent)
//{

//}
IGraphMotor::~IGraphMotor()
{
  qDebug()<<"IGraphMotor destruct-->";
}

IGraphMotor::IGraphMotor(IGraphMotorPrivate &dd, QWidget *parent):IGraph(dd,parent)
{

}
