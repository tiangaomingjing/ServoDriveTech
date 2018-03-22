#include "graphstatus129.h"
#include "ui_graphstatus129.h"
#include "igraphstatus_p.h"
#include "ledalarm.h"
#include "gtutils.h"

#include <QGridLayout>
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

