#ifndef BUILDERPARAMETERS_H
#define BUILDERPARAMETERS_H
#include <QObject>
#include "gtutils_global.h"


class GTUTILSSHARED_EXPORT BuilderParameters
{
public:
    BuilderParameters(const quint32 pwrID, const quint32 ctrID, const QString &version);
    quint32 m_pwrId;
    quint32 m_ctrId;
    QString m_version;
};

#endif // BUILDERPARAMETERS_H
