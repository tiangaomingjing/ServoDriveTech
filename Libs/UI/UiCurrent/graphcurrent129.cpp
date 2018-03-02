#include "graphcurrent129.h"
#include "ui_graphcurrent129.h"
#include "igraphcurrent_p.h"

#include <QDebug>
class GraphCurrent129Private:public IGraphCurrentPrivate
{
  Q_DECLARE_PUBLIC(GraphCurrent129)
public:
  GraphCurrent129Private(){}
  ~GraphCurrent129Private(){}
};

GraphCurrent129::GraphCurrent129(QWidget *parent) :
  IGraphCurrent(*(new GraphCurrent129Private),parent)
//  ui(new Ui::GraphCurrent129)
{
//  ui->setupUi(this);
}

GraphCurrent129::~GraphCurrent129()
{
//  delete ui;
  qDebug()<<"GraphCurrent129 destruct-->";
}
void GraphCurrent129::visitActive(IUiWidget *uiWidget)
{
  Q_UNUSED(uiWidget);
  createItems();
}
void GraphCurrent129::setUiVersionName()
{
  Q_D(GraphCurrent129);
  d->m_versionName="V129";
}
