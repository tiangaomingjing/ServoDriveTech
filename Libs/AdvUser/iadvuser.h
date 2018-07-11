#ifndef IADVUSER_H
#define IADVUSER_H

#include "advuser_global.h"
#include "sdassembly.h"

#include <QWidget>

class IAdvUserPrivate;
class QTreeWidgetItem;

class ADVUSERSHARED_EXPORT IAdvUser : public QWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(IAdvUser)
public:
    explicit IAdvUser(const QString &advUserName, QWidget *parent = 0);
    virtual ~IAdvUser();

    QString name();
    virtual QString nickName() = 0;
    bool execute();
    bool saveSettings();
    virtual void uiInit() = 0;

protected:
    IAdvUser(const QString &advUserName, IAdvUserPrivate &dd, QWidget *parent);
    virtual bool advUserActive() = 0;
    virtual bool readAdv() = 0;
    virtual bool writeAdv() = 0;
    virtual void respondErrorExecute() = 0;

    bool isModify();
    void setModify(bool modify);

    void saveDataToFile(const QString &group, const QString &key, const QVariant &value);
    QVariant dataFromFile(const QString &group,const QString &key,const QVariant &defaultValue);
private:

signals:

public slots:

protected:
    IAdvUserPrivate *d_ptr;
};

#endif // IADVUSER_H
