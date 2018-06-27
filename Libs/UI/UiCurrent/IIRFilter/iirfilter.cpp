#include "iirfilter.h"
#include "ui_iirfilter.h"

#include "NodeItems.h"

#include <QGraphicsScene>
#include <QComboBox>
#include <QStyledItemDelegate>
#include <QVBoxLayout>
#include <QLabel>

IIRFilter::IIRFilter(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::IIRFilter)
{
  ui->setupUi(this);

  QGraphicsScene *scene = new QGraphicsScene(this);
  ui->graphicsView->setScene(scene);
  ui->graphicsView->setObjectName("graphicsview_iirfilter");
//  scene->setSceneRect(-10000,-10000,20000,20000);
  ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  m_p1 = new NodePort;
  m_p2 = new NodePort;
  m_p3 = new NodePort;
  m_s1 = new NodeSwitch;
  connect(m_s1,SIGNAL(clicked(bool)),this,SLOT(onSwitchClicked(bool)));

  //U1
  QWidget *w = new QWidget;
  w->setObjectName("iirfilter");
  QVBoxLayout *vlayout = new QVBoxLayout;
  QLabel *label = new QLabel(tr("IIR Filter"),w);
  label->setObjectName("irrfilter_title");
  m_comboBox = new QComboBox(w);

  QStringList list;
  list<<tr("0 not use")<<tr("1 first-order")<<tr("2 second-order")<<tr("3 band-filter")<<tr("4 ex-band-filter");
  m_comboBox->addItems(list);
  QStyledItemDelegate* itemDelegate = new QStyledItemDelegate(m_comboBox);
  m_comboBox->setItemDelegate(itemDelegate);
  vlayout->addWidget(label);
  vlayout->addWidget(m_comboBox);
  w->setLayout(vlayout);
  m_u1 = new NodeBlock;
  m_u1->setCenterWidget(w,true);

  m_l1 = new NodeLine(m_p1,m_s1->leftPort());
  m_l2 = new NodeLine(m_s1->topPort(),m_u1->leftPort(),INodeConnection::DIR_UP,false);
  m_l3 = new NodeLine(m_u1->rightPort(),m_p2,INodeConnection::DIR_UP,false);
  m_l4 = new NodeLine(m_p2,m_p3);

  m_l5 = new NodeQuadLine(m_s1->bottomPort(),m_p2,INodeConnection::DIR_DOWN);

  scene->addItem(m_p1);
  scene->addItem(m_p2);
  scene->addItem(m_p3);
  scene->addItem(m_s1);
  scene->addItem(m_u1);
  scene->addItem(m_l1);
  scene->addItem(m_l2);
  scene->addItem(m_l3);
  scene->addItem(m_l4);
  scene->addItem(m_l5);

//  NodeCornerLine *cline = new NodeCornerLine(m_p2,m_u1->bottomPort(),INodeConnection::DIR_DOWN);
//  scene->addItem(cline);
  updatePos();

  connect(m_comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(onComboxIndexChanged(int)));
  connect(ui->btn_exit,SIGNAL(clicked(bool)),this,SLOT(onBtnExitClicked()));
  connect(ui->btn_config,SIGNAL(clicked(bool)),this,SIGNAL(configClicked()));
  connect(ui->btn_save,SIGNAL(clicked(bool)),this,SIGNAL(saveClicked()));

}

IIRFilter::~IIRFilter()
{
  delete ui;
}

void IIRFilter::updatePos()
{
  qreal w = m_u1->boundingRect().width();
  qreal h = m_u1->boundingRect().height();
  NodeQuadLine *quad = dynamic_cast<NodeQuadLine *>(m_l5);
  quad->setQualHeight(h/2);

  m_u1->setPos(-60,-30);

  QPointF tp = m_s1->topPort()->mapToParent(QPointF(0,0));
  qreal dh = tp.y();
  m_s1->setPos(m_u1->pos()+QPointF(-w/4-m_s1->boundingRect().width(),h/2-dh-m_s1->topPort()->rect().width()/2));
  m_p1->setPos(m_s1->pos()+QPointF(-20,m_s1->boundingRect().height()/2 - m_p1->rect().width()/2));
  m_p2->setPos(m_u1->pos()+QPointF(20+w,h/2 - m_p2->rect().height()/2));
  m_p3->setPos(m_p2->pos()+QPointF(20,0));
}

QDoubleSpinBox *IIRFilter::boxFn1()
{
  return ui->doubleSpinBox_fn1;
}

QDoubleSpinBox *IIRFilter::boxFn2()
{
  return ui->doubleSpinBox_fn2;
}

QDoubleSpinBox *IIRFilter::boxQx2()
{
  return ui->doubleSpinBox_qx2;
}

QDoubleSpinBox *IIRFilter::boxFnNch()
{
  return ui->doubleSpinBox_fn_nch;
}

QDoubleSpinBox *IIRFilter::boxQxNch()
{
  return ui->doubleSpinBox_qx_nch;
}

QDoubleSpinBox *IIRFilter::boxKnNch()
{
  return ui->doubleSpinBox_kn_nch;
}

int IIRFilter::currentFitSelectIndex()
{
  return m_comboBox->currentIndex();
}

void IIRFilter::setFitSelectIndex(int index)
{
  m_comboBox->setCurrentIndex(index);
  onComboxIndexChanged(index);
}

void IIRFilter::onComboxIndexChanged(int index)
{
  if(index == -1)
    return ;
  switch (index)
  {
  case 0:
    ui->label_fn1->setVisible(false);
    ui->label_fn2->setVisible(false);
    ui->label_fn_nch->setVisible(false);
    ui->label_kn_nch->setVisible(false);
    ui->label_qx2->setVisible(false);
    ui->label_qx_nch->setVisible(false);
    ui->doubleSpinBox_fn1->setVisible(false);
    ui->doubleSpinBox_fn2->setVisible(false);
    ui->doubleSpinBox_fn_nch->setVisible(false);
    ui->doubleSpinBox_kn_nch->setVisible(false);
    ui->doubleSpinBox_qx2->setVisible(false);
    ui->doubleSpinBox_qx_nch->setVisible(false);
    break;
  case 1:
    ui->label_fn1->setVisible(true);
    ui->label_fn2->setVisible(false);
    ui->label_fn_nch->setVisible(false);
    ui->label_kn_nch->setVisible(false);
    ui->label_qx2->setVisible(false);
    ui->label_qx_nch->setVisible(false);
    ui->doubleSpinBox_fn1->setVisible(true);
    ui->doubleSpinBox_fn2->setVisible(false);
    ui->doubleSpinBox_fn_nch->setVisible(false);
    ui->doubleSpinBox_kn_nch->setVisible(false);
    ui->doubleSpinBox_qx2->setVisible(false);
    ui->doubleSpinBox_qx_nch->setVisible(false);
    break;
  case 2:
    ui->label_fn1->setVisible(false);
    ui->label_fn2->setVisible(true);
    ui->label_fn_nch->setVisible(false);
    ui->label_kn_nch->setVisible(false);
    ui->label_qx2->setVisible(true);
    ui->label_qx_nch->setVisible(false);
    ui->doubleSpinBox_fn1->setVisible(false);
    ui->doubleSpinBox_fn2->setVisible(true);
    ui->doubleSpinBox_fn_nch->setVisible(false);
    ui->doubleSpinBox_kn_nch->setVisible(false);
    ui->doubleSpinBox_qx2->setVisible(true);
    ui->doubleSpinBox_qx_nch->setVisible(false);
    break;
  case 3:
    ui->label_fn1->setVisible(false);
    ui->label_fn2->setVisible(false);
    ui->label_fn_nch->setVisible(true);
    ui->label_kn_nch->setVisible(true);
    ui->label_qx2->setVisible(false);
    ui->label_qx_nch->setVisible(true);
    ui->doubleSpinBox_fn1->setVisible(false);
    ui->doubleSpinBox_fn2->setVisible(false);
    ui->doubleSpinBox_fn_nch->setVisible(true);
    ui->doubleSpinBox_kn_nch->setVisible(true);
    ui->doubleSpinBox_qx2->setVisible(false);
    ui->doubleSpinBox_qx_nch->setVisible(true);
    break;
  case 4:
    ui->label_fn1->setVisible(false);
    ui->label_fn2->setVisible(false);
    ui->label_fn_nch->setVisible(true);
    ui->label_kn_nch->setVisible(true);
    ui->label_qx2->setVisible(false);
    ui->label_qx_nch->setVisible(true);
    ui->doubleSpinBox_fn1->setVisible(false);
    ui->doubleSpinBox_fn2->setVisible(false);
    ui->doubleSpinBox_fn_nch->setVisible(true);
    ui->doubleSpinBox_kn_nch->setVisible(true);
    ui->doubleSpinBox_qx2->setVisible(false);
    ui->doubleSpinBox_qx_nch->setVisible(true);
    break;
  default:
    break;
  }
  if(index == 0)
    m_s1->setIsOn(false);
  else
    m_s1->setIsOn(true);

  emit fitSelectChanged(index);
}

void IIRFilter::onSwitchClicked(bool isOn)
{
  if(!isOn)
  {
    m_comboBox->setCurrentIndex(0);
  }
  else
  {
    m_comboBox->setCurrentIndex(1);
  }
}

void IIRFilter::onBtnExitClicked()
{
  hide();
}
