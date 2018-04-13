#ifndef PLOTTABCTLPRMS_H
#define PLOTTABCTLPRMS_H

#include <QObject>
#include "sdtglobaldef.h"

class ModeCtlPrms
{
public:
  ModeCtlPrms():m_isChecked(false),
    m_curMode(MODE_IDLE),m_ipa(0),m_uaref(0),m_ubref(0),m_ucref(0),m_udref(0),
    m_uqref(0),m_idref(0),m_iqref(0),m_vcl(0),m_vpl(0),m_vsl(0),m_pt(0)
  {

  }

typedef enum{
    MODE_IDLE,
    MODE_ADC,
    MODE_IPA,
    MODE_MPI,
    MODE_COL,
    MODE_CCL,
    MODE_VCL,
    MODE_VPL,
    MODE_VSL,
    MODE_FIX,
    MODE_PT,
    MODE_DB,
    MODE_CSC
  }ModeCtlType;

  bool m_isChecked;
  ModeCtlType m_curMode;
  //mode ipa
  qreal m_ipa;
  //mode col
  qreal m_uaref;
  qreal m_ubref;
  qreal m_ucref;
  qreal m_udref;
  qreal m_uqref;
  //mode ccl
  qreal m_idref;
  qreal m_iqref;
  //mode vcl
  qreal m_vcl;
  //mode vpl
  qreal m_vpl;
  //mode vsl
  qreal m_vsl;
  //mode pt
  qreal m_pt;
};
class MotionCtlPrms
{
public:
  typedef enum{
    MOTION_SRC_PC,
    MOTION_SRC_GLINK2
  }MotionSource;
  typedef enum{
    MOTION_TYPE_NONE,
    MOTION_TYPE_VEL
  }MotionType;

  bool m_isChecked;
  MotionSource m_src;
  MotionType m_type;

  //motion type vel
  bool m_isCircle;
  qreal m_stepAmp;
  quint16 m_stepTimes;
  qreal m_circleAmp;
  quint16 m_circleT;
  quint16 m_circleCount;

};

class PlotTabCtlPrms
{
public:
  explicit PlotTabCtlPrms(quint16 axisCount):
    m_axisCount(axisCount),
    m_curModeAxis(0),
    m_curMotionAxis(0)
  {
    for(int i=0;i<axisCount;i++)
    {
      ModeCtlPrms *mode=new ModeCtlPrms;
      m_modeCtlPrmsList.append(mode);
      MotionCtlPrms *motion=new MotionCtlPrms;
      m_motionCtlPrmsList.append(motion);
    }
  }
  ~PlotTabCtlPrms()
  {
    GT::deepClearList(m_modeCtlPrmsList);
    GT::deepClearList(m_motionCtlPrmsList);
  }
  quint16 m_axisCount;
  quint16 m_curModeAxis;
  quint16 m_curMotionAxis;

  QList<ModeCtlPrms*>m_modeCtlPrmsList;
  QList<MotionCtlPrms*>m_motionCtlPrmsList;
};
#endif // PLOTTABCTLPRMS

