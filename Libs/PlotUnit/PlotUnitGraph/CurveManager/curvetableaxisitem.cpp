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
  QStyledItemDelegate* itemDelegate = new QStyledItemDelegate(m_box);
  m_box->setItemDelegate(itemDelegate);
  hlayout->addWidget(m_box);
  hlayout->addWidget(m_label);
  hlayout->setMargin(0);
  hlayout->setSpacing(0);
}

