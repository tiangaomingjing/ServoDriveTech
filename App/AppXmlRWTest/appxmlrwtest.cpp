#include "appxmlrwtest.h"
#include "ui_appxmlrwtest.h"
#include "string.h"
#include "QtTreeManager/qttreemanager.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QProgressBar>
#include <QDebug>
#include <QTreeWidget>

#include "stdafx.h"

int aa = 100;

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
    int16 com_type = GTSD_COM_TYPE_RNNET;
    short ret0 = GTSD_CMD_Open(updateProgessBar, (void*)&aa, com_type);
    qDebug()<<"open ret"<<ret0;
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
    m_path1 = m_fileInfo.filePath();
    //m_path11 = m_fileInfo.absolutePath() + "/new/" + m_fileInfo.fileName();
    m_path11 = m_path1;
}

void AppXmlRWTest::onActionToolButtonClicked_2()
{
    openFile();
    ui->lineEdit_2->setText(m_fileInfo.fileName());
    m_path2 = m_fileInfo.filePath();
    //m_path22 = m_fileInfo.absolutePath() + "/new/" + m_fileInfo.fileName();
    m_path22 = m_path2;
}

void AppXmlRWTest::onActionToolButtonClicked_3()
{
    openFile();
    ui->lineEdit_3->setText(m_fileInfo.fileName());
    m_path3 = m_fileInfo.filePath();
    m_path33 = m_path3;
    //m_path33 = m_fileInfo.absolutePath() + "/new/" + m_fileInfo.fileName();
}

void AppXmlRWTest::onActionWriteClicked()
{

    char* pFileNameList[3];
    int pFileTypeList[3];
    int size = m_path1.size();
    char *p = (char *)malloc(size + 1);
    memset(p, '\0', size + 1);
    memcpy_s(p, size, m_path1.toStdString().c_str(), size);
    pFileNameList[0] = p;


    size = m_path2.size();
    p = (char *)malloc(size + 1);
    memset(p, '\0', size + 1);
    memcpy_s(p, size, m_path2.toStdString().c_str(), size);
    pFileNameList[1] = p;

    size = m_path3.size();
    p = (char *)malloc(size + 1);
    memset(p, '\0', size + 1);
    memcpy_s(p, size, m_path3.toStdString().c_str(), size);
    pFileNameList[2] = p;

    pFileTypeList[0] = 0;
    pFileTypeList[1] = 0;
    pFileTypeList[2] = 0;
    int num = 3;
    int16 axis = 0;
    int16 com_type = GTSD_COM_TYPE_RNNET;
    int16 stationId = 0xf0;
    short count = 0;
//    short ret0 = GTSD_CMD_Open(updateProgessBar, (void*)&aa, com_type);
//    qDebug()<<"open ret"<<ret0;
    qDebug()<<"1"<<pFileNameList[0];
    qDebug()<<"2"<<pFileNameList[1];
    qDebug()<<"3"<<pFileNameList[2];
    short ret = GTSD_CMD_XmlWriteFile(axis, pFileNameList, pFileTypeList, num, updateProgessBar, (void*)&aa, count, com_type, stationId);
    qDebug()<<"write ret"<<ret;

    for(int i = 0; i < num; i++)
    {
        free(pFileNameList[i]);
    }
}

void AppXmlRWTest::onActionReadClicked()
{
    char* pFileNameList[3];
    int pFileTypeList[3];
    int size = m_path11.size();
    char *p = (char *)malloc(size + 1);
    memset(p, '\0', size + 1);
    memcpy_s(p, size, m_path11.toStdString().c_str(), size);
    pFileNameList[0] = p;

    qDebug()<<"m_path1"<<m_path11;

    size = m_path22.size();
    p = (char *)malloc(size + 1);
    memset(p, '\0', size + 1);
    memcpy_s(p, size, m_path22.toStdString().c_str(), size);
    pFileNameList[1] = p;

    size = m_path33.size();
    p = (char *)malloc(size + 1);
    memset(p, '\0', size + 1);
    memcpy_s(p, size, m_path33.toStdString().c_str(), size);
    pFileNameList[2] = p;
    pFileTypeList[0] = 0;
    pFileTypeList[1] = 0;
    pFileTypeList[2] = 0;
    int num = 3;
    int16 axis = 0;
    int16 com_type = GTSD_COM_TYPE_RNNET;
    int16 stationId = 0xf0;
    short count = 0;
    short ret = GTSD_CMD_XmlReadFile(axis, pFileNameList, pFileTypeList, num, updateProgessBar, (void*)&aa, count, com_type, stationId);
    qDebug()<<"read ret"<<ret;

    for(int i = 0; i < num; i++)
    {
        free(pFileNameList[i]);
    }
}

void AppXmlRWTest::closeEvent(QCloseEvent *event)
{
    int16 com_type = GTSD_COM_TYPE_RNNET;
    short ret = GTSD_CMD_Close(com_type);
    qDebug()<<"close ret"<<ret;
}

void AppXmlRWTest::updateProgessBar(void *arg, int16 *value)
{
    //QProgressBar *bar=static_cast<QProgressBar *>(arg);
    int16 v = *value;
    qDebug()<<"value"<<v;
}
