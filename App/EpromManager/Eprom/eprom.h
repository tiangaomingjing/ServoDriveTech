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
    bool writeFromXmltoEprom(QTreeWidgetItem *writenItem);
    Uint32 readID();
    bool readFromEprom(QTreeWidget *tree);
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
    int m_baseAdd;
    QTreeWidget* m_writeTree;
    QTreeWidget* m_readTree;
    bool m_exist;
    bool m_continueWrite;
    QTreeWidgetItem* m_wrongItem;
protected:
    bool writeEEprom(QTreeWidgetItem *item);
    bool writeSingle(QTreeWidgetItem *item);
    virtual int16 writeEprom(int16 axis, Uint16 ofst, Uint8* value, Uint16 num, int16 com_type, int16 stationId) = 0;
    virtual int16 readEprom(int16 axis, Uint16 ofst, Uint8* value, Uint16 num, int16 com_type, int16 stationId) = 0;
    bool writeSuccessful(Uint8* value, Uint8* result, Uint16 num);
    virtual QTreeWidget* createReadTree(Uint32 id) = 0;
    virtual int getBaseAddress() = 0;
    bool readEEpromItem(QTreeWidgetItem* readTreeItem, QTreeWidgetItem* uiTreeItem);
    bool readSingle(QTreeWidgetItem* readTreeItem, QTreeWidgetItem *uiTreeItem);
    void compareNode(QTreeWidgetItem *oldNode, QTreeWidgetItem *newNode, QTreeWidget *tree);
};

#endif // EPROM_H
