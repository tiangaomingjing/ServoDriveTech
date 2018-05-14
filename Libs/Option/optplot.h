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

  quint16 delayTime();
  double xStoreTime();
  double xDisplayTime();
  double yMax();
  double yMin();
  double storedTime();
  quint16 pointNum();
  QString plotColor();
protected:
  bool optActive()Q_DECL_OVERRIDE;
  bool readOpt()Q_DECL_OVERRIDE;
  bool writeOpt()Q_DECL_OVERRIDE;
  void respondErrorExecute()Q_DECL_OVERRIDE;

signals:
    void plotParametersChanged();
public slots:
private:
  Ui::OptPlot *ui;
private slots:
  void valueModified();
};

#endif // OPTPLOT_H
