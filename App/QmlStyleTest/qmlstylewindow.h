#ifndef QMLSTYLEWINDOW_H
#define QMLSTYLEWINDOW_H

#include <QMainWindow>

namespace Ui {
class QmlStyleWindow;
}
class QmlStyleHelper;
class QmlStyleWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit QmlStyleWindow(QWidget *parent = 0);
  ~QmlStyleWindow();

private:
  Ui::QmlStyleWindow *ui;
  QmlStyleHelper *m_qmlstyleHelper;
};

#endif // QMLSTYLEWINDOW_H
