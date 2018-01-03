#ifndef APPMAINWINDOWTEST_H
#define APPMAINWINDOWTEST_H

#include <QMainWindow>
#include <QList>
#include "Kernel/globalconfig.h"

class QTreeWidget;
class QTreeWidgetItem;

namespace Ui {
class AppMainWindowTest;
}
namespace ComDriver {
class ICom;
}

class SdAssembly;
class OptContainer;
class AppMainWindowTest : public QMainWindow
{
  Q_OBJECT

public:
  explicit AppMainWindowTest(QWidget *parent = 0);
  ~AppMainWindowTest();

private slots:
  void on_pushButton_clicked();

  void on_pushButton_init_clicked();

  void on_pushButton_memery_clicked();

  void onProgressInfo(int v,QString msg);

  void on_actionChangeAddr_triggered();

  void on_pushButton_connectTest_clicked();

private:
  void initial();
  static void processBarInfo(void *bar, short *v);

private:
  Ui::AppMainWindowTest *ui;

  //程序启动时测试用例
  QList<SdAssembly*>sdAssemblyList;
  OptContainer *gConfig;
  SdAssembly *currentSdAssembly;
  bool stop;
  void mainFormInitTestCase();
  void mainConnectTestCase();
  void mainMemeryTestCase();
  QString m_filePath;
};

#endif // APPMAINWINDOWTEST_H
