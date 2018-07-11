#ifndef SELFBUILDER_H
#define SELFBUILDER_H

#include <QObject>

#include "gtutils_global.h"
#include "icom.h"

class QTreeWidgetItem;
class SelfBuilderPrivate;

class  BuilderParameters
{
public:
    int m_pwrId;
    int m_ctrId;
    QString m_version;

    explicit BuilderParameters(int pwrID = 0, int ctrID = 0, const QString &version = "V0"):
    m_pwrId(pwrID),
    m_ctrId(ctrID),
    m_version(version)
    {
    }

};

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
        RTN_SELF_READTREEERR = -11,
        RTN_SELF_IDNONEXIST = -12
    }RtnSelf;

    SelfBuilder(ComDriver::ICom *com);
    RtnSelf buildFromEprom(void (*processCallback)(void *pbar,short *value), void *processbar, BuilderParameters *parameters);
signals:
    void sendProcessInfo(int value, const QString &msg);

private:
    RtnSelf buildPower(void (*processCallback)(void *, short *), void *processbar);
    RtnSelf buildControl();
    RtnSelf initParameters();
    bool idExisted(const QString &id, const QString &path);
    bool versionExisted(const QString &ver, const QString &path);
    bool ctrVerExisted(const QString &ver, const QString &path);
    SelfBuilder::RtnSelf addModeToIdMap(const QString &id, const QString &path);
    bool createNewModeName(const QString &path);
    bool axisNumExisted(const QString &num, const QString &path);
    QString getNewestVersion(const QString &path);
    bool copyFileToPath(QString sourceDir, QString toDir, bool coverFileIfExist);
    bool copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist);
    RtnSelf addNewDatabase(const QString &id, const QString &path, const QString &indexPath);
    RtnSelf addNewCtrDatabase(const QString &id, const QString &path, const QString &indexPath);
    RtnSelf addIndexTree(const QString &path, const QString &id);
    RtnSelf addSelectTree(const QString &path, const QString &id);
    RtnSelf addDatabaseSelectTree(const QString &path);
    RtnSelf addSysConfig(void (*processCallback)(void *, short *), void *processbar);
    RtnSelf addSystemMap();
    RtnSelf addDatabaseVersion(const QString &id, const QString &path);
    QTreeWidgetItem *addBasicChild(QTreeWidgetItem *item, const QStringList &list);
    QString getOldPath(const QString &indexPath);
    RtnSelf readDataFromEEprom(const QString &path, bool isPwr);
    RtnSelf readTreeData(QTreeWidgetItem *item, bool isPwr);
    RtnSelf changeDocuments(void (*processCallback)(void *, short *), void *processbar, const QString &path);

    bool createNewNode(const QString &path, const QString &id);
    bool createSysPath(const QString &path);
    int getBaseAddress(const QString indexPath);
    RtnSelf readSingle(QTreeWidgetItem *item, bool isPwr);
private:
    SelfBuilderPrivate *dd;
};

#endif // SELFBUILDER_H
