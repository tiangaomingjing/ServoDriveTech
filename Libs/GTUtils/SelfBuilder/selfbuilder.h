#ifndef SELFBUILDER_H
#define SELFBUILDER_H

#include <QObject>


#include "builderparameters.h"
#include "gtutils_global.h"
#include "icom.h"

class QTreeWidgetItem;

enum SELFBUILDER_RTN{
    SELFBUILDER_SUCCESS = 0,
    SELFBUILDER_READPRODUCTERR = -1,
    SELFBUILDER_READSERIESERR = -2,
    SELFBUILDER_READAXISERR = -3,
    SELFBUILDER_NOPRODUCT = -4,
    SELFBUILDER_NEWMODEERR = -5,
    SELFBUILDER_WRITETREEERR = -6,
    SELFBUILDER_CREATEPATHERR = -7,
    SELFBUILDER_COPYERR = -8,
    SELFBUILDER_CREATETREEERR = -9,
    SELFBUILDER_READXMLERR = -10,
    SELFBUILDER_READTREEERR = -11
};

enum IDMAP {
    IDMAP_ID = 0,
    IDMAP_TYPE = 1,
    IDMAP_MODE = 2,
    IDMAP_NICK = 3,
    IDMAP_AXISNUM = 4
};

enum CONFIGTREE {
    CONFIG_NAME = 0,
    CONFIG_PARAMETER = 1,
    CONFIG_ID = 2,
    CONFIG_PRMEX = 3
};

enum INDEXTREE {
    INDEX_NAME = 0,
    INDEX_VALUE = 1
};

enum TREE{
    TREE_NAME = 0,
    TREE_VALUE = 1,
    TREE_SCALE = 3,
    TREE_TYPE = 5,
    TREE_ADDRESS = 6,
};

namespace ComDriver {
  class ICom;
}

class GTUTILSSHARED_EXPORT SelfBuilder
{
public:
    SelfBuilder(ComDriver::ICom *com);
    SELFBUILDER_RTN buildFromEprom(void (*processCallback)(void *pbar,short *value), void *processbar, BuilderParameters *parameters);
private:
    QString m_modeName;
    QString m_typeName;
    int m_axisNum;
    QString m_product;
    QString m_series;
    QString m_powerID;
    QString m_controlID;
    QString m_version;
    ComDriver::ICom *m_com;
    ComDriver::IComType m_type;
    QString m_newestMode;
    QString m_newestType;
    QString m_newestID;
    QString m_newestVersion;
    bool m_modeCreated;
private:
    SELFBUILDER_RTN buildPower(void (*processCallback)(void *, short *), void *processbar);
    SELFBUILDER_RTN buildControl();
    SELFBUILDER_RTN initParameters();
    bool idExisted(const QString &id, const QString &path);
    bool versionExisted(const QString &ver, const QString &path);
    bool ctrVerExisted(const QString &ver, const QString &path);
    SELFBUILDER_RTN addModeToIdMap(const QString &id, const QString &path);
    bool createNewModeName(const QString &path);
    bool axisNumExisted(const QString &num, const QString &path);
    QString getNewestVersion(const QString &path);
    bool copyFileToPath(QString sourceDir, QString toDir, bool coverFileIfExist);
    bool copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist);
    SELFBUILDER_RTN addNewDatabase(const QString &id, const QString &path, const QString &indexPath);
    SELFBUILDER_RTN addNewCtrDatabase(const QString &id, const QString &path, const QString &indexPath);
    SELFBUILDER_RTN addIndexTree(const QString &path, const QString &id);
    SELFBUILDER_RTN addSelectTree(const QString &path, const QString &id);
    SELFBUILDER_RTN addDatabaseSelectTree(const QString &path);
    SELFBUILDER_RTN addSysConfig(void (*processCallback)(void *, short *), void *processbar);
    SELFBUILDER_RTN addSystemMap();
    SELFBUILDER_RTN addDatabaseVersion(const QString &id, const QString &path);
    QTreeWidgetItem *addBasicChild(QTreeWidgetItem *item, const QStringList &list);
    QString getOldPath(const QString &indexPath);
    SELFBUILDER_RTN readDataFromEEprom(const QString &path, bool isPwr);
    SELFBUILDER_RTN readTreeData(QTreeWidgetItem *item, bool isPwr);
    SELFBUILDER_RTN changeDocuments(void (*processCallback)(void *, short *), void *processbar, const QString &path);

    bool createNewNode(const QString &path, const QString &id);
    bool createSysPath(const QString &path);

    static void updateProgessBar(void *arg, short *value);
};

#endif // SELFBUILDER_H
