#ifndef GRAPHBRAKE_P_H
#define GRAPHBRAKE_P_H
#include "graphbrake.h"
#include "igraph_p.h"
class GraphBrakePrivate:IGraphPrivate
{
  Q_DECLARE_PUBLIC(GraphBrake)
public:
  GraphBrakePrivate(){}
  virtual ~GraphBrakePrivate(){}
protected:

};

#endif // GRAPHBRAKE_P_H

