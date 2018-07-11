#ifndef VERATTRIBUTE_H
#define VERATTRIBUTE_H

#include <QObject>
class SevDevice;
class VerAttribute : public QObject
{
  Q_OBJECT
public:
  explicit VerAttribute(QObject *parent = 0);
  ~VerAttribute();
  void setActive(SevDevice*sev);

  bool versionNeedChecked() const;

signals:

public slots:

private:
  bool m_versionNeedChecked;
  bool m_hardIsBigger128;

};

#endif // VERATTRIBUTE_H
