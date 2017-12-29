#ifndef OPTPLOT_H
#define OPTPLOT_H

#include <QObject>
#include "iopt.h"

namespace Ui {
class OptPlot;
}
class OptPlotPrivate;

class OPTIONSHARED_EXPORT OptPlot : public IOpt
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(OptPlot)
public:
  explicit OptPlot(const QString &optName, QWidget *parent = 0);
  ~OptPlot();
  void uiInit()Q_DECL_OVERRIDE;
protected:
  bool optActive()Q_DECL_OVERRIDE;
  bool readOpt()Q_DECL_OVERRIDE;
  bool writeOpt()Q_DECL_OVERRIDE;
  void respondErrorExecute()Q_DECL_OVERRIDE;

signals:

public slots:
private:
  Ui::OptPlot *ui;
};

#endif // OPTPLOT_H
