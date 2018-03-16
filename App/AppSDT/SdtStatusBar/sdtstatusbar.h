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
  enum MsgType{
    MSG_TYPE_NORMAL,
    MSG_TYPE_WARNING,
    MSG_TYPE_ERROR
  };

  explicit SdtStatusBar(QTreeWidget *navTree,QWidget *parent = 0);
  ~SdtStatusBar();
  void resetStatus();
  void setMsg(const QString &str,MsgType type=MSG_TYPE_NORMAL);
  void setConnectStatus(bool connected);
  void setErrorStatus(bool hasError);
  void updateDeviceWhenChanged(QTreeWidget *navTree);
  QProgressBar *statusProgressBar()const;
  void setAlarmErrorStatus(quint32 devInx,qint16 axis,bool hasErr);

signals:
  void statusErr(quint32 devInx,qint16 axis,bool hasErr);//由主窗口传入信息给状态栏
  void statusPageChanged(int pIndex);//信息连接接力，接m_errDialog传出来的信息
//public slots:
//  void onStatusErr(quint32 devInx,qint16 axis,bool hasErr);
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
