#ifndef FORMMAIN_H
#define FORMMAIN_H

#include <QWidget>

namespace Ui {
class FormMain;
}

class FormMain : public QWidget
{
  Q_OBJECT

public:
  explicit FormMain(QWidget *parent = 0);
  ~FormMain();

private:
  Ui::FormMain *ui;
};

#endif // FORMMAIN_H
