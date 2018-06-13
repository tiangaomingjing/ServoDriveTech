#ifndef NODEEDITMAINWINDOW_H
#define NODEEDITMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class NodeEditMainWindow;
}
class QGraphicsScene;
class NodeEditMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit NodeEditMainWindow(QWidget *parent = 0);
  ~NodeEditMainWindow();

private:
  Ui::NodeEditMainWindow *ui;
  QGraphicsScene *m_scene;
};

#endif // NODEEDITMAINWINDOW_H
