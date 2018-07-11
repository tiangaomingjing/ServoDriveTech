#ifndef APPXMLRWTEST_H
#define APPXMLRWTEST_H

#include <QMainWindow>
#include <QFileInfo>
#include "ServoDriverComDll.h"

namespace Ui {
class AppXmlRWTest;
}

class AppXmlRWTest : public QMainWindow
{
    Q_OBJECT

public:
    explicit AppXmlRWTest(QWidget *parent = 0);
    ~AppXmlRWTest();
private:
    void openFile();
    static void updateProgessBar(void *arg, int16 *value);
private slots:
    void onActionToolButtonClicked();
    void onActionToolButtonClicked_2();
    void onActionToolButtonClicked_3();
    void onActionWriteClicked();
    void onActionReadClicked();
private:
    Ui::AppXmlRWTest *ui;
    QString m_filePath;
    QFileInfo m_fileInfo;
    QString m_path1;
    QString m_path2;
    QString m_path3;
    QString m_path11;
    QString m_path22;
    QString m_path33;
    quint32 getOperationValue(int start, int length);
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // APPXMLRWTEST_H
