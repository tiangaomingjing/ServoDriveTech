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
