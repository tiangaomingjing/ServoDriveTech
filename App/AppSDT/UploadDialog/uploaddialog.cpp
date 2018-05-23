#include "uploaddialog.h"
#include "ui_uploaddialog.h"
#include "sevdevice.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QDate>

UploadDialog::UploadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UploadDialog)
{
    ui->setupUi(this);
}

UploadDialog::~UploadDialog()
{
    delete ui;
}

void UploadDialog::uiInit(QList<SevDevice *> &devList, const QString uploadPath)
{
    m_uploadPath = uploadPath;
    for (int i = 0; i < devList.count(); i++) {
        ui->comboBox_devUpload->addItem(devList.at(i)->modelName());
    }
    m_devList = &devList;
    ui->lineEdit_fileUpload->setReadOnly(true);
    connect(ui->toolBtn_upload, SIGNAL(clicked()), this, SLOT(onToolButtonClicked()));
    connect(ui->btn_okUpload, SIGNAL(clicked()), this, SLOT(onOkButtonClicked()));
}

void UploadDialog::onToolButtonClicked()
{
    int index = ui->comboBox_devUpload->currentIndex();
    QDate curDate = QDate::currentDate();
    QString defaultName = m_devList->at(index)->modelName() + "_" + m_devList->at(index)->versionName() + "_" + QString::number(curDate.year()) + QString::number(curDate.month()) + QString::number(curDate.day());
    m_filePath = QFileDialog::getSaveFileName(this, tr("Open XML File"), m_uploadPath + "/" + defaultName + ".xml", tr("XML Files(*.xml)"));
    QFileInfo fileInfo;
    fileInfo.setFile(m_filePath);
    ui->lineEdit_fileUpload->setText(fileInfo.fileName());
}

void UploadDialog::onOkButtonClicked()
{
    int index = ui->comboBox_devUpload->currentIndex();
    emit sendDevAndPath(index, m_filePath);
    this->close();
}
