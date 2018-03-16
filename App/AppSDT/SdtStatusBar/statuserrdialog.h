#ifndef STATUSERRDIALOG_H
#define STATUSERRDIALOG_H

#include <QDialog>

namespace Ui {
class StatusErrDialog;
}
class QTreeWidget;
class QTreeWidgetItem;
class StatusErrDialog : public QDialog
{
  Q_OBJECT

public:
  explicit StatusErrDialog(QTreeWidget *navTree,QWidget *parent = 0);
  ~StatusErrDialog();

  void updateDevice(QTreeWidget *navTree);
  void setStatusError(quint32 devInx,qint16 axis,bool hasErr);

signals:
  void statusPageChanged(int pIndex);

public slots:
  void onStatusError(quint32 devInx,qint16 axis,bool hasErr);
private slots:
  void onTreeWidgetItemClicked(QTreeWidgetItem *item,int column);
private:
  void setItemStatus(QTreeWidgetItem *item,bool status);
  QTreeWidgetItem *findStatusItem(QTreeWidgetItem *axisItem) const;
private:
  Ui::StatusErrDialog *ui;
};

#endif // STATUSERRDIALOG_H
