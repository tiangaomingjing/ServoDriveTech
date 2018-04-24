#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class DialogPickCurve;
}
class OptFace;
class QTreeWidget;
class QTreeWidgetItem;
class QTableWidget;

class DialogPickCurve : public QDialog
{
  Q_OBJECT

public:
  explicit DialogPickCurve(QWidget *parent = 0);
  ~DialogPickCurve();

  void addExpertTreeWidget(const QTreeWidget *tree);
  void setAxisTable(int axisCount);


signals:
  void expertTreeItemDoubleClicked(QTableWidget* axisTable,QTreeWidgetItem *item);

protected:

private slots:
  void onUserSelectChanged();
  void onTreeWidgetExpertExpandedClicked();
  void onExpertTreeWidgetDoubleClicked(QTreeWidgetItem *item,int column);

private:
  void setIcons();
private:
  Ui::DialogPickCurve *ui;
  OptFace *m_face;
};

#endif // DIALOG_H
