#include "graphvelocity129.h"
#include "ui_graphvelocity129.h"
#include "igraphvelocity_p.h"
#include <QDebug>

class GraphVelocity129Private:public IGraphVelocityPrivate
{
  Q_DECLARE_PUBLIC(GraphVelocity129)
public:
  GraphVelocity129Private(){}
  ~GraphVelocity129Private(){}

};

GraphVelocity129::GraphVelocity129(QWidget *parent) :
  IGraphVelocity(*(new GraphVelocity129Private),parent),
  ui(new Ui::GraphVelocity129)
{
  ui->setupUi(this);
}

GraphVelocity129::~GraphVelocity129()
{
  delete ui;
  qDebug()<<"GraphVelocity129 destruct-->";
}
void GraphVelocity129::setCustomVisitActive(IUiWidget *uiWidget)
{

}
void GraphVelocity129::setUiVersionName()
{
  Q_D(GraphVelocity129);
  d->m_versionName="V129";
  setObjectName("GraphVelocity129");
}

void GraphVelocity129::setupDataMappings()
{

}
