#ifndef SDTMAINWINDOW_H
#define SDTMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class SDTMainWindow;
}

class SDTMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit SDTMainWindow(QWidget *parent = 0);
  ~SDTMainWindow();

private:
  void staticUiInit();
  void toolBarOwnInit();
  void createActions();
  void setAppIcon();

private:
  Ui::SDTMainWindow *ui;

  QAction *m_actnDisNet;
  QAction *m_actnDisMode;
  QAction *m_actnConnect;
};

#endif // SDTMAINWINDOW_H
