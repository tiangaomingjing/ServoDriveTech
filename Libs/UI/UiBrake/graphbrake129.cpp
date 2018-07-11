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

}
GraphBrake129::~GraphBrake129()
{
  delete ui;
  qDebug()<<"GraphBrake129 destruct-->";
}

void GraphBrake129::syncTreeDataToUiFace()
{
  //将树的数据全更新到用户界面上
  Q_D(GraphBrake129);
  d->m_mapping->syncAllItem2BoxText();
}

void GraphBrake129::setCustomVisitActive(IUiWidget *uiWidget)
{
  Q_UNUSED(uiWidget);
}

void GraphBrake129::setUiVersionName()
{
  Q_D(GraphBrake129);
  d->m_versionName="V129";
}

void GraphBrake129::setupDataMappings()
{
  Q_D(GraphBrake129);

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
}
