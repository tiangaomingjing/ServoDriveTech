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

class SDTMainWindow : public QMainWindow
{
  Q_OBJECT
  enum NavShowType{
    NAV_SHOW_SINGLE,
    NAV_SHOW_SINGLE_1_4_6,
    NAV_SHOW_MIX
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

  static void processCallBack(void *argv,short *value);

  bool deviceInit();
  void navigationTreeInit();
  void globalUiPageInit();
  void stackedWidgetInit();
signals:
  void initProgressInfo(int barValue,QString msg);
private slots:
  void onActnOptionClicked();

  //响应option选项slots
  void onOptAutoLoadChanged(bool changed);
  void onOptFaceCssChanged(QString css);

  void onProgressInfo(int barValue, QString msg);

  void onNavTreeWidgetItemClicked(QTreeWidgetItem * item, int column);

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

  static short m_probarValue;

  //-------servo-------
  QList<SdAssembly*>m_sdAssemblyList;
  IUiControler *m_gUiControl;
  OptContainer *m_optc;
  SdAssembly *m_currentSdAssembly;

};

#endif // SDTMAINWINDOW_H
