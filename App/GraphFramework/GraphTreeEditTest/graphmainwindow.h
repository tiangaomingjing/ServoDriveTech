#ifndef GRAPHMAINWINDOW_H
#define GRAPHMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class GraphMainWindow;
}
class QGraphicsScene;
class QGraphicsView;

class GraphMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit GraphMainWindow(QWidget *parent = 0);
  ~GraphMainWindow();

private:
  Ui::GraphMainWindow *ui;
  QGraphicsScene *m_scene;
  QGraphicsView *m_view;
};

#endif // GRAPHMAINWINDOW_H
