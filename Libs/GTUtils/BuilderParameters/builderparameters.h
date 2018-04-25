#ifndef BUILDERPARAMETERS_H
#define BUILDERPARAMETERS_H
#include <QObject>
#include "gtutils_global.h"


class BuilderParameters
{

public:
    quint32 m_pwrId;
    quint32 m_ctrId;
    QString m_version;

    BuilderParameters(const quint32 pwrID, const quint32 ctrID, const QString &version):
    m_pwrId(pwrID),
    m_ctrId(ctrID),
    m_version(version)
    {

    }
};

#endif // BUILDERPARAMETERS_H
