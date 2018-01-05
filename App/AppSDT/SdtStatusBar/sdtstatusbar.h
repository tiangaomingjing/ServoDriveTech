#ifndef SDTSTATUSBAR_H
#define SDTSTATUSBAR_H

#include <QWidget>

namespace Ui {
class SdtStatusBar;
}
class QMenu;
class SDTMainWindow;
class StatusErrDialog;
class QTreeWidget;
class QProgressBar;
class SdtStatusBar : public QWidget
{
  Q_OBJECT

public:
  explicit SdtStatusBar(QTreeWidget *navTree,QWidget *parent = 0);
  ~SdtStatusBar();
  void resetStatus();
  void setWarningMsg(const QString &str);
  void setConnectStatus(bool connected);
  void showErrorStatus(bool show);
  void updateDeviceWhenChanged(QTreeWidget *navTree);//当设备变化后要重新调用，并在生成导航树之后
  QProgressBar *statusProgressBar()const;

signals:
  void statusErr(quint32 devInx,qint16 axis,bool hasErr);//由主窗口传入信息给状态栏
  void statusPageChanged(int pIndex);//信息连接接力，接m_errDialog传出来的信息
private slots:
//  void onActnClickedtest(QAction* act);
  void onActnToolClicked();
//  void onActnToolTrig(QAction *act);
protected:
//  bool eventFilter(QObject *watched, QEvent *event)override;
private:
  Ui::SdtStatusBar *ui;
//  QMenu *m_menu;
  StatusErrDialog *m_errDialog;
};

#endif // SDTSTATUSBAR_H
