#include "optpath.h"
#include "ui_optpath.h"
#include "iopt_p.h"
#include <QDebug>
#include <QFile>
#include <QLabel>
#include <QLineEdit>
#include <QToolButton>
#include <QLayout>

class OptPathPrivate: public IOptPrivate {
    Q_DECLARE_PUBLIC(OptPath)
    public:
      OptPathPrivate();
      ~OptPathPrivate();
      QStringList m_pathList;
      QStringList m_nameList;
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
    readOpt();
    QString fileName = d->m_optPath + "path/path.ini";
    QFile file(fileName);
    if(file.open(QFile::ReadOnly))
    {
      QTextStream in(&file);
      QString s;
      while (!in.atEnd()) {
        s=in.readLine();
        qDebug()<<s;
        d->m_nameList.append(s);
      }
      d->m_nameList.removeAll("");
      file.close();
    }
    uiInit();
}

OptPath::~OptPath()
{
    delete ui;
}

void OptPath::uiInit()
{
    Q_D(OptPath);
    qDebug()<< "list count "<<d->m_nameList.count();
//    for (int i = 0; i < d->m_nameList.count(); i++) {
//        QVBoxLayout *vBox = new QVBoxLayout;
//        QHBoxLayout *hBox = new QHBoxLayout;
//        QLabel* label = new QLabel(d->m_nameList.at(i));
//        QToolButton* toolButton = new QToolButton;
//        QLineEdit* lineEdit = new QLineEdit;
//        lineEdit->setText(d->m_pathList.at(i));
//        hBox->addWidget(lineEdit);
//        hBox->addWidget(toolButton);
//        vBox->addWidget(label);
//        vBox->addLayout(hBox);
//        ui->verticalLayout->addLayout(vBox);
//    }
}

bool OptPath::optActive()
{
  qDebug()<<"opt plot execute active ";
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
  return true;
}
bool OptPath::writeOpt()
{
  Q_D(OptPath);
  return true;
}
void OptPath::respondErrorExecute()
{

}
