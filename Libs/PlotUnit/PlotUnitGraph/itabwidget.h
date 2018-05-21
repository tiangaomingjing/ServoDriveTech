#ifndef ITABWIDGET_H
#define ITABWIDGET_H

#include <QWidget>
class SevDevice;

class ITabWidget : public QWidget
{
  Q_OBJECT
public:
  explicit ITabWidget(const QString &name,int axisCount ,SevDevice *sev,QWidget *parent = 0);

  QString name() const;
  void setName(const QString &name);

  int axisCount() const;
  void setAxisCount(int axisCount);

  SevDevice *sevDevice() const;
  void setSevDevice(SevDevice *sevDevice);

  void uiUpdate() = 0 ;

signals:

public slots:
protected:
  QString m_name;
  int m_axisCount;
  SevDevice *m_sevDevice;
};

#endif // ITABWIDGET_H
