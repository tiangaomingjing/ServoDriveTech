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
//  QGridLayout *glayout=new QGridLayout(this);
////  glayout->addWidget(ui->pushButton,0,2);
//  glayout->addLayout(ui->hlayout_btn,0,0);
//  glayout->addWidget(ui->widget_currentPrm,1,0);
//  glayout->addWidget(ui->widget_machinePrm,1,1,1,2);
//  glayout->addWidget(ui->widget_velocityPrm,2,0);
//  glayout->addWidget(ui->widget_impedancePrm,2,1);
//  glayout->addWidget(ui->widget_torquePrm,2,2);

}

GraphMotor129::~GraphMotor129()
{
  delete ui;
}
