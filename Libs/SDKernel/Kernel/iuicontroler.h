#ifndef IUICONTROLER_H
#define IUICONTROLER_H

#include <QObject>
class GlobalConfig;

class SevDevice;
class IUiWidget;
class IUiControler : public QObject
{
  Q_OBJECT
public:
  explicit IUiControler(GlobalConfig *gconfig,QObject *parent=0);
  virtual ~IUiControler();
  virtual void createUis()=0;
  quint16 uiCount();
  IUiWidget* uiAt(quint8 index);

signals:
  void initProgressInfo(int value,QString msg);
public slots:
protected:
  GlobalConfig *m_gConfig;
  QList<IUiWidget*>m_uiLists;
};

#endif // IUICONTROLER_H
