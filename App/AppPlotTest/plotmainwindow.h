#ifndef PLOTMAINWINDOW_H
#define PLOTMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class PlotMainWindow;
}
class AxisModeWidget;

class PlotMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit PlotMainWindow(QWidget *parent = 0);
  ~PlotMainWindow();

private slots:
  void onAxisModeClearOthers(quint16 axis);
  void onAxisModeChanged(quint16 axis, int mode);

private:
  Ui::PlotMainWindow *ui;
  QList<AxisModeWidget*> m_axisModeList;
};

#endif // PLOTMAINWINDOW_H
