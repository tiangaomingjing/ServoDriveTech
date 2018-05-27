#include "sdttreewidgetnav.h"

SdtTreeWidgetNav::SdtTreeWidgetNav(QWidget *parent) : QTreeWidget(parent)
{
  m_szHint = QSize(150,600);
}
void SdtTreeWidgetNav::updateSizeHint(QSize & szHint2Set) {
   m_szHint = szHint2Set;
   updateGeometry();
}

QSize SdtTreeWidgetNav::sizeHint() const {
   return m_szHint;
}
