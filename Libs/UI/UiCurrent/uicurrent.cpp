#include "uicurrent.h"
#include "ui_uicurrent.h"
#include "iuiwidget_p.h"
#include "igraphcurrent.h"

#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>

class UiCurrentPrivate:public IUiWidgetPrivate
{
  Q_DECLARE_PUBLIC(UiCurrent)
public:
  UiCurrentPrivate();
  ~UiCurrentPrivate();
protected:
  IGraphCurrent *m_graphCurrentView;
//  QGraphicsScene *m_scene;
};
UiCurrentPrivate::UiCurrentPrivate():IUiWidgetPrivate(),
  m_graphCurrentView(NULL)
{

}
UiCurrentPrivate::~UiCurrentPrivate()
{

}

UiCurrent::UiCurrent(QWidget *parent):IUiWidget(*(new UiCurrentPrivate),parent),ui(new Ui::UiCurrent)
{
  ui->setupUi(this);
}
UiCurrent::~UiCurrent()
{
  qDebug()<<"begin release UiCurrent ------------------>";
  Q_D(UiCurrent);


  delete d->m_graphCurrentView;
  qDebug()<<"delete m_graphCurrentView";

//  delete d->m_scene;
//  qDebug()<<"delete m_scene";

  delete ui;


  qDebug()<<"UiCurrent destruct-->";
}

void UiCurrent::accept(QWidget *w)//take ownership of w
{
  Q_D(UiCurrent);
  ui->qmlHboxLayout->addWidget(w);

//  d->m_scene=new QGraphicsScene;
  d->m_graphCurrentView=dynamic_cast<IGraphCurrent *>(w);
//  d->m_graphCurrentView->setScene(d->m_scene);

  d->m_graphCurrentView->visit(this);
  ui->label->setText(d->m_graphCurrentView->objectName());
}

void UiCurrent::setUiActive(bool actived)
{
  if(actived)
  {
    Q_D(UiCurrent);
    if(readGenRAM())
      d->m_graphCurrentView->syncTreeDataToUiFace();
  }
}

QStackedWidget *UiCurrent::getUiStackedWidget(void)
{
  return ui->stackedWidget;
}
QVBoxLayout *UiCurrent::getVBoxLayout(void)
{
  return ui->verticalLayout_tree;
}
void UiCurrent::setDefaultUi()
{
  setCurrentUiIndex(0);
}

