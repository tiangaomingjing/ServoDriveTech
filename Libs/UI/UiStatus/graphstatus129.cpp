#include "graphstatus129.h"
#include "ui_graphstatus129.h"
#include "igraphstatus_p.h"
class GraphStatus129Private:public IGraphStatusPrivate
{
  Q_DECLARE_PUBLIC(GraphStatus129)
public:
  GraphStatus129Private(){}
  ~GraphStatus129Private(){}
};

GraphStatus129::GraphStatus129(QWidget *parent) :
  IGraphStatus(*(new GraphStatus129Private),parent),
  ui(new Ui::GraphStatus129)
{
  ui->setupUi(this);
}

GraphStatus129::~GraphStatus129()
{
  delete ui;
}

void GraphStatus129::setCustomVisitActive(IUiWidget *uiWidget)
{

}
void GraphStatus129::setUiVersionName()
{
  Q_D(GraphStatus129);
  d->m_versionName="V129";
}

void GraphStatus129::setupDataMappings()
{

}
