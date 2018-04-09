#include "appxmlrwtest.h"
#include "ui_appxmlrwtest.h"
#include "ServoDriverComDll.h"

#include <QMessageBox>
#include <QFileDialog>

AppXmlRWTest::AppXmlRWTest(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AppXmlRWTest)
{
    ui->setupUi(this);
    m_filePath = ".";

    connect(ui->toolButton, SIGNAL(clicked()), this, SLOT(onActionToolButtonClicked()));
    connect(ui->toolButton_2, SIGNAL(clicked()), this, SLOT(onActionToolButtonClicked_2()));
    connect(ui->toolButton_3, SIGNAL(clicked()), this, SLOT(onActionToolButtonClicked_3()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(onActionWriteClicked()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(onActionReadClicked()));

}

AppXmlRWTest::~AppXmlRWTest()
{
    delete ui;
}

void AppXmlRWTest::openFile() {
    QString path = QFileDialog::getOpenFileName(NULL, tr("Open File"),
                                                m_filePath, tr("XML Files(*.xml)"));
    if (!path.isNull()) {
        m_fileInfo.setFile(path);
        m_filePath = m_fileInfo.filePath() + "/";
    } else {
        QMessageBox::information(this, tr("Path"), tr("You didn't select any files."));
    }
}

void AppXmlRWTest::onActionToolButtonClicked()
{
    openFile();
    ui->lineEdit->setText(m_fileInfo.fileName());
    m_path1 = m_fileInfo.filePath().toLatin1().data();
}

void AppXmlRWTest::onActionToolButtonClicked_2()
{
    openFile();
    ui->lineEdit_2->setText(m_fileInfo.fileName());
    m_path2 = m_fileInfo.filePath().toLatin1().data();
}

void AppXmlRWTest::onActionToolButtonClicked_3()
{
    openFile();
    ui->lineEdit_3->setText(m_fileInfo.fileName());
    m_path3 = m_fileInfo.filePath().toLatin1().data();
}

void AppXmlRWTest::onActionWriteClicked()
{

}

void AppXmlRWTest::onActionReadClicked()
{

}
