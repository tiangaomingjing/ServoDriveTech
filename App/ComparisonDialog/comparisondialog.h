#ifndef COMPARISONDIALOG_H
#define COMPARISONDIALOG_H

#include <QDialog>
#include <QFileInfo>

class QTreeWidget;
class QTreeWidgetItem;

namespace Ui {
class ComparisonDialog;
}

class ComparisonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ComparisonDialog(QWidget *parent = 0);
    ~ComparisonDialog();
private:
    void initPath();
    bool loadTree(const QString &path, QTreeWidget *treeWidget);
    void compareNode(QTreeWidgetItem *oldNode, QTreeWidgetItem *newNode);
    void eliminateEmptyItem(QTreeWidget* tree);
    void clearEmptyItem(QTreeWidgetItem *item);
    void restoreItemList(QList<QTreeWidgetItem*> list);
    void fillSpaceNode(QTreeWidgetItem *fillItem, QTreeWidgetItem *spaceItem, const QStringList &list);
//    void hideItems(QTreeWidgetItem *item, const QList<QTreeWidgetItem *> &list);
//    bool containChangedItems(QTreeWidgetItem *item, const QList<QTreeWidgetItem *> &list);
//    void showItems(QTreeWidgetItem *item);
private:
    Ui::ComparisonDialog *ui;
    QString m_oldFilePath;
    QString m_newFilePath;
    QFileInfo m_oldFileInfo;
    QFileInfo m_newFileInfo;
    QFileInfo m_saveFileInfo;
    bool m_newLoaded;
    bool m_oldLoaded;
    int m_barCount;
    QList<QTreeWidgetItem*> m_oldItemList;
    QList<QTreeWidgetItem*> m_newItemList;
    QTreeWidgetItem *m_editedItem;
    int m_editedCol;
private slots:
    void onActionOldBtnClicked();
    void onActionNewBtnClicked();
    void onActionCompareClicked();
    void onActionUpdateClicked();
    void onActionSaveClicked();
    void onActionItemDoubleClicked(QTreeWidgetItem* item, int col);
    void onActionEditFinished();
    void onActionItemDoubleClicked_2(QTreeWidgetItem* item, int col);
    void onActionEditFinished_2();
    void onActionSyncBoxChanged();
    void onActionDiffBoxChanged();
    void onTreeItemChanged(QTreeWidgetItem*item, int col);
    void clickOldBtn(const QString &path);
    void clickNewBtn(const QString &path);
};

#endif // COMPARISONDIALOG_H
