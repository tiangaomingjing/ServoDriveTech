#include "kuselectwidget133.h"
#include "ui_kuselectwidget133.h"
#include <QStyledItemDelegate>



KuSelectWidget133::KuSelectWidget133(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::KuSelectWidget133)
{
  ui->setupUi(this);
  QStyledItemDelegate* itemDelegate = new QStyledItemDelegate(ui->comboBox);
  ui->comboBox->setItemDelegate(itemDelegate);

  connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(onComboBoxIndexChanged(int)));
}

KuSelectWidget133::~KuSelectWidget133()
{
  delete ui;
}

QDoubleSpinBox *KuSelectWidget133::boxKu1()
{
  return ui->doubleSpinBox_ku1;
}

QDoubleSpinBox *KuSelectWidget133::boxKu2()
{
  return ui->doubleSpinBox_ku2;
}

QDoubleSpinBox *KuSelectWidget133::boxTs()
{
  return ui->doubleSpinBox_ts;
}

QDoubleSpinBox *KuSelectWidget133::boxSpdu()
{
  return ui->doubleSpinBox_spdu;
}

QDoubleSpinBox *KuSelectWidget133::boxSpdl()
{
  return ui->doubleSpinBox_spdl;
}

void KuSelectWidget133::setKuModeUi(int index)
{
  switch (index) {
  case 0:
    ui->line->setVisible(false);
    ui->label_ku2->setVisible(false);
    ui->label_ts->setVisible(false);
    ui->label_spdl->setVisible(false);
    ui->label_spdu->setVisible(false);
    ui->doubleSpinBox_ku2->setVisible(false);
    ui->doubleSpinBox_spdl->setVisible(false);
    ui->doubleSpinBox_spdu->setVisible(false);
    ui->doubleSpinBox_ts->setVisible(false);
    break;
  case 1:
  case 2:
    ui->line->setVisible(true);
    ui->label_ku2->setVisible(true);
    ui->label_ts->setVisible(true);
    ui->label_spdl->setVisible(true);
    ui->label_spdu->setVisible(true);
    ui->doubleSpinBox_ku2->setVisible(true);
    ui->doubleSpinBox_spdl->setVisible(true);
    ui->doubleSpinBox_spdu->setVisible(true);
    ui->doubleSpinBox_ts->setVisible(true);
    break;
  default:
    ui->line->setVisible(false);
    ui->label_ku2->setVisible(false);
    ui->label_ts->setVisible(false);
    ui->label_spdl->setVisible(false);
    ui->label_spdu->setVisible(false);
    ui->doubleSpinBox_ku2->setVisible(false);
    ui->doubleSpinBox_spdl->setVisible(false);
    ui->doubleSpinBox_spdu->setVisible(false);
    ui->doubleSpinBox_ts->setVisible(false);
    break;
  }
  ui->comboBox->setCurrentIndex(index);
}

void KuSelectWidget133::onComboBoxIndexChanged(int index)
{
  if(index == -1)
    return ;
  setKuModeUi(index);
  emit kuSwChanged(index);
}
