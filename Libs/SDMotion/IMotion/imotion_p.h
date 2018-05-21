#ifndef IMOTION_P
#define IMOTION_P

#include "imotion.h"

class QWidget;
class SevDevice;
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
};

#endif // IMOTION_P

