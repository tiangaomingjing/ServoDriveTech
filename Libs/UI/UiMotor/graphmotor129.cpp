#include "graphmotor129.h"
#include "ui_graphmotor129.h"
#include "igraphmotor_p.h"

class GraphMotor129Private:public IGraphMotorPrivate
{
  Q_DECLARE_PUBLIC(GraphMotor129)
public:
  GraphMotor129Private(){}
  ~GraphMotor129Private(){}
};

GraphMotor129::GraphMotor129(QWidget *parent) :
  IGraphMotor(*(new GraphMotor129Private),parent),
  ui(new Ui::GraphMotor129)
{
  ui->setupUi(this);
}

GraphMotor129::~GraphMotor129()
{
  delete ui;
}
