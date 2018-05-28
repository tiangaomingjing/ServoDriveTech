#ifndef IMOTION_P
#define IMOTION_P

#include "imotion.h"
#include <QList>
#include <QVector>

class QWidget;
class SevDevice;
class QListWidget;

class IMotionPrivate
{
  Q_DECLARE_PUBLIC(IMotion)
public:
  IMotionPrivate():m_ui(NULL),
    m_sev(NULL)
  {

  }
  virtual ~IMotionPrivate(){}
protected:
  IMotion *q_ptr;

  QString m_name;
  QWidget *m_ui;
  SevDevice *m_sev;
  IMotion::MotionType m_type;
  int m_curAxis;
  QListWidget *m_axisListWidget;
  QVector<int>m_motionUnFinishVector;
};

#endif // IMOTION_P

