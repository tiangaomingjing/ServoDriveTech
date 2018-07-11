#ifndef SERVOFILE_H
#define SERVOFILE_H

#include <QObject>
#include <QDir>

class SevDevice;
class QTreeWidget;
class QTreeWidgetItem;

class ServoFile : public QObject
{
    Q_OBJECT
public:
    explicit ServoFile(QObject *parent = 0);
    bool downLoadFile(void (*processCallback)(void *pbar,short *value), void *processbar, const QString &xmlPath, SevDevice *dev);
    bool upLoadFile(void (*processCallback)(void *pbar,short *value), void *processbar, const QString &xmlPath, SevDevice *dev);

signals:
    void sendProgressbarMsg(int, QString);
public slots:
private:
    //void updatePrmTree(QTreeWidget *downloadTree, QTreeWidget *dspTree);
    void updatePrmTreeItem(QTreeWidgetItem *downloadItem, QTreeWidgetItem *dspItem);
    bool downloadItem(SevDevice *dev, int axisIndex, QTreeWidgetItem *item);
    bool uploadItem(SevDevice *dev, int axisIndex, QTreeWidgetItem *item);
    bool readXmlFromDsp(void (*processCallback)(void *pbar,short *value), void *processbar, const QString &path, SevDevice *dev);
    bool deleteDir(const QString &path);
    bool isFileExist(const QString &fileName);
    int getItemNum(QTreeWidget *tree);
private:
    int m_barCount;
    int m_downloadItemNum;
    int m_uploadItemNum;
};

#endif // SERVOFILE_H
