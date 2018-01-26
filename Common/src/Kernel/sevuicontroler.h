#ifndef SEVUICONTROLER_H
#define SEVUICONTROLER_H

#include "iuicontroler.h"

class OptContainer;
class IUiWidget;
class QTranslator;
class SevUiControler : public IUiControler
{
  Q_OBJECT
public:
  explicit SevUiControler(SevDevice *sev,QObject *parent=0);
  ~SevUiControler();
  void createUis()Q_DECL_OVERRIDE;
  IUiWidget *uiWidget(quint32 devInx,qint16 axisInx,const QString &uiName) const;

signals:

public slots:

private:
  void setTransLanguage();
  void clearTransLanguage();
private:
  SevDevice *m_sev;
  QList<QTranslator*>m_transList;
};

#endif // SEVUICONTROLER_H
