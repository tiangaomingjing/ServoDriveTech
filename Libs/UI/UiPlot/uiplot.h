#ifndef UIPLOT_H
#define UIPLOT_H

#include "uiplot_global.h"
#include "iuiwidget.h"

namespace Ui {
class UiPlot;
}
class QWidget;
class UiPlotPrivate;
class QHBoxLayout;
class UIPLOTSHARED_EXPORT UiPlot:public IUiWidget
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(UiPlot)
public:
  explicit UiPlot(QWidget *parent = 0);
  ~UiPlot();

  void accept(QWidget*w) Q_DECL_OVERRIDE;
  bool readPageFLASH()Q_DECL_OVERRIDE{return true;}
  bool writePageFLASH()Q_DECL_OVERRIDE{return true;}
  QHBoxLayout *hBoxLayout();
  bool hasConfigFunc() {return false;}
  bool hasSaveFunc() {return false;}

private slots:
  void onWinFloatChanged(bool isIn);

private:
    QStackedWidget *getUiStackedWidget(void)Q_DECL_OVERRIDE;
    QVBoxLayout *getVBoxLayout(void)Q_DECL_OVERRIDE;
    void setDefaultUi()Q_DECL_OVERRIDE;


private:
  Ui::UiPlot *ui;
};

#endif // UIPLOT_H
