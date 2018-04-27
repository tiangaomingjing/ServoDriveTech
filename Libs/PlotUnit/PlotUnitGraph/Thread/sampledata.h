#ifndef SAMPLEDATA
#define SAMPLEDATA

#include "comglobal.h"
#include <QDebug>

class SampleData{
public:
  SampleData()
  {
    qDebug()<<"------------ sample data construct --------";
  }

  int devId;
  int dspId;
  ComDriver::CurveList curves;
};

#endif // SAMPLEDATA

