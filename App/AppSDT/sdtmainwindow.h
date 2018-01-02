#ifndef SDTMAINWINDOW_H
#define SDTMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class SDTMainWindow;
}
class QToolButton;
class SDTMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit SDTMainWindow(QWidget *parent = 0);
  ~SDTMainWindow();

private:
  void staticUiInit();
  void createActions();
  void setAppIcon();
  void closeEvent(QCloseEvent *e)override;

private slots:
  void onActnOptionClicked();

  //响应option选项slots
  void onOptAutoLoadChanged(bool changed);
  void onOptFaceCssChanged(QString css);

private:
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
};

#endif // SDTMAINWINDOW_H
