#ifndef SEVDSPMAP_H
#define SEVDSPMAP_H
#include "idspmap.h"

class SevDspMap:public IDspMap
{
  Q_OBJECT
public:
  explicit SevDspMap(SevDevicePrivate *sev,QObject *parent=0);
  ~SevDspMap();
  bool initTreeMap()Q_DECL_OVERRIDE;
signals:
  void initProgressInfo(int value,QString msg);
};

#endif // SEVDSPMAP_H
