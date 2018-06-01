#include "resetdspselectdialog.h"
#include "ui_resetdspselectdialog.h"
#include "sevdevice.h"

#include <QCheckBox>

ResetDspSelectDialog::ResetDspSelectDialog(QList<SevDevice*> *dstSevList,const QList<SevDevice*>&srcSevList, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::ResetDspSelectDialog),
  m_dstSevList(dstSevList),
  m_srcSevList(srcSevList)
{
  ui->setupUi(this);
  SevDevice *sev = NULL;
  for(int i = 0;i<srcSevList.size();i++)
  {
    sev = srcSevList.at(i);
    QCheckBox *box = new QCheckBox(this);
    box->setText(tr("[%1]%2").arg(sev->aliasName()).arg(sev->modelName()));
    box->setChecked(false);
    m_boxList.append(box);
    ui->verticalLayout_selectItem->insertWidget(i,box);
  }
  m_boxList.at(0)->setChecked(true);
  ui->label_resetDspTitle->setText(tr("Select Device:\n"));
  setWindowTitle(tr("Dialog Reset DSP"));
  connect(ui->btn_resetDspOK,SIGNAL(clicked(bool)),this,SLOT(onBtnOkClicked()));
}

ResetDspSelectDialog::~ResetDspSelectDialog()
{
  delete ui;
}

void ResetDspSelectDialog::onBtnOkClicked()
{
  for(int i = 0;i<m_boxList.size();i++)
  {
    if(m_boxList.at(i)->isChecked())
    {
      m_dstSevList->append(m_srcSevList.at(i));
    }
  }
  accept();
}
