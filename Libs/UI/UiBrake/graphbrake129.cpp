#include "graphbrake129.h"
#include "igraphbrake_p.h"
#include "ui_graphbrake129.h"

class GraphBrake129Private:public IGraphBrakePrivate
{
  Q_DECLARE_PUBLIC(GraphBrake129)
public:
  GraphBrake129Private(){}
  ~GraphBrake129Private(){}

};

GraphBrake129::GraphBrake129(QWidget *parent) :
  IGraphBrake(*(new GraphBrake129Private),parent),
  ui(new Ui::GraphBrake129)
{
  ui->setupUi(this);
}
GraphBrake129::~GraphBrake129()
{
  delete ui;
}
