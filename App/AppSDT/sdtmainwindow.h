#ifndef SDTMAINWINDOW_H
#define SDTMAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

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
class QProcess;
class MessageServer;
class StatusMonitor;
class SevDevice;

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

  void createSdAssemblyListByDevConfig(const QList<DeviceConfig *> &configList);
  void updateSDTMainUiByConfigList(const QList<DeviceConfig *> &configList);
  void updateStatusMonitorDevice(const QList<SevDevice *> &list);

  SdAssembly *createSdAssembly(DeviceConfig *cfg);
  QList<SevDevice *> sevList();

  //ui显示状态相关
  void setUiStatusConnect(bool isNet);
  void setUiAllEnable(bool en);

  bool setConnect(bool net);

  bool isAutoLoad();

  bool MessageBoxAsk(const QString &msg);
  void startListen();

signals:
  void initProgressInfo(int barValue,QString msg);
  void sendDevConfigToServer(QByteArray block);
  void currentTitleChanged(const QString &title);
  void appClosed();
  void beforeSevDeviceChanged();

private slots:
  void onActnOptionClicked();
  void onActnTbtnMoreClicked();
  void onActnConnectClicked(bool checked);
  void onActnDisConnectClicked(bool checked);
  void onActnHelpDeviceInfoClicked();
  void onActnNewConfigClicked();
  void onActnSaveClicked();
  void onActnConfigClicked();
  void onActnDownloadClicked();
  void onActnUploadClicked();
  void onActnProduceClicked();
  void onActnAdvUserClicked();
  void onActnCompareClicked();
  void onActnUpdateClicked();
  void onStartMsgReceived();
  void onCloseMsgReceived();
  void onDownloadMsgReceived(int index, const QString &filePath);
  void onUploadMsgReceived(int index, const QString &filePath);

  //响应option选项slots
  void onOptAutoLoadChanged(bool changed);
  void onOptFaceCssChanged(const QString &css);
  void onOptUserChanged(bool isAdmin);
  void onOptPathChanged(const QStringList &list);

  void onProgressInfo(int barValue, const QString &msg);

  void onNavTreeWidgetItemClicked(QTreeWidgetItem * item, int column);

  void onStatusBarPageChanged(int pIndex);

  //响应状态监视器
  void onDeviceAlarmError(quint16 devId,quint16 axisInx,bool hasError);
  void onDeviceNetError(quint16 devId);

  //响应寻相操作
  void onIpaSearchPhaseInfo(int barValue, const QString &msg);
  void onIpaWarningMsg(const QString &msg);
  void onIpaDone();


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
  QAction *m_actnAdvUser;
  SdtStatusBar *m_statusBar;
  QProgressBar *mp_progressBar;
  UiShowStatus m_currentUiStatus;

  static short m_probarValue;

  //-------servo-------
  QList<SdAssembly*>m_sdAssemblyList;
  GlobalUiControler *m_gUiControl;
  OptContainer *m_optc;
  SdAssembly *m_currentSdAssembly;
  
  //-------socket-------
  bool m_produceClicked;
  QProcess *m_process;
  MessageServer *m_server;


  PlotUnit *m_plot;
  bool m_connecting;
  StatusMonitor *m_statusMonitor;

  QString m_downloadPath;
  QString m_downloadFileName;
  int m_downloadIndex;
  QString m_uploadPath;
  QString m_uploadFileName;
  int m_uploadIndex;
};

#endif // SDTMAINWINDOW_H
