#include "screenstartup.h"
#include <QProgressBar>
#include <QLabel>
#include <QVBoxLayout>
#include <QSpacerItem>

ScreenStartup::ScreenStartup(QPixmap &pixmap) : QSplashScreen(pixmap)
{
  QVBoxLayout *vlayout=new QVBoxLayout(this);
  setLayout(vlayout);
  vlayout->setMargin(0);
  QSpacerItem *spacerItem=new QSpacerItem(width(),30,QSizePolicy::Expanding,QSizePolicy::Expanding);
  label=new QLabel(this);
  label->setObjectName("startLabel");
  pBar=new QProgressBar(this);
  pBar->setObjectName("startProgressBar");
  pBar->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
  vlayout->addSpacerItem(spacerItem);
  vlayout->addWidget(label);
  vlayout->addWidget(pBar);
}

void ScreenStartup::onProgressMessage(int barValue, QString msg)
{
  label->setText(msg);
  pBar->setValue(barValue);
}
