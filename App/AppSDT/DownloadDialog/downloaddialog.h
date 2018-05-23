#ifndef DOWNLOADDIALOG_H
#define DOWNLOADDIALOG_H

#include <QDialog>

class SevDevice;

namespace Ui {
class DownloadDialog;
}

class DownloadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DownloadDialog(QWidget *parent = 0);
    ~DownloadDialog();
    void uiInit(const QList<SevDevice *> &devList, const QString downloadPath);
signals:
    void sendDevAndPath(int, QString);

private:
    Ui::DownloadDialog *ui;
private slots:
    void onToolButtonClicked();
    void onOkButtonClicked();
private:
    QString m_filePath;
    QString m_downloadPath;
};

#endif // DOWNLOADDIALOG_H
