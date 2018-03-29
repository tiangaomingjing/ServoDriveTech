#ifndef FLOATWIDGET_H
#define FLOATWIDGET_H

#include <QWidget>

namespace Ui {
class FloatWidget;
}

class PlotMainWindow;
class FloatWidget : public QWidget
{
  Q_OBJECT

public:
  explicit FloatWidget(QWidget *parent = 0);
  ~FloatWidget();

  void visit(PlotMainWindow *window);


private slots:
  void on_btn_in_clicked();

  void on_btn_out_clicked();

signals:
  void btnIn(bool in);

private:
  Ui::FloatWidget *ui;
  PlotMainWindow *m_window;
};

#endif // FLOATWIDGET_H
