#ifndef SDTSTATUSBAR_H
#define SDTSTATUSBAR_H

#include <QWidget>

namespace Ui {
class SdtStatusBar;
}
class QMenu;
class SdtStatusBar : public QWidget
{
  Q_OBJECT

public:
  explicit SdtStatusBar(QWidget *parent = 0);
  ~SdtStatusBar();
  void resetStatus();
  void setWarningMsg(const QString &str);
private slots:
  void onActnClickedtest(QAction* act);
  void onActnToolClicked();
  void onActnToolTrig(QAction *act);
protected:
  bool eventFilter(QObject *watched, QEvent *event)override;
private:
  Ui::SdtStatusBar *ui;
  QMenu *m_menu;
};

#endif // SDTSTATUSBAR_H
