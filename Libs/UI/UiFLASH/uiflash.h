﻿#ifndef UIFLASH_H
#define UIFLASH_H

#include "uiflash_global.h"
#include "iuiwidget.h"

namespace Ui {
class UiFLASH;
}
class QWidget;
class UiFLASHPrivate;

class UIFLASHSHARED_EXPORT UiFLASH:public IUiWidget
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(UiFLASH)
public:
  explicit UiFLASH(QWidget *parent = 0);
  ~UiFLASH();

  bool readPageFLASH()Q_DECL_OVERRIDE{return true;}
  bool writePageFLASH()Q_DECL_OVERRIDE{return true;}
  void createQmlWidget()Q_DECL_OVERRIDE{}

private:
  QStackedWidget *getUiStackedWidget(void)Q_DECL_OVERRIDE;
  QVBoxLayout *getVBoxLayout(void)Q_DECL_OVERRIDE;
  void setDefaultUi()Q_DECL_OVERRIDE;


private:
  Ui::UiFLASH *ui;
};

#endif // UIFLASH_H
