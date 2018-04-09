#ifndef SELFBUILDER_H
#define SELFBUILDER_H

#include <QObject>


#include "builderparameters.h"
#include "gtutils_global.h"
#include "../../Com/Communication/icom.h"

class QTreeWidgetItem;

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
    void buildFromEprom(BuilderParameters *parameters);
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
    void buildPower();
    void buildControl();
    void initParameters();
    bool idExisted(const QString &id, const QString &path);
    bool versionExisted(const QString &ver, const QString &path);
    bool ctrVerExisted(const QString &ver, const QString &path);
    void addModeToIdMap(const QString &id, const QString &path);
    bool createNewModeName(const QString &path);
    bool axisNumExisted(const QString &num, const QString &path);
    QString getNewestVersion(const QString &path);
    bool copyFileToPath(QString sourceDir, QString toDir, bool coverFileIfExist);
    bool copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist);
    bool addNewDatabase(const QString &id, const QString &path, const QString &indexPath);
    bool addNewCtrDatabase(const QString &id, const QString &path, const QString &indexPath);
    void addIndexTree(const QString &path, const QString &id);
    void addSelectTree(const QString &path, const QString &id);
    void addDatabaseSelectTree(const QString &path);
    void addSysConfig();
    void addSystemMap();
    void addDatabaseVersion(const QString &id, const QString &path);
    QTreeWidgetItem *addBasicChild(QTreeWidgetItem *item, const QStringList &list);
    QString getOldPath(const QString &indexPath);
    void readDataFromEEprom(const QString &path, bool isPwr);
    void readTreeData(QTreeWidgetItem *item, bool isPwr);
    void changeDocuments();

    bool createNewNode(const QString &path, const QString &id);
    bool createSysPath(const QString &path);

};

#endif // SELFBUILDER_H
