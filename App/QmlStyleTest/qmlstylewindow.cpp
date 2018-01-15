#include "qmlstylewindow.h"
#include "ui_qmlstylewindow.h"

#include "qmlstylehelper.h"

#include "gtutils.h"

#include <QtQml>
#include <QQuickWidget>

QmlStyleWindow::QmlStyleWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::QmlStyleWindow)
{
  ui->setupUi(this);
  qmlRegisterType<QmlStyleHelper>("QtCppClass", 1, 0, "QmlStyleHelper");
  m_qmlstyleHelper=new QmlStyleHelper(12,"english","blue",0);

  QString f1="D:/Smart/ServoMaster/git-project/ServoDriveTech/ServoDriveTech/App/QmlStyleTest/Qmlw1.qml";
  QString f2="D:/Smart/ServoMaster/git-project/ServoDriveTech/ServoDriveTech/App/QmlStyleTest/Qmlw2.qml";
  m_qw1=new QQuickWidget;
  m_qw1->engine()->addImportPath("D:/Smart/ServoMaster/git-project/ServoDriveTech/ServoDriveTech/build/debug/custom/option/qmlstyle/");
  m_qw1->setMinimumSize(600,400);
  m_qw1->rootContext()->setContextProperty("qmlStyleHelper",m_qmlstyleHelper);
  m_qw1->setResizeMode(QQuickWidget::SizeRootObjectToView );
  m_qw1->setSource(QUrl::fromLocalFile(f1));

  m_qw2=new QQuickWidget;
  m_qw2->engine()->addImportPath("D:/Smart/ServoMaster/git-project/ServoDriveTech/ServoDriveTech/build/debug/custom/option/qmlstyle/");
  m_qw2->setMinimumSize(600,400);
  m_qw2->rootContext()->setContextProperty("qmlStyleHelper",m_qmlstyleHelper);
  m_qw2->setResizeMode(QQuickWidget::SizeRootObjectToView );
  m_qw2->setSource(QUrl::fromLocalFile(f2));
  ui->qvlayout_1->addWidget(m_qw1);
  ui->qvlayout_2->addWidget(m_qw2);
}

QmlStyleWindow::~QmlStyleWindow()
{
  delete ui;
  delete m_qmlstyleHelper;
}

void QmlStyleWindow::on_actionBlueTest_triggered()
{
  m_qmlstyleHelper->setCss("blue");
}

void QmlStyleWindow::on_actionBlackTest_triggered()
{
  m_qmlstyleHelper->setCss("black");
}
