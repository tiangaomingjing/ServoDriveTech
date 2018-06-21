#include "nodeeditmainwindow.h"
#include "ui_nodeeditmainwindow.h"

#include "nodeport.h"
#include "nodeline.h"
#include "nodeblock.h"
#include "nodecornerline.h"
#include "nodequadline.h"
#include "nodeswitch.h"
#include "nodeswitch.h"

#include <QGraphicsScene>
#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>

NodeEditMainWindow::NodeEditMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::NodeEditMainWindow)
{
  ui->setupUi(this);
  m_scene = new QGraphicsScene(this);
  ui->graphicsView->setScene(m_scene);
  port1 = new NodePort;

  port1->setPen(QPen(Qt::red));
  port1->setBrush(QBrush(Qt::blue));

  m_switch = new NodeSwitch;
  m_scene->addItem(m_switch);

  line = new NodeLine(port1,m_switch->leftPort());
  m_scene->addItem(line);


  port2 = new NodePort;

  port2->setPen(QPen(Qt::blue));
  port2->setBrush(QBrush(Qt::yellow));
  port2->setPos(100,100);

  m_scene->addItem(port1);
  m_scene->addItem(port2);

  qDebug()<<"cccccccccccccccccccc";

  block = new NodeBlock;
//  block->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
  QWidget *w = new QWidget;
  QVBoxLayout *vlayout = new QVBoxLayout(w);
  QLabel *label = new QLabel("Hello world");
  QLineEdit *edit = new QLineEdit;
  QLabel *label2 = new QLabel("Hello world 2");
  QLineEdit *edit2 = new QLineEdit;
  vlayout->addWidget(label);
  vlayout->addWidget(edit);
  vlayout->addWidget(label2);
  vlayout->addWidget(edit2);
  w->setLayout(vlayout);
  block->setCenterWidget(w);
  block->setPos(100,-200);
  m_scene->addItem(block);

  NodeLine *mLine = new NodeLine(m_switch->topPort(),block->leftPort(),INodeConnection::DIR_UP,false);
  m_scene->addItem(mLine);

//  cornerLine = new NodeCornerLine(m_switch->bottomPort(),port2,INodeConnection::DIR_DOWN);
//  m_scene->addItem(cornerLine);


  quadLine = new NodeQuadLine(m_switch->bottomPort(),port2);
  quadLine->setDir(INodeConnection::DIR_DOWN);
  quadLine->setQualHeight(50);
  m_scene->addItem(quadLine);

}

NodeEditMainWindow::~NodeEditMainWindow()
{
  delete ui;
}

void NodeEditMainWindow::on_actionTest_triggered()
{
    delete port1;
    delete block;
}

void NodeEditMainWindow::on_actionTestMove_triggered()
{
    block->setPos(block->scenePos()+QPointF(10,10));
}

void NodeEditMainWindow::on_actionSetFontTest_triggered()
{
  static int psize=12;
  QFont font ;
  font.setPixelSize(psize);
  qApp->setFont(font);
  psize ++;
}

void NodeEditMainWindow::on_actionTestDelPort2_triggered()
{
    delete port2;
}
