#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include "sdtglobaldef.h"

GT_NAMESPACE_BEGIN

class Utils : public QObject
{
  Q_OBJECT
public:
  explicit Utils(QObject *parent = 0);

signals:

public slots:
};

GT_NAMESPACE_END

#endif // UTILS_H
