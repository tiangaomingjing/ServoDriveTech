#ifndef TABMOTION_H
#define TABMOTION_H

#include <QWidget>

namespace Ui {
class TabMotion;
}

class TabMotion : public QWidget
{
  Q_OBJECT

public:
  explicit TabMotion(QWidget *parent = 0);
  ~TabMotion();

private:
  Ui::TabMotion *ui;
};

#endif // TABMOTION_H
