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
class ICurve;

class DialogPickCurve : public QDialog
{
  Q_OBJECT

public:
  explicit DialogPickCurve(QWidget *parent = 0);
  ~DialogPickCurve();

  void expertTreeWidgetInit(const QTreeWidget *tree);
  void axisTableInit(int axisCount);
  void usrCurveTableInit(QList<ICurve *> curves);

signals:
  void expertTreeItemDoubleClicked(QTableWidget* axisTable,QTreeWidgetItem *item);
  void addUsrCurveRequest(ICurve *newc);

protected:

private slots:
  void onUserSelectChanged();
  void onTreeWidgetExpertExpandedClicked();
  void onExpertTreeWidgetDoubleClicked(QTreeWidgetItem *item,int column);
  void onUsrTableCellDoubleClicked(int row, int column);

private:
  void setIcons();
private:
  Ui::DialogPickCurve *ui;
  OptFace *m_face;
};

#endif // DIALOG_H
