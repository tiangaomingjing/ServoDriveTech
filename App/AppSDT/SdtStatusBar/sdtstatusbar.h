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

signals:
  void statusErr(quint32 devInx,qint16 axis,bool hasErr);
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
