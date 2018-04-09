#include "builderparameters.h"

BuilderParameters::BuilderParameters(const quint32 pwrID, const quint32 ctrID, const QString &version)
{
    m_pwrId = pwrID;
    m_ctrId = ctrID;
    m_version = version;
}

