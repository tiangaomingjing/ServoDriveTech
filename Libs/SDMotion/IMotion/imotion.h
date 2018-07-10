#ifndef IMOTION_H
#define IMOTION_H

#include <QObject>
#include "imotion_global.h"

class IMotionPrivate;
class QWidget;
class SevDevice;
class QListWidget;
class OptPlot;
class IMOTIONSHARED_EXPORT IMotion:public QObject
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(IMotion)
public:
  typedef enum{
    MOTION_TYPE_NONE = 0,
    MOTION_TYPE_VEL = 1,
    MOTION_TYPE_POS = 2
  }MotionType;
  virtual ~IMotion();
  virtual void movePrepare(quint16 axisInx) = 0;
  virtual bool move(quint16 axisInx) = 0;
  virtual bool stop(quint16 axisInx) = 0;
  virtual void updateAxisUi(quint16 axisInx) = 0;
    virtual void setMode() = 0;
  QWidget *ui();
  void setName(const QString &name);
  QString name();
  SevDevice *sevDevice();
  void setSevDevice(SevDevice *sev);
  QListWidget *axisListWidget();

  MotionType motionType();
  OptPlot *optPlot();
signals:
  void progressValueChanged(quint16 axisInx,int value);
  void motionFinish(quint16 axisInx);
  void motionAllDone();
protected:
  IMotion(IMotionPrivate&dd,QObject *parent=0);
  IMotionPrivate *d_ptr;
  void setMotionType(MotionType type);
};

class MotionNonePrivate;
class QListWidget;

class IMOTIONSHARED_EXPORT MotionNone:public IMotion
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(MotionNone)
public:
  explicit MotionNone(QListWidget *axisListWidget,SevDevice *sev,const QString &name = "none",QObject *parent = 0);
  ~MotionNone();
  void movePrepare(quint16 axisInx);
  bool move(quint16 axisInx) Q_DECL_OVERRIDE;
  bool stop(quint16 axisInx) Q_DECL_OVERRIDE;
  void updateAxisUi(quint16 axisInx) Q_DECL_OVERRIDE;
};

#endif // IMOTION_H
