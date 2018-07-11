#include "optpath.h"
#include "ui_optpath.h"
#include "iopt_p.h"
#include <QDebug>
#include <QFile>
#include <QLabel>
#include <QLineEdit>
#include <QToolButton>
#include <QLayout>
#include <QSignalMapper>
#include <QFileDialog>
#include <QMap>

class OptPathPrivate: public IOptPrivate {
    Q_DECLARE_PUBLIC(OptPath)
    public:
      OptPathPrivate();
      ~OptPathPrivate();
      QStringList m_pathList;
      QStringList m_nameList;
      QMap<QString, QString> m_map;
};

OptPathPrivate::OptPathPrivate()
{

}

OptPathPrivate::~OptPathPrivate()
{

}

OptPath::OptPath(const QString &optName, QWidget *parent) : IOpt(optName,*new OptPathPrivate,parent),
    ui(new Ui::OptPath)
{
    Q_D(OptPath);
    ui->setupUi(this);
    initMap();
    readOpt();
    QString fileName = d->m_optPath + "path/path.ini";
    QFile file(fileName);
    if(file.open(QFile::ReadOnly))
    {
      QTextStream in(&file);
      QString s;
      while (!in.atEnd()) {
        s=in.readLine();
        d->m_nameList.append(s);
      }
      d->m_nameList.removeAll("");
      file.close();
    }
//    while(ui->verticalLayout->count()) {
//        ui->verticalLayout->removeItem(ui->verticalLayout->itemAt(0));
//    }
    QSignalMapper *pMapper = new QSignalMapper();
    for (int i = 0; i < d->m_nameList.count(); i++) {
        QVBoxLayout *vBox = new QVBoxLayout;
        QHBoxLayout *hBox = new QHBoxLayout;
        QLabel* label = new QLabel(d->m_map.value(d->m_nameList.at(i)));
        QToolButton* toolButton = new QToolButton;
        QLineEdit* lineEdit = new QLineEdit;
        lineEdit->setReadOnly(true);
        hBox->addWidget(lineEdit);
        hBox->addWidget(toolButton);
        vBox->addWidget(label);
        vBox->addLayout(hBox);
        ui->verticalLayout->addLayout(vBox);
        connect(toolButton, SIGNAL(clicked()), pMapper, SLOT(map()));
        pMapper->setMapping(toolButton, i);
    }
    connect(pMapper, SIGNAL(mapped(int)), this, SLOT(onActionToolButtonClicked(int)));
    uiInit();
}

OptPath::~OptPath()
{
    delete ui;
}

void OptPath::uiInit()
{
    Q_D(OptPath);
    for (int i = 0; i < d->m_pathList.count(); i++) {
        QWidget *lineWidget = ui->verticalLayout->itemAt(i)->layout()->itemAt(1)->layout()->itemAt(0)->widget();
        QLineEdit *lineEdit = static_cast<QLineEdit*>(lineWidget);
        lineEdit->setText(d->m_pathList.at(i));
    }
    qDebug()<< "path ui Init";
}

QString OptPath::servo2FilePath()
{
    Q_D(OptPath);
    return d->m_pathList.at(0);
}

QString OptPath::file2ServoPath()
{
    Q_D(OptPath);
    return d->m_pathList.at(1);
}

QString OptPath::flashFilePath()
{
    Q_D(OptPath);
    return d->m_pathList.at(2);
}

QString OptPath::oldFilePath()
{
    Q_D(OptPath);
    return d->m_pathList.at(3);
}

QString OptPath::newFilePath()
{
    Q_D(OptPath);
    return d->m_pathList.at(4);
}

QString OptPath::curvePath()
{
    Q_D(OptPath);
    return d->m_pathList.at(5);
}

QString OptPath::nickName()
{
    return tr("Path");
}

bool OptPath::optActive()
{
    Q_D(OptPath);
  qDebug()<<"opt path execute active ";
  for (int i = 0; i < d->m_pathList.count(); i++) {
      QWidget *lineWidget = ui->verticalLayout->itemAt(i)->layout()->itemAt(1)->layout()->itemAt(0)->widget();
      QLineEdit *lineEdit = static_cast<QLineEdit*>(lineWidget);
      d->m_pathList.replace(i, lineEdit->text());
  }
  emit pathesChanged(d->m_pathList);
  return true;
}
bool OptPath::readOpt()
{
  Q_D(OptPath);
    QString tempPath;
    tempPath = data("path", "servo2file", "").toString();
    d->m_pathList.append(tempPath);
    tempPath = data("path", "file2servo", "").toString();
    d->m_pathList.append(tempPath);
    tempPath = data("path", "flashfilepath", "").toString();
    d->m_pathList.append(tempPath);
    tempPath = data("path", "oldfilepath", "").toString();
    d->m_pathList.append(tempPath);
    tempPath = data("path", "newfilepath", "").toString();
    d->m_pathList.append(tempPath);
    tempPath = data("path", "curvepath", "").toString();
    d->m_pathList.append(tempPath);
  return true;
}
bool OptPath::writeOpt()
{
  Q_D(OptPath);
    saveData("path", "servo2file", d->m_pathList.at(0));
    saveData("path", "file2servo", d->m_pathList.at(1));
    saveData("path", "flashfilepath", d->m_pathList.at(2));
    saveData("path", "oldfilepath", d->m_pathList.at(3));
    saveData("path", "newfilepath", d->m_pathList.at(4));
    saveData("path", "curvepath", d->m_pathList.at(5));
  return true;
}
void OptPath::respondErrorExecute()
{

}

void OptPath::initMap()
{
    Q_D(OptPath);
    d->m_map.insert("Servo to File:", tr("Upload path:"));
    d->m_map.insert("File to Servo:", tr("Download path:"));
    d->m_map.insert("Flash File Path:", tr("Flash file path:"));
    d->m_map.insert("Old File Path:", tr("Old Version path:"));
    d->m_map.insert("New File Path:", tr("New Version path:"));
    d->m_map.insert("Curve Path:", tr("Curve Path:"));
}

void OptPath::onActionToolButtonClicked(int index) {
    Q_D(OptPath);
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    d->m_pathList.at(index),
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    //qDebug()<<"dir "<<dir;
    if (dir.compare(d->m_pathList.at(index)) != 0 && dir.compare("") != 0) {
        setModify(true);
        QWidget *lineWidget = ui->verticalLayout->itemAt(index)->layout()->itemAt(1)->layout()->itemAt(0)->widget();
        QLineEdit *lineEdit = static_cast<QLineEdit*>(lineWidget);
        lineEdit->setText(dir);
        //d->m_pathList.replace(index, dir);
    }
}
