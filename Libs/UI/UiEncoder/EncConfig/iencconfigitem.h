#ifndef IENCCONFIGITEM_H
#define IENCCONFIGITEM_H

#include <QObject>

class QWidget;
class IEncConfigItem : public QObject
{
  Q_OBJECT
public:
  enum EncType{
    ENC_TYPE_ABSOLUTE,
    ENC_TYPE_INCREASE,
    ENC_TYPE_NONE
  };
  explicit IEncConfigItem(QObject *parent = 0);
  virtual ~IEncConfigItem();

  virtual QStringList errorStrings(quint16 errorCode);
  virtual bool hasWarnig(quint16 errorCode);
  virtual bool hasLostError(quint16 errorCode);
  virtual void attributeUiInit();
  virtual bool execute();

  EncType encType() const;
  void setEncType(const EncType encType);

  quint16 encConfigData() const;
  void setEncConfigData(const quint16 encConfigData);

  quint32 lineNumber() const;
  void setLineNumber(const quint32 lineNumber);

  QWidget *attributeUi() const;

  void setWarningsString(const QStringList &warnings);

  quint16 lostOper() const;
  void setLostOper(const quint16 lostOper);

  quint16 alarmOper() const;
  void setAlarmOper(const quint16 alarmOper);

  quint16 crcErrOper() const;
  void setCrcErrOper(const quint16 crcErrOper);


signals:

public slots:
protected:
  EncType m_encType;
  quint16 m_encConfigData;
  quint32 m_lineNumber;
  QStringList m_warnings;

  quint16 m_lostOper;
  quint16 m_alarmOper;
  quint16 m_crcErrOper;
  QWidget *m_attributeUi;
};

#endif // IENCCONFIGITEM_H
