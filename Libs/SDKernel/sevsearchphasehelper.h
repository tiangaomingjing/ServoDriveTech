#ifndef SEVSEARCHPHASEHELPER_H
#define SEVSEARCHPHASEHELPER_H

#include <QObject>
#include "sdtglobaldef.h"
#include <QTimer>
class SevDevice;

class SevSearchPhaseHelper : public QObject
{
  Q_OBJECT
public:
  typedef enum {
    IPA_STA_CHECK_SEVON = 0,
    IPA_STA_CHECK_FINISH = 1,
    IPA_STA_DONE = 2
  }IpaSta;
  explicit SevSearchPhaseHelper(SevDevice *sev,quint16 axisInx,QObject *parent = 0);
  ~SevSearchPhaseHelper();

  bool searchPhaseStart(int value);

signals:
  void ipaSearchPhaseInfo(int barValue, const QString &msg);
  void ipaWarningMsg(const QString &msg);
  void ipaDone();

private slots:
  void onTimeOut();
private:
  bool checkIpaFinishFlag();
private:
  SevDevice *m_sev;
  GT::SevControlSrc m_curControlSrc;
  GT::ModeCtlType m_curMode;
  quint16 m_axisInx;
  QTimer m_timer;
  IpaSta m_sta;
  int m_checkSevOnCountUse;
  int m_checkFinishCountUse;
  int m_progressValue;
};

#endif // SEVSEARCHPHASEHELPER_H
