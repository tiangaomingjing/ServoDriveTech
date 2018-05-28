#ifndef ADVUSERMASK_H
#define ADVUSERMASK_H

#include <QWidget>
#include "iadvuser.h"
#include "sevdevice.h"

namespace Ui {
class AdvUserMask;
}

class AdvUserMaskPrivate;
class AdvMapperIndex;

class ADVUSERSHARED_EXPORT AdvUserMask : public IAdvUser
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(AdvUserMask)

    Q_PROPERTY(QColor flashNodeColor READ flashNodeColor WRITE setFlashNodeColor NOTIFY flashNodeColorChanged)

public:
    explicit AdvUserMask(const QString &advName, QWidget *parent = 0);
    ~AdvUserMask();

    void uiInit() Q_DECL_OVERRIDE;
    void setSevList(const QList<SevDevice*> &list);

    QColor flashNodeColor();
    void setFlashNodeColor(const QColor &nodeColor);
signals:
    void flashNodeColorChanged(QColor &clr);
protected:
    bool advUserActive() Q_DECL_OVERRIDE;
    bool readAdv() Q_DECL_OVERRIDE;
    bool writeAdv() Q_DECL_OVERRIDE;
    void respondErrorExecute() Q_DECL_OVERRIDE;
    void contextMenuEvent(QContextMenuEvent *event);

private slots:
    void onItemExpanded(QTreeWidgetItem *item);
    void onTreeItemClickedEdit(QTreeWidgetItem *item, int column);
    void onRespondErrorExe();
    void onClearAlarmTriggered();
    void onCopySingleAxisTriggered();
    void onCopyAllAxisTriggered();
    void onRefreshTriggered();
private:
    Ui::AdvUserMask *ui;
private:
    void modifyItemStructure(QTreeWidgetItem* axisItem, QTreeWidgetItem* targetItem, SevDevice *dev);
    QTreeWidgetItem* findItemInTarget(QTreeWidgetItem* targetItem, const QString &str);
    int findAxisIndex(QTreeWidgetItem* item);
    int findDevIndex(QTreeWidgetItem* item);
    void updateItemData(QTreeWidgetItem *item);
    void readItem(QTreeWidgetItem *item);
    void setItemColor(QTreeWidgetItem *item);
    bool isAxisItem(QTreeWidgetItem* item);
    bool isDevItem(QTreeWidgetItem* item);
    void calculateItem(QTreeWidgetItem* item);
    void clearLists();
    void setZero(QTreeWidgetItem *item);
    void copyItem(QTreeWidgetItem* originItem, QTreeWidgetItem *targetItem);
};

#endif // ADVUSERMASK_H
