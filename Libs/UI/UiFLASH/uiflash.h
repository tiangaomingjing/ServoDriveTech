#ifndef UIFLASH_H
#define UIFLASH_H

#include "uiflash_global.h"
#include "iuiwidget.h"

namespace Ui {
class UiFLASH;
}
class QWidget;
class UiFLASHPrivate;

class UIFLASHSHARED_EXPORT UiFLASH:public IUiWidget
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(UiFLASH)

    Q_PROPERTY(QColor flashNodeColor READ flashNodeColor WRITE setFlashNodeColor NOTIFY flashNodeColorChanged)

public:
  explicit UiFLASH(QWidget *parent = 0);
  ~UiFLASH();

  bool readPageFLASH()Q_DECL_OVERRIDE{return true;}
  bool writePageFLASH()Q_DECL_OVERRIDE{return true;}
  bool hasConfigFunc()Q_DECL_OVERRIDE;
  bool hasSaveFunc()Q_DECL_OVERRIDE;

  QColor flashNodeColor();
  void setFlashNodeColor(const QColor &nodeColor);

signals:
  void flashNodeColorChanged(QColor &clr);
protected:
  void setContextAction();
  void addTreeWidget(QTreeWidget *tree);
  bool eventFilter(QObject *obj, QEvent *event);
private:
  QStackedWidget *getUiStackedWidget(void)Q_DECL_OVERRIDE;
  QVBoxLayout *getVBoxLayout(void)Q_DECL_OVERRIDE;
  void setDefaultUi()Q_DECL_OVERRIDE;
  void setItemColor(QTreeWidgetItem *item);
  void updateItemData(QTreeWidgetItem *item);
  void writeItem(QTreeWidgetItem *item);
  void readItem(QTreeWidgetItem *item);
  bool isEditedDataValid(QTreeWidgetItem *item);

private:
    Ui::UiFLASH *ui;

private slots:
  void onTreeItemClickedEdit(QTreeWidgetItem *item,int column);
  void onActionEditFinished();
  void onItemExpanded(QTreeWidgetItem *item);

};

#endif // UIFLASH_H
