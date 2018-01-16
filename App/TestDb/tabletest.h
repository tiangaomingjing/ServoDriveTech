#ifndef TABLETEST_H
#define TABLETEST_H

#include <QDialog>
#include <QGroupBox>
#include <QStackedWidget>
#include <QListWidget>
#include <QMenu>
#include <QCheckBox>

#include "dbmanager.h"
#include "eprom_control.h"
#include "eprom_power.h"

namespace Ui {
class tableTest;
}

class tableTest : public QDialog
{
    Q_OBJECT

public:
    explicit tableTest(QWidget *parent = 0, QString role = "", DBManager *manager = NULL);
    ~tableTest();

private:
    Ui::tableTest *ui;
    void showRoles();
    QString getTitle(QSqlTableModel* model);
    void showWidget(int index);
    void modifyWidgetsAmount(int num);
    //void writeSingle();
    //void writeRelation();
    static void updateProgessBar(void *arg, qint16 *value);
    //void addButtonOnList();
    //QList<QGroupBox *> getGroupList(QWidget *widget);
private slots:    
    void onActionAddClicked();
    //void onActionItemChanged(QListWidgetItem* item);
    //void contextMenuEvent(QContextMenuEvent *event);
    void onActionDeleteTriggered();
    void onActionSupportItemDelete(int index);
    void onActionSupportItemAdd(int index);
    void onActionSupportItemClear();
    void deleteDuplicatedItems(QStringList* strList, QListWidget* supportList);
    //void showListWidgetMenuSlot(QPoint);
    //void onActionAddExistedClicked(int index);
    //void onAdditionReceived(QList<QCheckBox*> boxList, int index, int currentIndex);
    void onActionConfirmClicked();

    void onActionConnectClicked();
    void onActionDisConnectClicked();
    void onActionReadClicked();
    void onActionCheckClicked();
private:
    DBManager *m_dbManager;
    QString m_role;
    QList<QSqlTableModel*> m_modelList;
    EPROM_POWER *powerBoard;
    EPROM_CONTROL *controlBoard;
    bool m_isOpenCom;
    com_type m_type;
};

#endif // TABLETEST_H
