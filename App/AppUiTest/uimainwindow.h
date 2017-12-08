#ifndef UIMAINWINDOW_H
#define UIMAINWINDOW_H

#include <QMainWindow>
#include "Kernel/globalconfig.h"

namespace Ui {
class UiMainWindow;
}
class SdAssembly;

class UiMainWindow : public QMainWindow
{
  Q_OBJECT
enum NavShowType{
  NAV_SHOW_SIGNAL,
  NAV_SHOW_MIX
};
public:
  explicit UiMainWindow(QWidget *parent = 0);
  ~UiMainWindow();
  bool init();

  bool servoInit();
  void navigationInit();

private slots:
  void onProgressInfo(int v, QString msg);


private:
  Ui::UiMainWindow *ui;

  QList<SdAssembly*>m_sdAssemblyList;
  GlobalConfig m_gConfig;
  SdAssembly *m_currentSdAssembly;
};

#endif // UIMAINWINDOW_H
