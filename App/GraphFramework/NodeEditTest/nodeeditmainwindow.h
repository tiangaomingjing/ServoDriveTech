#ifndef NODEEDITMAINWINDOW_H
#define NODEEDITMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class NodeEditMainWindow;
}
class QGraphicsScene;

class NodePort;
class NodeLine;
class NodeBlock;
class NodeCornerLine;
class NodeQuadLine;
class NodeSwitch;

class NodeEditMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit NodeEditMainWindow(QWidget *parent = 0);
  ~NodeEditMainWindow();

private slots:
  void on_actionTest_triggered();

  void on_actionTestMove_triggered();

  void on_actionSetFontTest_triggered();

  void on_actionTestDelPort2_triggered();

private:
  Ui::NodeEditMainWindow *ui;
  QGraphicsScene *m_scene;

  NodePort *port1;
  NodePort *port2;
  NodeLine *line;
  NodeBlock *block;
  NodeCornerLine *cornerLine;
  NodeQuadLine *quadLine;
  NodeSwitch *m_switch;
};

#endif // NODEEDITMAINWINDOW_H
