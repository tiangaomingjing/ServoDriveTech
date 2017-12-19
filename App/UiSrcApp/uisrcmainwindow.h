#ifndef UISRCMAINWINDOW_H
#define UISRCMAINWINDOW_H

#include <QMainWindow>
#include "Kernel/globalconfig.h"

namespace Ui {
class UiSrcMainWindow;
}
class SdAssembly;
class IUiControler;

class UiSrcMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit UiSrcMainWindow(QWidget *parent = 0);
  ~UiSrcMainWindow();

private:
  Ui::UiSrcMainWindow *ui;
  QList<SdAssembly*>m_sdAssemblyList;
  IUiControler *m_gUiControl;
  GlobalConfig m_gConfig;
  SdAssembly *m_currentSdAssembly;
};

#endif // UISRCMAINWINDOW_H
