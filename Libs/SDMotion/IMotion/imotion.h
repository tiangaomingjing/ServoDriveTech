#ifndef IMOTION_H
#define IMOTION_H

#include <QObject>
#include "imotion_global.h"

class IMotionPrivate;
class QWidget;
class SevDevice;
class IMOTIONSHARED_EXPORT IMotion:public QObject
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(IMotion)
public:
  typedef enum{
    MOTION_TYPE_NONE,
    MOTION_TYPE_VEL
  }MotionType;
  virtual ~IMotion();
  virtual bool move(quint16 axisInx) = 0;
  QWidget *ui();
  void setUi(QWidget *ui);
  void setName(const QString &name);
  QString name();
  SevDevice *sevDevice();
  void setSevDevice(SevDevice *sev);
  void setMotionType(MotionType type);
  MotionType motionType();

protected:
  IMotion(IMotionPrivate&dd,QObject *parent=0);
  IMotionPrivate *d_ptr;
};

class MotionNonePrivate;

class IMOTIONSHARED_EXPORT MotionNone:public IMotion
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(MotionNone)
public:
  explicit MotionNone(SevDevice *sev ,MotionType type = MOTION_TYPE_NONE,const QString &name = "none",QObject *parent = 0);
  bool move(quint16 axisInx) Q_DECL_OVERRIDE;
};

#endif // IMOTION_H
