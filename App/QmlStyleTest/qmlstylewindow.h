#ifndef QMLSTYLEWINDOW_H
#define QMLSTYLEWINDOW_H

#include <QMainWindow>

namespace Ui {
class QmlStyleWindow;
}
class QmlStyleHelper;
class QQuickWidget;
class QmlStyleWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit QmlStyleWindow(QWidget *parent = 0);
  ~QmlStyleWindow();

private slots:
  void on_actionBlueTest_triggered();

  void on_actionBlackTest_triggered();

private:
  Ui::QmlStyleWindow *ui;
  QmlStyleHelper *m_qmlstyleHelper;
  QQuickWidget *m_qw1;
  QQuickWidget *m_qw2;
};

#endif // QMLSTYLEWINDOW_H
