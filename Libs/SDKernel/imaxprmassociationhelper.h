#ifndef IMAXPRMASSOCIATIONHELPER_H
#define IMAXPRMASSOCIATIONHELPER_H

#include <QObject>
class SevDevice;
class QTreeWidget;

class ImaxPrmAssociationHelper : public QObject
{
  Q_OBJECT


public:
  explicit ImaxPrmAssociationHelper(SevDevice *sev ,QObject *parent = 0);
  ~ImaxPrmAssociationHelper();

  bool active(quint16 axisInx);

private:
  double readImaxValueFromDevice(quint16 axisInx, QString type, quint16 imaxOffset);
  bool writeIxDataToFlash(quint16 axisInx, QString type, quint16 offst, quint64 value);

signals:

public slots:
private:
  SevDevice *m_sev;
  QTreeWidget *m_motorTree;
};

#endif // IMAXPRMASSOCIATIONHELPER_H
