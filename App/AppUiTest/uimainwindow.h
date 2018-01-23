#ifndef UIMAINWINDOW_H
#define UIMAINWINDOW_H

#include <QMainWindow>
#include "Kernel/globalconfig.h"

namespace Ui {
class UiMainWindow;
}
class SdAssembly;
class UiMainWindowPrivate;
class QTreeWidgetItem;
class DeviceConfig;

class UiMainWindow : public QMainWindow
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(UiMainWindow)
enum NavShowType{
  NAV_SHOW_SINGLE,
  NAV_SHOW_SINGLE_1_4_6,
  NAV_SHOW_MIX
};
public:
  explicit UiMainWindow(QWidget *parent = 0);
  ~UiMainWindow();
  bool init();

  void readConfig();

  void staticUiInit();
  bool deviceInit();
  void navigationTreeInit();
  void globalUiPageInit();

  void clearDevice();
  void clearNavigationTree();
  void clearGlobalUiPage();
  void clear();


private slots:
  void onProgressInfo(int v, QString msg);

  void onActConnectTestClicked();
  void onActDisConnectTestClicked();
  void onActNewTestClicked();
  void onActWriteFLASHTestClicked();
  void onActReadFlashTestClicked();
  void onActQueryTestClicked();
  void onActConnectClicked();
  void onActDisConnectClicked();
  void onActNewSelectClicked();
  void onActChineseClicked();
  void onActEnglishClicked();

  void onNavTreeWidgetItemClicked(QTreeWidgetItem * item, int column);
  static void processCallBack(void *argv,short *value);

private:
  NavShowType getNavShowType();
  void clearStackedWidget();
  void stackedWidgetInit();
  void removeAllStackedWidget();

private:
  Ui::UiMainWindow *ui;
  UiMainWindowPrivate *d_ptr;
  static short value;

  void createSdAssemblyByDevConfig(const QList<DeviceConfig *> &configList);
};

#endif // UIMAINWINDOW_H
