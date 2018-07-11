#ifndef RESETDSPSELECTDIALOG_H
#define RESETDSPSELECTDIALOG_H

#include <QDialog>

namespace Ui {
class ResetDspSelectDialog;
}
class SevDevice;
class QCheckBox;

class ResetDspSelectDialog : public QDialog
{
  Q_OBJECT

public:
  explicit ResetDspSelectDialog(QList<SevDevice*> *dstSevList,const QList<SevDevice*>&srcSevList,QWidget *parent = 0);
  ~ResetDspSelectDialog();
private slots:
  void onBtnOkClicked();

private:
  Ui::ResetDspSelectDialog *ui;
  QList<QCheckBox *>m_boxList;
  QList<SevDevice*> *m_dstSevList;
  QList<SevDevice*> m_srcSevList;
};

#endif // RESETDSPSELECTDIALOG_H
