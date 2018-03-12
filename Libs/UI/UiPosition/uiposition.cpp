#include "uiposition.h"
#include "ui_uiposition.h"
#include "iuiwidget_p.h"
#include "igraphposition.h"

#include <QGraphicsScene>
#include <QGraphicsView>

class UiPositionPrivate:public IUiWidgetPrivate
{
  Q_DECLARE_PUBLIC(UiPosition)
public:
  UiPositionPrivate();
  ~UiPositionPrivate();
protected:
  IGraphPosition *m_graphPosition;
//  QGraphicsScene *m_scene;
};
UiPositionPrivate::UiPositionPrivate()
{

}
UiPositionPrivate::~UiPositionPrivate()
{

}

UiPosition::UiPosition(QWidget *parent):IUiWidget(*(new UiPositionPrivate),parent),ui(new Ui::UiPosition)
{
  ui->setupUi(this);

}
UiPosition::~UiPosition()
{
  Q_D(UiPosition);

//  delete d->m_scene;
  delete d->m_graphPosition;

  delete ui;
}

void UiPosition::accept(QWidget *w)
{
  Q_D(UiPosition);
  ui->qmlHboxLayout->addWidget(w);
//  d->m_scene=new QGraphicsScene;
  d->m_graphPosition=dynamic_cast<IGraphPosition *>(w);
//  d->m_graphPosition->setScene(d->m_scene);

  d->m_graphPosition->visit(this);
  ui->label->setText(d->m_graphPosition->objectName());
}

QStackedWidget *UiPosition::getUiStackedWidget(void)
{
  return ui->stackedWidget;
}
QVBoxLayout *UiPosition::getVBoxLayout(void)
{
  return ui->verticalLayout_tree;
}
void UiPosition::setDefaultUi()
{
  setCurrentUiIndex(0);
}

