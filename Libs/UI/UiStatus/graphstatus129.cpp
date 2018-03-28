#include "graphstatus129.h"
#include "ui_graphstatus129.h"
#include "igraphstatus_p.h"
#include "ledalarm.h"
#include "gtutils.h"
#include "sdtglobaldef.h"
#include "sevdevice.h"
#include "iuiwidget.h"

#include <QGridLayout>
#include <QTreeWidget>
#include <QDebug>

#define CURR_STATE_INX    0
#define ADC_VDC_INX       1
#define ALM_FLAG_INX      2
#define ALM_CODE_ALL_INX  3
#define CMD_ID_INX        4
#define CURR_ID_INX       5
#define USR_MODE_INX      6



class GraphStatus129Private:public IGraphStatusPrivate
{
  Q_DECLARE_PUBLIC(GraphStatus129)
public:
  GraphStatus129Private(){}
  ~GraphStatus129Private(){}
};

GraphStatus129::GraphStatus129(QWidget *parent) :
  IGraphStatus(*(new GraphStatus129Private),parent),
  ui(new Ui::GraphStatus129)
{
  ui->setupUi(this);
  ui->btn_statusClearAlarm->setText(tr("ClearAlarm"));
  connect(ui->btn_statusClearAlarm,SIGNAL(clicked(bool)),this,SLOT(onBtnClearAlarmClicked()));
}

GraphStatus129::~GraphStatus129()
{
  delete ui;
}
void GraphStatus129::setUiVersionName()
{
  Q_D(GraphStatus129);
  d->m_versionName="V129";
}

void GraphStatus129::setupDataMappings()
{

}

void GraphStatus129::setDeviceStatusIconByCss(const QString &css)
{
  QString iconpath=GTUtils::customPath()+"/option/style/"+css+"/icon/status_device.png";
  ui->label_statusIcon->setPixmap(QPixmap(iconpath));
}

QWidget *GraphStatus129::alarmBackgroundWidget()
{
  return ui->widget_statusAlarm;
}

void GraphStatus129::addLedErrorToUi()
{
  Q_D(GraphStatus129);
  ui->verticalLayout_statusInfo->insertWidget(0,d->m_ledFlag);
  ui->verticalLayout_statusInfo->setContentsMargins(20,30,20,20);
  ui->verticalLayout_statusInfo->setStretch(0,0);
  ui->verticalLayout_statusInfo->setStretch(1,1);
  ui->verticalLayout_statusInfo->setStretch(2,0);
  ui->verticalLayout_statusInfo->setStretch(3,1);
}

quint32 GraphStatus129::alarmCode()
{
  Q_D(GraphStatus129);
  quint32 code=0;
  double value=0;
  value=d->m_treeWidget->topLevelItem(ALM_CODE_ALL_INX)->text(GT::COL_PAGE_TREE_VALUE).toDouble();
  code=value;
  return code;
}

bool GraphStatus129::hasError()
{
  Q_D(GraphStatus129);
  qint16 code=0;
  double value=0;
  value=d->m_treeWidget->topLevelItem(ALM_FLAG_INX)->text(GT::COL_PAGE_TREE_VALUE).toDouble();
  code=value;
  return (bool)code;
}

void GraphStatus129::updateUiLabelText()
{
  Q_D(GraphStatus129);
  //从1开始的
  qint16 currState=d->m_treeWidget->topLevelItem(CURR_STATE_INX)->text(GT::COL_PAGE_TREE_VALUE).toDouble()-1;
  if(currState<d->m_sevStatusText.count())
    ui->label_statusValue_sevStatus->setText(d->m_sevStatusText.at(currState));

  double vdc;
  double vdcGain=1;
  vdcGain=d->m_treeWidget->topLevelItem(ADC_VDC_INX)->text(GT::COL_PAGE_TREE_SCALE).toDouble();
  vdc=d->m_treeWidget->topLevelItem(ADC_VDC_INX)->text(GT::COL_PAGE_TREE_VALUE).toDouble()/vdcGain;
  ui->label_statusValue_busVol->setText(QString::number(vdc,'f',3));

  qint16 cmdMode=0;
  cmdMode=d->m_treeWidget->topLevelItem(CMD_ID_INX)->text(GT::COL_PAGE_TREE_VALUE).toDouble();
  if(cmdMode<d->m_sevModeText.count())
    ui->label_statusValue_cmdMode->setText(d->m_sevModeText.at(cmdMode));

  qint16 currMode=0;
  currMode=d->m_treeWidget->topLevelItem(CURR_ID_INX)->text(GT::COL_PAGE_TREE_VALUE).toDouble();
  if(currMode<d->m_sevModeText.count())
    ui->label_statusValue_curMode->setText(d->m_sevModeText.at(currMode));

  qint16 usrMode=0;
  usrMode=d->m_treeWidget->topLevelItem(USR_MODE_INX)->text(GT::COL_PAGE_TREE_VALUE).toDouble();
  if(usrMode<d->m_sevUsrModeText.count())
    ui->label_statusValue_usrMode->setText(d->m_sevUsrModeText.at(usrMode));

}

void GraphStatus129::onBtnClearAlarmClicked()
{
  Q_D(GraphStatus129);
  d->m_dev->clearAlarm(d->m_uiWidget->uiIndexs().axisInx);
  qDebug()<<"clear alarm";
}

