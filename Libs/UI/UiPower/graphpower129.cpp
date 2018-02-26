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
  foreach (QDoubleSpinBox *box, allBox) {
    box->installEventFilter(this);
  }
}

GraphPower129::~GraphPower129()
{
  delete ui;
}
void GraphPower129::syncTreeDataToUiFace()
{
  //将树的数据全更新到用户界面上
  Q_D(GraphPower129);
  d->m_mapping->syncAllItem2BoxText();
}

void GraphPower129::visitActive(IUiWidget *uiWidget)
{
  Q_D(GraphPower129);

  qDebug()<<"graph power 129 visit"<<uiWidget->objectName();
  d->m_dev=uiWidget->device();
  int axis=uiWidget->uiIndexs().axisInx;
  int page=uiWidget->uiIndexs().pageInx;
  d->m_treeWidget=d->m_dev->axisTreeSource(axis,page);

  //this->ui->dspinBox_maxVoltage->setEnabled(false);

  QList<QDoubleSpinBox *>bList;
  //bList的先后位置不能变
  bList<<ui->dSpinBox_pwrBusOver\
       <<ui->dSpinBox_pwrBusUnder\
       <<ui->dSpinBox_pwrBrakeOpen\
       <<ui->dSpinBox_pwrBrakeClose\
       <<ui->dSpinBox_pwrRelayOn\
       <<ui->dSpinBox_pwrRelayOff;
  if(bList.count()<=d->m_treeWidget->topLevelItemCount())
  {
    for(int i=0;i<bList.count();i++)
    {
      d->m_mapping->insertBox2Item(bList.at(i),d->m_treeWidget->topLevelItem(i));
      d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(i),bList.at(i));
    }
  }

  setEditTextStatusDefaultAll();

  connect(d->m_dev,SIGNAL(itemRangeValid(QTreeWidgetItem*,int)),this,SLOT(onItemBoxEditTextError(QTreeWidgetItem*,int)));
  OptFace *face=dynamic_cast<OptFace *>(OptContainer::instance()->optItem("optface"));
  connect(face,SIGNAL(faceCssChanged(QString)),this,SLOT(onFaceCssChanged(QString)));
}
void GraphPower129::setUiVersionName()
{
  Q_D(GraphPower129);
  d->m_versionName="V129";
}

bool GraphPower129::eventFilter(QObject *obj, QEvent *event)
{
  if (event->type()==QEvent::KeyPress)
  {
    QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
    if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)
    {
      Q_D(GraphPower129);
      qDebug()<<"enter clicked"<<"object name"<<obj->objectName();
      QDoubleSpinBox* box = dynamic_cast<QDoubleSpinBox*>(obj);
      d->m_mapping->syncBoxText2Item(box);
      setEditTextStatus(box,OptFace::EDIT_TEXT_STATUS_READY);
      return true;
    }
  }
  return QWidget::eventFilter(obj,event);
}

void GraphPower129::onItemBoxEditTextError(QTreeWidgetItem *item,int status)
{
  Q_D(GraphPower129);
  QDoubleSpinBox *box=d->m_mapping->box(item);
  if(box!=NULL)
    setEditTextStatus(box,OptFace::EditTextStatus(status));
}
void GraphPower129::onFaceCssChanged(const QString &css)
{
  Q_UNUSED(css);
  setEditTextStatusDefaultAll();
}

void GraphPower129::setEditTextStatus(QDoubleSpinBox *box,OptFace::EditTextStatus status)
{
  OptFace *face=dynamic_cast<OptFace *>(OptContainer::instance()->optItem("optface"));
  face->setEditTextStatus(box,status);
}
void GraphPower129::setEditTextStatusDefaultAll()
{
  Q_D(GraphPower129);
  foreach (QDoubleSpinBox *box, d->m_mapping->boxLists())
  {
    setEditTextStatus(box,OptFace::EDIT_TEXT_STATUS_DEFAULT);
//    setEditTextStatus(box,OptFace::EDIT_TEXT_STATUS_READY);
  }
}
