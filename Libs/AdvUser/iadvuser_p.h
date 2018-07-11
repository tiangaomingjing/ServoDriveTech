#ifndef IADVUSER_P
#define IADVUSER_P

#include <QObject>
#include "sdassembly.h"
class IAdvUser;

class IAdvUserPrivate {
    Q_DECLARE_PUBLIC(IAdvUser)
public:
    IAdvUserPrivate();
    virtual ~IAdvUserPrivate();
    IAdvUser *q_ptr;
    bool m_isModify;
    QString m_name;
    static QString m_usrPath;
};

#endif // IADVUSER_P

