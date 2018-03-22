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
    bool loadTree(QString &path, QTreeWidget *treeWidget);
    void compareNode(QTreeWidgetItem *oldNode, QTreeWidgetItem *newNode);
    void eliminateEmptyItem(QTreeWidget* tree);
    void clearEmptyItem(QTreeWidgetItem *item);
    void restoreItemList(QList<QTreeWidgetItem*> list);
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
    void onActionSyncBoxChanged();
};

#endif // COMPARISONDIALOG_H
