#include "graphposition129.h"
#include "ui_graphposition129.h"
#include "igraphposition_p.h"
class GraphPosition129Private:public IGraphPositionPrivate
{
  Q_DECLARE_PUBLIC(GraphPosition129)
public:
  GraphPosition129Private(){}
  ~GraphPosition129Private(){}
};

GraphPosition129::GraphPosition129(QWidget *parent) :
  IGraphPosition(*(new GraphPosition129Private),parent),
  ui(new Ui::GraphPosition129)
{
  ui->setupUi(this);
}

GraphPosition129::~GraphPosition129()
{
  delete ui;
}
void GraphPosition129::visitActive(IUiWidget *uiWidget)
{

}
void GraphPosition129::setUiVersionName()
{
  Q_D(GraphPosition129);
  d->m_versionName="V129";
}
