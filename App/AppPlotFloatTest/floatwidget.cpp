#include "floatwidget.h"
#include "ui_floatwidget.h"

#include <QLabel>

FloatWidget::FloatWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FloatWidget)
{
  ui->setupUi(this);
  ui->btn_in->setCheckable(true);
  ui->btn_in->setChecked(true);
  QLabel *label=new QLabel(this);
  label->setText("this is float widget");
  connect(ui->btn_in,SIGNAL(clicked(bool)),this,SIGNAL(btnIn(bool)));
}

FloatWidget::~FloatWidget()
{
  delete ui;
}

void FloatWidget::visit(PlotMainWindow *window)
{
  m_window=window;
}


void FloatWidget::on_btn_in_clicked()
{
//  emit btnIn(ui->btn_in->isChecked());
}

void FloatWidget::on_btn_out_clicked()
{

}
