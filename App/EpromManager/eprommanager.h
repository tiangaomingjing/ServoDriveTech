#ifndef EPROMMANAGER_H
#define EPROMMANAGER_H

#include <QDialog>
#include "eprom_control.h"
#include "eprom_power.h"

class QLabel;
class QTcpSocket;
class TcpConnect;

namespace Ui {
class EpromManager;
}

class EpromManager : public QDialog
{
    Q_OBJECT

public:
    explicit EpromManager(QWidget *parent = 0);
    ~EpromManager();
private:
    Ui::EpromManager *ui;
    void initializeTree();
    com_type getComType();
    void addTreeItem(QTreeWidgetItem *root, QTreeWidgetItem *child, int count);
    void itemClick(QTreeWidgetItem* item, int column, QLabel *label, QString *text, int *lay);
    static void updateProgessBar(void *arg, qint16 *value);
    void setComConnectStatus(bool isConnected);
    bool MessageBoxAsk(QString &msg);
    void showSelectTree();
    void changeConfigText(QString text, QTreeWidget *tree);
    void changeComText();
    void showText(QString configText, QString comText);
    void showTree(QString text, QTreeWidget *tree, QTreeWidget *uiTree);
    void onTextChange(QString text, QTreeWidget *tree);
    void onOkClicked();
    void closeEvent(QCloseEvent *event);
private:
    EPROM *powerBoard;
    EPROM *controlBoard;
    QTreeWidget *powerMap;
    QTreeWidget *controlMap;
    QTreeWidget *powerIndex;
    QTreeWidget *controlIndex;
    QString itemText;
    int m_dspNum;
    int barCount;
    bool m_isOpenCom;
    QString m_filePath;
    QString m_hexPath;
    QString m_xmlPath;
    QString m_powerID;
    QString m_controlID;
    QString m_configText;
    QString m_comText;
    QString m_powerPath;
    QString m_controlPath;
    QString m_typeName;
    QString m_modeName;
    TcpConnect *m_tcpClient;
    bool m_tcpSuccess;

private slots:
    void onWriteClicked();
    void treeItemClicked(QTreeWidgetItem* item, int column);
    void onWriteClicked_2();
    void onBarUpdate();
    void showWarn(QString msg);
    void setBarCount(int value);
    void onReadClicked();
    void onReadClicked_2();
    void onCompareClicked();
    void onCompareClicked_2();
    void onActionConnectClicked();
    void onActionDisConnectClicked();
    void onActionFlashClicked();
    void onLineTextChange(QString text);
    void onLineTextChange_2(QString text);
    void selectHex();
    void selectXml();
    void scrollTree(QTreeWidgetItem* item);
    void scrollTree_2(QTreeWidgetItem* item);
//    void onComButtonClicked();
    
    void receiveConfig(const QStringList &list);
};

#endif // EPROMMANAGER_H
