#ifndef UIRAM_H
#define UIRAM_H

#include "uiram_global.h"
#include "iuiwidget.h"

namespace Ui {
class UiRAM;
}
class QWidget;
class UiRAMPrivate;

class UIRAMSHARED_EXPORT UiRAM:public IUiWidget
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(UiRAM)
    Q_PROPERTY(QColor ramNodeColor READ ramNodeColor WRITE setRamNodeColor NOTIFY ramNodeColorChanged)
public:
  explicit UiRAM(QWidget *parent = 0);
  ~UiRAM();

  bool readPageFLASH()Q_DECL_OVERRIDE{return true;}
  bool writePageFLASH()Q_DECL_OVERRIDE{return true;}
  bool hasConfigFunc()Q_DECL_OVERRIDE;
  bool hasSaveFunc()Q_DECL_OVERRIDE;

  QColor ramNodeColor();
  void setRamNodeColor(const QColor &nodeColor);

signals:
  void ramNodeColorChanged(QColor &clr);
protected:
  void setContextAction() Q_DECL_OVERRIDE;
  void addTreeWidget(QTreeWidget *tree);
  bool eventFilter(QObject *obj, QEvent *event);
private:
  QStackedWidget *getUiStackedWidget(void) Q_DECL_OVERRIDE;
  QVBoxLayout *getVBoxLayout(void)Q_DECL_OVERRIDE;
  void setDefaultUi()Q_DECL_OVERRIDE;

  void setItemColor(QTreeWidgetItem *item);
  void updateItemData(QTreeWidgetItem *item);
  void writeItem(QTreeWidgetItem *item);
  void readItem(QTreeWidgetItem *item);
  bool isEditedDataValid(QTreeWidgetItem *item);

private:
  Ui::UiRAM *ui;
  UiRAMPrivate *dd;
private slots:
  void onTreeItemClickedEdit(QTreeWidgetItem *item,int column);
  void onActionEditFinished();
  void onItemExpanded(QTreeWidgetItem *item);

};

#endif // UIRAM_H
