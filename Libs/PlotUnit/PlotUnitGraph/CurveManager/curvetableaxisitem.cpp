#include "curvetableaxisitem.h"

#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
#include <QStyledItemDelegate>

CurveTableAxisItem::CurveTableAxisItem(QWidget *parent) : QWidget(parent)
{
  QHBoxLayout *hlayout=new QHBoxLayout(this);
  m_label=new QLabel(this);
  m_label->setAlignment(Qt::AlignCenter);
  m_box=new QComboBox(this);
  m_box->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
  QStyledItemDelegate* itemDelegate = new QStyledItemDelegate(m_box);
  m_box->setItemDelegate(itemDelegate);
  hlayout->addWidget(m_box);
  hlayout->addWidget(m_label);
  hlayout->setMargin(0);
  hlayout->setSpacing(0);
  hlayout->setStretch(0,1);
  hlayout->setStretch(1,1);
}

