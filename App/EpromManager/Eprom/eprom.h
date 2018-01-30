#ifndef EPROM_H
#define EPROM_H
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QString>
#include "ServoDriverComDll.h"
#include "globaldefine.h"
#include "treemanager.h"

class EPROM : public QObject
{
    Q_OBJECT
public:
    ~EPROM();
    EPROM(QString filePath, int16 com_type);
    void writeFromXmltoEprom(QTreeWidgetItem *writenItem);
    Uint32 readID();
    void readFromEprom(QTreeWidget *tree);
    void compare(QTreeWidget *tree);
    QTreeWidget* getTree();
signals:
    void updateBarCount();
    void changeBarCount(int value);
    void sendWarnMsg(QString msg);
    void sendScrollItem(QTreeWidgetItem *item);
protected:
    int16 m_type;
    QString m_filePath;
    int baseAdd;
    QTreeWidget* m_writeTree;
    QTreeWidget* m_readTree;
    bool m_exist;
    bool continueWrite;
    QTreeWidgetItem* m_wrongItem;
protected:
    void writeEEprom(QTreeWidgetItem *item);
    void writeSingle(QTreeWidgetItem *item);
    virtual int16 writeEprom(int16 axis, Uint16 ofst, Uint8* value, Uint16 num, int16 com_type, int16 stationId) = 0;
    virtual int16 readEprom(int16 axis, Uint16 ofst, Uint8* value, Uint16 num, int16 com_type, int16 stationId) = 0;
    bool writeSuccessful(Uint8* value, Uint8* result, Uint16 num);
    virtual QTreeWidget* createReadTree(Uint32 id) = 0;
    void readEEpromItem(QTreeWidgetItem* readTreeItem, QTreeWidgetItem* uiTreeItem);
    void readSingle(QTreeWidgetItem* readTreeItem, QTreeWidgetItem *uiTreeItem);
    void compareNode(QTreeWidgetItem *oldNode, QTreeWidgetItem *newNode, QTreeWidget *tree);
};

#endif // EPROM_H
