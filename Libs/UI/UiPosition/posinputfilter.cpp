#include "posinputfilter.h"
#include "ui_posinputfilter.h"

#include "NodeItems.h"

#include <QGraphicsScene>
#include <QComboBox>
#include <QStyledItemDelegate>
#include <QVBoxLayout>
#include <QLabel>
#include <QHBoxLayout>

PosInputFilter::PosInputFilter(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::PosInputFilter),
  m_SW(0)
{
  ui->setupUi(this);

  QGraphicsScene *scene = new QGraphicsScene(this);
  ui->graphicsView->setScene(scene);
  ui->graphicsView->setObjectName("graphicsview_posfilter");
//  scene->setSceneRect(-10000,-10000,20000,20000);
  ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  m_p1 = new NodePort;
  m_p2 = new NodePort;
  m_p3 = new NodePort;
  m_p4 = new NodePort;
  m_s1 = new NodeSwitch;
  connect(m_s1,SIGNAL(clicked(bool)),this,SLOT(onSwitch1Clicked(bool)));
  m_s2 = new NodeSwitch;
  connect(m_s2,SIGNAL(clicked(bool)),this,SLOT(onSwitch2Clicked(bool)));

  //U1
  QWidget *w1 = new QWidget;
  w1->setObjectName("posFirfilter");
  QVBoxLayout *vlayout1 = new QVBoxLayout;
  QLabel *label1 = new QLabel(tr("Fir Filter"),w1);
  label1->setObjectName("posFirfilter_title");
  QHBoxLayout *hlayout1 = new QHBoxLayout;
  QLabel *label_maf = new QLabel(tr("maf_num"),w1);
  QLabel *label_unit = new QLabel("(ms)",w1);
  m_mafNum = new QDoubleSpinBox(w1);
  m_mafNum->setButtonSymbols(QAbstractSpinBox::NoButtons);
  m_mafNum->setMaximumWidth(30);
  m_mafNum->setMinimum(0);
  m_mafNum->setMaximum(2147483647);
  hlayout1->addWidget(label_maf);
  hlayout1->addWidget(m_mafNum);
  hlayout1->addWidget(label_unit);
  vlayout1->addWidget(label1);
  vlayout1->addLayout(hlayout1);
  w1->setLayout(vlayout1);
  m_u1 = new NodeBlock;
  m_u1->setCenterWidget(w1,true);


  //U2
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
  m_u2 = new NodeBlock;
  m_u2->setCenterWidget(w,true);

  m_l1 = new NodeLine(m_p1,m_s1->leftPort());
  m_l2 = new NodeLine(m_s1->topPort(),m_u1->leftPort(),INodeConnection::DIR_UP,false);
  m_l3 = new NodeLine(m_u1->rightPort(),m_p2,INodeConnection::DIR_UP,false);
  m_l4 = new NodeLine(m_p2,m_s2->leftPort());
  m_l5 = new NodeLine(m_s2->topPort(),m_u2->leftPort(),INodeConnection::DIR_UP,false);
  m_l6 = new NodeLine(m_u2->rightPort(),m_p3,INodeConnection::DIR_UP,false);
  m_l7 = new NodeLine(m_p3,m_p4);
  m_l8 = new NodeQuadLine(m_s1->bottomPort(),m_p2,INodeConnection::DIR_DOWN);
  m_l9 = new NodeQuadLine(m_s2->bottomPort(),m_p3,INodeConnection::DIR_DOWN);

  scene->addItem(m_p1);
  scene->addItem(m_p2);
  scene->addItem(m_p3);
  scene->addItem(m_p4);
  scene->addItem(m_s1);
  scene->addItem(m_s2);
  scene->addItem(m_u1);
  scene->addItem(m_u2);
  scene->addItem(m_l1);
  scene->addItem(m_l2);
  scene->addItem(m_l3);
  scene->addItem(m_l4);
  scene->addItem(m_l5);
  scene->addItem(m_l6);
  scene->addItem(m_l7);
  scene->addItem(m_l8);
  scene->addItem(m_l9);

  updatePos();

  connect(m_comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(onComboxIndexChanged(int)));
  connect(ui->btn_exit,SIGNAL(clicked(bool)),this,SLOT(onBtnExitClicked()));
  connect(ui->btn_config,SIGNAL(clicked(bool)),this,SIGNAL(configClicked()));
  connect(ui->btn_save,SIGNAL(clicked(bool)),this,SIGNAL(saveClicked()));

}

PosInputFilter::~PosInputFilter()
{
  delete ui;
}

void PosInputFilter::updatePos()
{
  qreal w1 = m_u1->boundingRect().width();
  qreal h1 = m_u1->boundingRect().height();
  qreal w2 = m_u2->boundingRect().width();
  qreal h2 = m_u2->boundingRect().height();
  NodeQuadLine *quad8 = dynamic_cast<NodeQuadLine *>(m_l8);
  quad8->setQualHeight(h1/2);
  NodeQuadLine *quad9 = dynamic_cast<NodeQuadLine *>(m_l9);
  quad9->setQualHeight(h1/2 + 12);

  m_u1->setPos(-60,-30);

  QPointF tp = m_s1->topPort()->mapToParent(QPointF(0,0));
  qreal dh = tp.y();

  m_s1->setPos(m_u1->pos()+QPointF(-m_s1->boundingRect().width()*2,h1/2-dh-m_s1->topPort()->rect().width()/2));
  m_p1->setPos(m_s1->pos()+QPointF(-20,m_s1->boundingRect().height()/2 - m_p1->rect().width()/2));
  m_p2->setPos(m_u1->pos()+QPointF(20+w1,h1/2 - m_p2->rect().height()/2));
  m_s2->setPos(m_p2->pos()+QPointF(20,-m_s2->boundingRect().height()/2+m_p2->rect().height()/2));
  m_u2->setPos(m_s2->pos()+QPointF(m_s2->boundingRect().width()+20,-(h2/2-dh-m_s2->topPort()->rect().width()/2)));
  m_p3->setPos(m_u2->pos()+QPointF(w2+20,h2/2-m_p3->rect().height()/2));
  m_p4->setPos(m_p3->pos()+QPointF(20,0));

}

QDoubleSpinBox *PosInputFilter::boxFn1()
{
  return ui->doubleSpinBox_fn1;
}

QDoubleSpinBox *PosInputFilter::boxFn2()
{
  return ui->doubleSpinBox_fn2;
}

QDoubleSpinBox *PosInputFilter::boxQx2()
{
  return ui->doubleSpinBox_qx2;
}

QDoubleSpinBox *PosInputFilter::boxFnNch()
{
  return ui->doubleSpinBox_fn_nch;
}

QDoubleSpinBox *PosInputFilter::boxQxNch()
{
  return ui->doubleSpinBox_qx_nch;
}

QDoubleSpinBox *PosInputFilter::boxKnNch()
{
  return ui->doubleSpinBox_kn_nch;
}

QDoubleSpinBox *PosInputFilter::boxMafNum()
{
  return m_mafNum;
}

int PosInputFilter::currentIIRFilterIndex()
{
  return m_comboBox->currentIndex();
}

void PosInputFilter::setIIRFilterIndex(int index)
{
  m_comboBox->setCurrentIndex(index);
  onComboxIndexChanged(index);
}

void PosInputFilter::onComboxIndexChanged(int index)
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
    m_s2->setIsOn(false);
  else
    m_s2->setIsOn(true);
}

void PosInputFilter::onSwitch1Clicked(bool isOn)
{
  if(isOn)
    m_SW = 0;
  else
    m_SW = 1;
}

void PosInputFilter::onSwitch2Clicked(bool isOn)
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

void PosInputFilter::onBtnExitClicked()
{
  hide();
}

quint16 PosInputFilter::SW() const
{
  return m_SW;
}

void PosInputFilter::setSW(quint16 SW)
{
  m_SW = SW;
  if(SW == 0)
    m_s1->setIsOn(true);
  else
    m_s1->setIsOn(false);
}
