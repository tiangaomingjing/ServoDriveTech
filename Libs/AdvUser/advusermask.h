#ifndef ADVUSERMASK_H
#define ADVUSERMASK_H

#include <QWidget>
#include "iadvuser.h"
#include "sevdevice.h"

namespace Ui {
class AdvUserMask;
}

class AdvUserMaskPrivate;

class ADVUSERSHARED_EXPORT AdvUserMask : public IAdvUser
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(AdvUserMask)

    Q_PROPERTY(QColor flashNodeColor READ flashNodeColor WRITE setFlashNodeColor NOTIFY flashNodeColorChanged)

public:
    explicit AdvUserMask(const QString &usrName, QWidget *parent = 0);
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
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void onItemExpanded(QTreeWidgetItem *item);
    void onTreeItemClickedEdit(QTreeWidgetItem *item, int column);
    void onActionEditFinished();
private:
    Ui::AdvUserMask *ui;
private:
    void modifyItemStructure(QTreeWidgetItem* axisItem, QTreeWidgetItem* targetItem);
    QTreeWidgetItem* findItemInTarget(QTreeWidgetItem* targetItem, const QString &str);
    int findAxisIndex(QTreeWidgetItem* item);
    int findDevIndex(QTreeWidgetItem* item);
    void updateItemData(QTreeWidgetItem *item);
    void writeItem(QTreeWidgetItem *item);
    void readItem(QTreeWidgetItem *item);
    void setItemColor(QTreeWidgetItem *item);
    bool isEditedDataValid(QTreeWidgetItem *item);
};

#endif // ADVUSERMASK_H
