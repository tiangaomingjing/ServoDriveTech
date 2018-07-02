#ifndef KUSELECTWIDGET133_H
#define KUSELECTWIDGET133_H

#include <QWidget>

namespace Ui {
class KuSelectWidget133;
}
class QDoubleSpinBox;

class KuSelectWidget133 : public QWidget
{
  Q_OBJECT

public:
  explicit KuSelectWidget133(QWidget *parent = 0);
  ~KuSelectWidget133();

  QDoubleSpinBox *boxKu1();
  QDoubleSpinBox *boxKu2();
  QDoubleSpinBox *boxTs();
  QDoubleSpinBox *boxSpdu();
  QDoubleSpinBox *boxSpdl();

signals:
  void kuSwChanged(int index);

private slots:
  void onComboBoxIndexChanged(int index);

private:
  Ui::KuSelectWidget133 *ui;
};

#endif // KUSELECTWIDGET133_H
