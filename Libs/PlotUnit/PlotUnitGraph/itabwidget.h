#ifndef ITABWIDGET_H
#define ITABWIDGET_H

#include <QWidget>
class SevDevice;

class ITabWidget : public QWidget
{
  Q_OBJECT
public:
  explicit ITabWidget(const QString &name,SevDevice *sev,QWidget *parent = 0);
  virtual ~ITabWidget(){}

  QString name() const;
  void setName(const QString &name);

  int axisCount() const;
  void setAxisCount(int axisCount);

  SevDevice *sevDevice() const;
  void setSevDevice(SevDevice *sevDevice);

  virtual void uiUpdate() = 0 ;
  virtual void resetUi() = 0;

signals:

public slots:

protected:
  QString m_name;
  int m_axisCount;
  SevDevice *m_sev;
};

#endif // ITABWIDGET_H
