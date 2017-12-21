#include "uiencoder.h"
#include "ui_uiencoder.h"
#include "iuiwidget_p.h"

#include <QQuickWidget>
#include <QQmlContext>

class UiEncoderPrivate:public IUiWidgetPrivate
{
  Q_DECLARE_PUBLIC(UiEncoder)
public:
  UiEncoderPrivate();
  ~UiEncoderPrivate();
protected:

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
  delete ui;
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
void UiEncoder::setQmlContext()
{

}

void UiEncoder::setQmlSignalSlot()
{

}

void UiEncoder::addQmlWidget()
{
  Q_D(UiEncoder);
  ui->qmlHboxLayout->addWidget(d->m_qwidget);
}
