#ifndef FIRMWAREFLASHDIALOG_H
#define FIRMWAREFLASHDIALOG_H

#include <QDialog>

class SevDevice;

namespace Ui {
class FirmwareFlashDialog;
}

class FirmwareFlashDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FirmwareFlashDialog(QList<SevDevice*> &devList, QWidget *parent = 0);
    ~FirmwareFlashDialog();

private:
    void uiInit();
    void createConnections();
    QStringList getFilesFromExt(const QString &fileExt, const QString &filePath, int num);
    QString getFileFromName(const QString &fileName, const QString &filePath);
    bool deleteDir(const QString &path);
    bool downloadHexFile();
    bool downloadRpdFile();
    bool downloadXmlFiles();
    static void processCallBack(void *argv, short *value);
private:
    Ui::FirmwareFlashDialog *ui;
    QString m_filePath;
    QString m_decompressPath;
    QString m_desPath;
    QList<SevDevice*> *m_devList;
private slots:
    void onActnToolbtnClicked();
    void onActnFlashBtnClicked();
};

#endif // FIRMWAREFLASHDIALOG_H
