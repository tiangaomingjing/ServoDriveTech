#ifndef UPLOADDIALOG_H
#define UPLOADDIALOG_H

#include <QDialog>

namespace Ui {
class UploadDialog;
}

class SevDevice;

class UploadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UploadDialog(QWidget *parent = 0);
    ~UploadDialog();
    void uiInit(QList<SevDevice *> &devList, const QString uploadPath);
signals:
    void sendDevAndPath(int, QString);
private slots:
    void onToolButtonClicked();
    void onOkButtonClicked();
private:
    QString m_filePath;
    QString m_uploadPath;
    QList<SevDevice *>* m_devList;
    Ui::UploadDialog *ui;
};

#endif // UPLOADDIALOG_H
