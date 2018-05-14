#ifndef ADVUSERCONTAINER_H
#define ADVUSERCONTAINER_H

#include "advuser_global.h"
#include "iadvuser.h"
#include <QObject>
#include <QHash>

class ADVUSERSHARED_EXPORT AdvUserContainer : public QObject
{
    Q_OBJECT
public:
    static AdvUserContainer *instance(QObject *parent = 0);
    ~AdvUserContainer();
    void addAdvUserItem(IAdvUser *adv);
    IAdvUser* advItem(const QString &advName);
    QList<IAdvUser*> advItems();
    void saveAdv();
protected:
    AdvUserContainer(QObject *parent = 0);

signals:

public slots:

private:
    AdvUserContainer(AdvUserContainer &oc);
    static QHash<QString, IAdvUser*> m_advHash;
    static AdvUserContainer *m_instance;
    QList<IAdvUser*> m_advList;
};

#endif // ADVUSERCONTAINER_H
