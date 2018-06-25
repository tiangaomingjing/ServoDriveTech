#include "motionposition.h"

class MotionPositionPrivate:public IMotionPrivate
{
    Q_DECLARE_PUBLIC(MotionPosition)
public:
    MotionPositionPrivate(){}
    ~MotionPositionPrivate(){}
protected:
    QList<VelPlanMotion *> m_velPlanList;

};

MotionPosition::MotionPosition()
{
}
