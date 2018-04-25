#ifndef SELFBUILDER_H
#define SELFBUILDER_H

#include <QObject>


#include "builderparameters.h"
#include "gtutils_global.h"
#include "icom.h"

class QTreeWidgetItem;
class SelfBuilderPrivate;

namespace ComDriver {
  class ICom;
}

class GTUTILSSHARED_EXPORT SelfBuilder : public QObject
{
    Q_OBJECT
public:
    typedef enum {
        RTN_SELF_SUCCESS = 0,
        RTN_SELF_READPRODUCTERR = -1,
        RTN_SELF_READSERIESERR = -2,
        RTN_SELF_READAXISERR = -3,
        RTN_SELF_NOPRODUCT = -4,
        RTN_SELF_NEWMODEERR = -5,
        RTN_SELF_WRITETREEERR = -6,
        RTN_SELF_CREATEPATHERR = -7,
        RTN_SELF_COPYERR = -8,
        RTN_SELF_CREATETREEERR = -9,
        RTN_SELF_READXMLERR = -10,
        RTN_SELF_READTREEERR = -11
    }Rtn_Self;

    SelfBuilder(ComDriver::ICom *com);
    SelfBuilder::Rtn_Self buildFromEprom(void (*processCallback)(void *pbar,short *value), void *processbar, BuilderParameters *parameters);
signals:
    void sendProcessInfo(int value, const QString &msg);
private:
    SelfBuilderPrivate *dd;

private:
    SelfBuilder::Rtn_Self buildPower(void (*processCallback)(void *, short *), void *processbar);
    SelfBuilder::Rtn_Self buildControl();
    SelfBuilder::Rtn_Self initParameters();
    bool idExisted(const QString &id, const QString &path);
    bool versionExisted(const QString &ver, const QString &path);
    bool ctrVerExisted(const QString &ver, const QString &path);
    SelfBuilder::Rtn_Self addModeToIdMap(const QString &id, const QString &path);
    bool createNewModeName(const QString &path);
    bool axisNumExisted(const QString &num, const QString &path);
    QString getNewestVersion(const QString &path);
    bool copyFileToPath(QString sourceDir, QString toDir, bool coverFileIfExist);
    bool copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist);
    SelfBuilder::Rtn_Self addNewDatabase(const QString &id, const QString &path, const QString &indexPath);
    SelfBuilder::Rtn_Self addNewCtrDatabase(const QString &id, const QString &path, const QString &indexPath);
    SelfBuilder::Rtn_Self addIndexTree(const QString &path, const QString &id);
    SelfBuilder::Rtn_Self addSelectTree(const QString &path, const QString &id);
    SelfBuilder::Rtn_Self addDatabaseSelectTree(const QString &path);
    SelfBuilder::Rtn_Self addSysConfig(void (*processCallback)(void *, short *), void *processbar);
    SelfBuilder::Rtn_Self addSystemMap();
    SelfBuilder::Rtn_Self addDatabaseVersion(const QString &id, const QString &path);
    QTreeWidgetItem *addBasicChild(QTreeWidgetItem *item, const QStringList &list);
    QString getOldPath(const QString &indexPath);
    SelfBuilder::Rtn_Self readDataFromEEprom(const QString &path, bool isPwr);
    SelfBuilder::Rtn_Self readTreeData(QTreeWidgetItem *item, bool isPwr);
    SelfBuilder::Rtn_Self changeDocuments(void (*processCallback)(void *, short *), void *processbar, const QString &path);

    bool createNewNode(const QString &path, const QString &id);
    bool createSysPath(const QString &path);
};

#endif // SELFBUILDER_H
