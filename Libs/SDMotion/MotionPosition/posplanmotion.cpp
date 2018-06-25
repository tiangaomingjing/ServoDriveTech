#include "posplanmotion.h"
#include "uimotionposition.h"
#include "sevdevice.h"
#include "gtutils.h"

PosPlanMotion::PosPlanMotion(quint16 axisInx, SevDevice *dev, UiPosMotionData * data, QObject *parent) :
    QObject(parent),
    m_sev(dev),
    m_data(data),
    m_axisInx(axisInx)
{
    m_timer.setTimerType(Qt::PreciseTimer);
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));
}

PosPlanMotion::~PosPlanMotion()
{

}

QTimer *PosPlanMotion::timer()
{
    return &m_timer;
}

void PosPlanMotion::movePrepare()
{

}

