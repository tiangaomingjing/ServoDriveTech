#ifndef APPXMLRWTEST_H
#define APPXMLRWTEST_H

#include <QMainWindow>
#include <QFileInfo>

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
    char* m_path1;
    char* m_path2;
    char* m_path3;
};

#endif // APPXMLRWTEST_H
