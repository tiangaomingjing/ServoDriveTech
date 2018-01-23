#include "graphcurrent129.h"
#include "ui_graphcurrent129.h"
#include "igraphcurrent_p.h"
class GraphCurrent129Private:public IGraphCurrentPrivate
{
  Q_DECLARE_PUBLIC(GraphCurrent129)
public:
  GraphCurrent129Private(){}
  ~GraphCurrent129Private(){}
};

GraphCurrent129::GraphCurrent129(QWidget *parent) :
  IGraphCurrent(*(new GraphCurrent129Private),parent),
  ui(new Ui::GraphCurrent129)
{
  ui->setupUi(this);
}

GraphCurrent129::~GraphCurrent129()
{
  delete ui;
}
void GraphCurrent129::visit(IUiWidget *ui)
{

}
