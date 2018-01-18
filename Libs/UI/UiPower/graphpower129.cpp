#include "graphpower129.h"
#include "ui_graphpower129.h"
#include "igraphpower_p.h"
class GraphPower129Private:public IGraphPowerPrivate
{
  Q_DECLARE_PUBLIC(GraphPower129)
public:
  GraphPower129Private(){}
  ~GraphPower129Private(){}
};

GraphPower129::GraphPower129(QWidget *parent) :
  IGraphPower(*(new GraphPower129Private),parent),
  ui(new Ui::GraphPower129)
{
  ui->setupUi(this);
}

GraphPower129::~GraphPower129()
{
  delete ui;
}
