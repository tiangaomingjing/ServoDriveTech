#include "graphencoder129.h"
#include "ui_graphencoder129.h"
#include "igraphencoder_p.h"

class GraphEncoder129Private:public IGraphEncoderPrivate
{
  Q_DECLARE_PUBLIC(GraphEncoder129)
public:
  GraphEncoder129Private(){}
  ~GraphEncoder129Private(){}
};

GraphEncoder129::GraphEncoder129(QWidget *parent) :
  IGraphEncoder(*(new GraphEncoder129Private),parent),
  ui(new Ui::GraphEncoder129)
{
  ui->setupUi(this);
}

GraphEncoder129::~GraphEncoder129()
{
  delete ui;
}
void GraphEncoder129::visitActive(IUiWidget *uiWidget)
{

}
void GraphEncoder129::setUiVersionName()
{
  Q_D(GraphEncoder129);
  d->m_versionName="V129";
}
