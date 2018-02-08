#include "graphpower129.h"
#include "ui_graphpower129.h"
#include "igraphpower_p.h"
#include "iuiwidget.h"
#include "uipower.h"
#include "sevdevice.h"
#include "boxitemmapping.h"
#include "Option"

#include <QDebug>
#include <QTreeWidget>
#include <QKeyEvent>

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
  QList<QDoubleSpinBox *> allBox = findChildren<QDoubleSpinBox *>();
  qDebug()<<"power all box count="<<allBox.count();
//  foreach (QDoubleSpinBox *box, allBox) {
//    box->installEventFilter(this);
//  }
}

GraphPower129::~GraphPower129()
{
  delete ui;
}
void GraphPower129::visitActive(IUiWidget *uiWidget)
{

}
void GraphPower129::setUiVersionName()
{
  Q_D(GraphPower129);
  d->m_versionName="V129";
}

//bool GraphPower129::eventFilter(QObject *obj, QEvent *event)
//{
//  if (event->type()==QEvent::KeyPress)
//  {
//    QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
//    if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)
//    {
//      Q_D(GraphPower129);
//      qDebug()<<"enter clicked"<<"object name"<<obj->objectName();
//      QDoubleSpinBox* box=dynamic_cast<QDoubleSpinBox*>(obj);
//      d->m_mapping->syncBoxText2Item(box);
//      //setEditTextStatus(box,OptFace::EDIT_TEXT_STATUS_READY);
//      return true;
//    }
//  }
//  return QWidget::eventFilter(obj,event);
//}
