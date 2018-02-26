#include "graphbrake129.h"
#include "igraphbrake_p.h"
#include "ui_graphbrake129.h"
#include "iuiwidget.h"
#include "uibrake.h"
#include "sevdevice.h"
#include "boxitemmapping.h"
#include "Option"
#include "gtutils.h"

#include <QDebug>
#include <QTreeWidget>
#include <QKeyEvent>
#include <QPainter>

class GraphBrake129Private:public IGraphBrakePrivate
{
  Q_DECLARE_PUBLIC(GraphBrake129)
public:
  GraphBrake129Private(){}
  ~GraphBrake129Private(){}

};

BrakePaintPrivate::BrakePaintPrivate(QWidget *parent):QWidget(parent) {
}

BrakePaintPrivate::~BrakePaintPrivate() {

}

void BrakePaintPrivate::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    QPixmap pixMap;
    OptFace *face = dynamic_cast<OptFace *>(OptContainer::instance()->optItem("optface"));
    QString iconPath = GTUtils::customPath()+"/option/style/"+face->css()+"/icon/";
    QString path = iconPath + "brake.png";
    pixMap.load(path);
    painter.drawPixmap(0, 0, this->width(), this->height(), pixMap);
}

GraphBrake129::GraphBrake129(QWidget *parent) :
  IGraphBrake(*(new GraphBrake129Private),parent),
  ui(new Ui::GraphBrake129)
{
  ui->setupUi(this);

  QList<QDoubleSpinBox *> allBox = findChildren<QDoubleSpinBox *>();
  qDebug()<<"all box count="<<allBox.count();
  foreach (QDoubleSpinBox *box, allBox) {
    box->installEventFilter(this);
  }
}
GraphBrake129::~GraphBrake129()
{
  delete ui;
}

void GraphBrake129::syncTreeDataToUiFace()
{
  //将树的数据全更新到用户界面上
  Q_D(GraphBrake129);
  d->m_mapping->syncAllItem2BoxText();
}

void GraphBrake129::visitActive(IUiWidget *uiWidget)
{
    Q_D(GraphBrake129);

    qDebug()<<"graph brake 129 visit"<<uiWidget->objectName();
    d->m_dev=uiWidget->device();
    int axis=uiWidget->uiIndexs().axisInx;
    int page=uiWidget->uiIndexs().pageInx;
    d->m_treeWidget=d->m_dev->axisTreeSource(axis,page);

    QList<QDoubleSpinBox *>bList;
    //bList的先后位置不能变
    bList<<ui->dSpinBox_brakeDynamicWait\
        <<ui->dSpinBox_brakeDynamicDuration\
       <<ui->dSpinBox_brakeExternalDelay\
      <<ui->dSpinBox_brakeExternalWait\
     <<ui->dSpinBox_brakeExternalDuration\
    <<ui->dSpinBox_brakeDynamicLag\
    <<ui->dSpinBox_brakeExternalLag\
    <<ui->dSpinBox_brakeEmergencyDeceleration;

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

void GraphBrake129::setUiVersionName()
{
  Q_D(GraphBrake129);
  d->m_versionName="V129";
}

bool GraphBrake129::eventFilter(QObject *obj, QEvent *event)
{
  if (event->type()==QEvent::KeyPress)
  {
    QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
    if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)
    {
      Q_D(GraphBrake129);
      qDebug()<<"enter clicked"<<"object name"<<obj->objectName();
      QDoubleSpinBox* box=dynamic_cast<QDoubleSpinBox*>(obj);
      d->m_mapping->syncBoxText2Item(box);
      setEditTextStatus(box,OptFace::EDIT_TEXT_STATUS_READY);
      return true;
    }
  }
  return QWidget::eventFilter(obj,event);
}

void GraphBrake129::onItemBoxEditTextError(QTreeWidgetItem *item,int status)
{
  Q_D(GraphBrake129);
  QDoubleSpinBox *box=d->m_mapping->box(item);
  if(box!=NULL)
    setEditTextStatus(box,OptFace::EditTextStatus(status));
}
void GraphBrake129::onFaceCssChanged(const QString &css)
{
  Q_UNUSED(css);
  setEditTextStatusDefaultAll();
}

void GraphBrake129::setEditTextStatus(QDoubleSpinBox *box,OptFace::EditTextStatus status)
{
  OptFace *face=dynamic_cast<OptFace *>(OptContainer::instance()->optItem("optface"));
  face->setEditTextStatus(box,status);
}
void GraphBrake129::setEditTextStatusDefaultAll()
{
  Q_D(GraphBrake129);
  foreach (QDoubleSpinBox *box, d->m_mapping->boxLists())
  {
    setEditTextStatus(box,OptFace::EDIT_TEXT_STATUS_DEFAULT);
//    setEditTextStatus(box,OptFace::EDIT_TEXT_STATUS_READY);
  }
}
