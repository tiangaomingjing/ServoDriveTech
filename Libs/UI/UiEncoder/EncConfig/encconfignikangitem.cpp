#include "encconfignikangitem.h"
#include "sdtglobaldef.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QDebug>

EncConfigNiKangItem::EncConfigNiKangItem(QObject *parent) : IEncConfigItem(parent),
  m_comboBox(NULL)
{
  m_encConfigData=0x0001;
  setObjectName(tr("EncNiKang"));
}
EncConfigNiKangItem::~EncConfigNiKangItem()
{
  GT::deletePtrObject(m_attributeUi);
}
void EncConfigNiKangItem::attributeUiInit()
{
  m_attributeUi=new QWidget;
  QHBoxLayout *hlayout=new QHBoxLayout(m_attributeUi);
  QLabel *label=new QLabel(tr("baud:"),m_attributeUi);
  m_comboBox=new QComboBox(m_attributeUi);
  m_comboBox->addItem("4M",0);//bit12:0 4M ,1 2.5M
  m_comboBox->addItem("2.5M",1);
  hlayout->addWidget(label);
  hlayout->addWidget(m_comboBox);
  m_attributeUi->setLayout(hlayout);

}
bool EncConfigNiKangItem::execute()
{
  if(m_comboBox!=NULL)
  {
    quint8 data=m_comboBox->currentData().toUInt();
    m_encConfigData&=0x0fff;//12-15位清0
    if(data==1)
    {
      m_encConfigData|=0x1000;
    }
  }
  qDebug()<<"m_encConfigData"<<m_encConfigData;
  return true;
}

