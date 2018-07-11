
#ifndef IGRAPHSTATUS_H
#define IGRAPHSTATUS_H

#include <QWidget>
#include "iuiwidget_global.h"
#include "igraph.h"

class IGraphStatusPrivate;
class IUiWidget;
class QVBoxLayout;

class IUIWIDGETSHARED_EXPORT IGraphStatus : public IGraph
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(IGraphStatus)
public:
//  explicit IGraphStatus(QWidget *parent = 0);
  virtual ~IGraphStatus();
  void visit(IUiWidget *uiWidget) Q_DECL_OVERRIDE;
  void setTimerActive(bool active);

protected:
  virtual void setUiVersionName()Q_DECL_OVERRIDE =0;
  virtual void setCustomVisitActive(IUiWidget*uiWidget);
  virtual void setupDataMappings()=0;
  virtual void syncTreeDataToUiFace();

  virtual void setDeviceStatusIconByCss(const QString &css)=0;
  virtual QWidget *alarmBackgroundWidget()=0;
  virtual void addLedErrorToUi()=0;
  virtual quint32 alarmCode()=0;
  virtual bool hasError()=0;
  virtual void updateUiLabelText()=0;



signals:

public slots:

protected slots:
  virtual void onFaceCssChanged(const QString &css);
  virtual void onTimeOut();

private:
  void addAlarmLedsToWidget(IUiWidget *uiWidget);
  void addLedErrorTitle();
protected:
  IGraphStatus(IGraphStatusPrivate&dd, QWidget *parent=0);

};

#endif // IGRAPHSTATUS_H
