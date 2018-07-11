#include "downloaddialog.h"
#include "ui_downloaddialog.h"
#include "sevdevice.h"

#include <QFileInfo>
#include <QFileDialog>

DownloadDialog::DownloadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DownloadDialog)
{
    ui->setupUi(this);
}

DownloadDialog::~DownloadDialog()
{
    delete ui;
}

void DownloadDialog::uiInit(const QList<SevDevice *> &devList, const QString &downloadPath, QString &filePath, int &index)
{
    m_downloadPath = downloadPath;
    m_filePath = &filePath;
    m_index = &index;
    for (int i = 0; i < devList.count(); i++) {
        ui->comboBox_devDownload->addItem(devList.at(i)->modelName());
    }
    ui->lineEdit_fileDownload->setReadOnly(true);
    connect(ui->toolBtn_download, SIGNAL(clicked()), this, SLOT(onToolButtonClicked()));
    connect(ui->btn_okDownload, SIGNAL(clicked()), this, SLOT(onOkButtonClicked()));
}

void DownloadDialog::onToolButtonClicked()
{
    *m_filePath = QFileDialog::getOpenFileName(this, tr("Open XML File"), m_downloadPath, tr("XML Files(*.xml)"));
    QFileInfo fileInfo;
    fileInfo.setFile(*m_filePath);
    ui->lineEdit_fileDownload->setText(fileInfo.fileName());
}

void DownloadDialog::onOkButtonClicked()
{
    *m_index = ui->comboBox_devDownload->currentIndex();
    this->close();
}
