#include "uiencoder.h"
#include "ui_uiencoder.h"
#include "iuiwidget_p.h"
#include "igraphencoder.h"
#include "sevdevice.h"
#include "gtutils.h"

#include <QQuickWidget>
#include <QQmlContext>
#include <QDebug>


class UiEncoderPrivate:public IUiWidgetPrivate
{
  Q_DECLARE_PUBLIC(UiEncoder)
public:
  UiEncoderPrivate();
  ~UiEncoderPrivate();
protected:
  IGraphEncoder *m_graphEncoder;

};
UiEncoderPrivate::UiEncoderPrivate()
{

}
UiEncoderPrivate::~UiEncoderPrivate()
{

}

UiEncoder::UiEncoder(QWidget *parent):IUiWidget(*(new UiEncoderPrivate),parent),ui(new Ui::UiEncoder)
{
  ui->setupUi(this);

}
UiEncoder::~UiEncoder()
{
  Q_D(UiEncoder);
  delete ui;
  delete d->m_graphEncoder;
}

bool UiEncoder::hasConfigFunc()
{
  return false;
}

bool UiEncoder::hasSaveFunc()
{
  return true;
}
void UiEncoder::accept(QWidget *w)
{
  Q_D(UiEncoder);
  ui->qmlHboxLayout->addWidget(w);
  d->m_graphEncoder=dynamic_cast<IGraphEncoder *>(w);
  d->m_graphEncoder->visit(this);
}
void UiEncoder::setUiActive(bool actived)
{
  Q_D(UiEncoder);
  if(d->m_device->isConnecting())
  {
    if(actived)
    {
      //读一次FLASH的值
      //开启编码器刷新定时器及错误检查
      readPageFLASH();
      emit encActive();
    }
//    GTUtils::delayms(100);
    d->m_graphEncoder->startUpdateTimer(actived);
    qDebug()<<"TEST_OUT UiEncoder :d->m_graphEncoder->startUpdateTimer(actived)"<<actived;
  }
}

void UiEncoder::setContextAction()
{
  createActionSwitchView();
}

void UiEncoder::onDspReset()
{
  setUiActive(false);
}

QStackedWidget *UiEncoder::getUiStackedWidget(void)
{
  return ui->stackedWidget;
}

QVBoxLayout *UiEncoder::getVBoxLayout(void)
{
  return ui->verticalLayout_tree;
}
void UiEncoder::setDefaultUi()
{
  setCurrentUiIndex(0);
}

