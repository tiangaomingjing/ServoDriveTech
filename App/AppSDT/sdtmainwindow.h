#ifndef SDTMAINWINDOW_H
#define SDTMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class SDTMainWindow;
}
class QToolButton;
class SdAssembly;
class QTreeWidgetItem;
class IUiControler;
class OptContainer;
class SdtStatusBar;
class QTreeWidget;
class QProgressBar;
class GlobalUiControler;
class IUiWidget;
class PlotUnit;
class DeviceConfig;

class SDTMainWindow : public QMainWindow
{
  Q_OBJECT
  enum UiShowStatus{
    UI_STA_FUNCF,
    UI_STA_FUNCNF,
    UI_STA_PLOTF,
    UI_STA_PLOTNF
  };
public:
  explicit SDTMainWindow(QWidget *parent = 0);
  ~SDTMainWindow();

  bool init();

  QTreeWidget *navTreeWidget() const;

private:
  void staticUiInit();
  void createActions();
  void setAppIcon();
  void createConnections();
  void clearStackedWidget();
  void closeEvent(QCloseEvent *e)override;
//  void changeEvent(QEvent *event);//可用于捕抓语言改变事件

  static void processCallBack(void *argv,short *value);

  bool deviceInit();
  void navigationTreeInit();
  void clearNavigationTree();
  void globalUiPageInit();
  void stackedWidgetInit();
  void removeAllStackedWidget();

  void disactiveAllUi();
  void activeCurrentUi();
  void changeConfigSaveBtnStatus();
  void showPlotUiOnly(bool show);

  void setNavCurrentSelectedInfo();

  void createSdAssemblyByDevConfig(const QList<DeviceConfig *> &configList);

  SdAssembly *createSdAssembly(DeviceConfig *cfg);

  //ui显示状态相关
  void setUiStatusConnect(bool isNet);
  void setUiAllEnable(bool en);

  bool setConnect(bool net);

  bool isAutoLoad();

  bool MessageBoxAsk(const QString &msg);

signals:
  void initProgressInfo(int barValue,QString msg);
private slots:
  void onActnOptionClicked();
  void onActnTbtnMoreClicked();
  void onActnConnectClicked(bool checked);
  void onActnDisConnectClicked(bool checked);
  void onActnHelpDeviceInfoClicked();
  void onActnNewConfigClicked();
  void onActnSaveClicked();

  //响应option选项slots
  void onOptAutoLoadChanged(bool changed);
  void onOptFaceCssChanged(const QString &css);

  void onProgressInfo(int barValue, QString msg);

  void onNavTreeWidgetItemClicked(QTreeWidgetItem * item, int column);

  void onStatusBarPageChanged(int pIndex);

  void onPlotFloatingChanged(bool floating);


private:

  //---------ui--------------
  Ui::SDTMainWindow *ui;
  QAction *m_actnDisNet;
  QAction *m_actnConnect;
  QAction *m_actnNewConfig;
  QAction *m_actnDownload;
  QAction *m_actnUpload;
  QAction *m_actnCompare;
  QAction *m_actnConfig;
  QAction *m_actnSave;
  QToolButton *m_tbtnMore;
  QAction *m_actnOffMode;
  QAction *m_actnOnMode;
  QToolButton *m_tbtnHelp;
  QAction *m_actnAboutHardware;
  QAction *m_actnAboutSoftware;
  QAction *m_actnReset;
  QAction *m_actnUpdateFlash;
  QAction *m_actnOption;
  QAction *m_actnProduce;
  SdtStatusBar *m_statusBar;
  QProgressBar *mp_progressBar;
  UiShowStatus m_currentUiStatus;

  static short m_probarValue;

  //-------servo-------
  QList<SdAssembly*>m_sdAssemblyList;
  GlobalUiControler *m_gUiControl;
  OptContainer *m_optc;
  SdAssembly *m_currentSdAssembly;

  PlotUnit *m_plot;
  bool m_connecting;

};

#endif // SDTMAINWINDOW_H
