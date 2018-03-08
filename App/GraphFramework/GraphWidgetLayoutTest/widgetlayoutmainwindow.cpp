#include "widgetlayoutmainwindow.h"
#include "ui_widgetlayoutmainwindow.h"
#include "interactiveview.h"

#include "piditem.h"
#include "sumitem.h"
#include "sumitemwidget.h"
#include "widgetitem.h"
#include "arrowitem.h"
#include "targetitemwidget.h"
#include "anchoritemhelper.h"
#include "saturationitemwidget.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsWidget>
#include <QGraphicsLinearLayout>
#include <QGraphicsProxyWidget>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QLineEdit>
#include <QTime>

#include <qmath.h>

class Label :public QLabel
{
public:
  Label(const QString &text):QLabel(text)
  {

  }
  ~Label()
  {
    qDebug()<<"label destruct-->";
  }
};

WidgetLayoutMainWindow::WidgetLayoutMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::WidgetLayoutMainWindow)
{
  ui->setupUi(this);
  QAction *act=new QAction("setcolor",this);
  ui->mainToolBar->addAction(act);
  connect(act,SIGNAL(triggered(bool)),this,SLOT(onActionTest()));

  scene=new QGraphicsScene(this);
  scene->setSceneRect(-400, -200, 800, 400);
  view=new InteractiveView;
  view->setScene(scene);
  view->setCacheMode(QGraphicsView::CacheBackground);
  view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
  view->setRenderHint(QPainter::Antialiasing);
  view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
  view->scale(qreal(1), qreal(1));
  view->setBackgroundBrush(QBrush(Qt::green));
  ui->verticalLayout->insertWidget(0,view);


//  QGraphicsWidget *w=new QGraphicsWidget;
  QGraphicsWidget *w=new QGraphicsWidget(0, Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
//  QGraphicsWidget *w=new QGraphicsWidget(0, Qt::Window);
//  w->setWindowFlags(Qt::FramelessWindowHint);
  w->setWindowTitle(tr("pid block"));
  w->setFlags(QGraphicsItem::ItemIsMovable);
  w->setPos(0,0);
  QPalette p;
  p.setBrush(QPalette::Window,QBrush(Qt::transparent));
  w->setPalette(p);


//  QLabel *label=new QLabel("Hello world");
//  QGraphicsProxyWidget *pLabel=scene->addWidget(label);
////  QGraphicsProxyWidget *pLabel=new QGraphicsProxyWidget;
////  pLabel->setWidget(label);

//  QDoubleSpinBox *box=new QDoubleSpinBox;
//  QGraphicsProxyWidget *pbox=scene->addWidget(box);
////  QGraphicsProxyWidget *pbox=new QGraphicsProxyWidget;
////  pbox->setWidget(box);


//  QGraphicsLinearLayout *layout=new QGraphicsLinearLayout(Qt::Vertical);
//  layout->addItem(pLabel);
//  layout->addItem(pbox);
//  w->setLayout(layout);

  QWidget *widget=new QWidget;
  widget->setObjectName("w");

  QLabel *label=new QLabel("Hello world");
  QDoubleSpinBox *box=new QDoubleSpinBox;
  QHBoxLayout *hlayout=new QHBoxLayout;
  hlayout->addWidget(label);
  hlayout->addWidget(box);
  widget->setLayout(hlayout);

  QWidget *widget2=new QWidget;
  QHBoxLayout *hlayout2=new QHBoxLayout;
  hlayout2->setMargin(0);
  hlayout2->addWidget(widget);
  widget2->setLayout(hlayout2);

//  QGraphicsProxyWidget *pw=scene->addWidget(widget);
  QGraphicsProxyWidget *pw=new QGraphicsProxyWidget;
  pw->setWidget(widget2);

  QGraphicsLinearLayout *layout=new QGraphicsLinearLayout(Qt::Vertical);
  layout->addItem(pw);
  w->setLayout(layout);

  scene->addItem(w);

  scene->installEventFilter(this);

  QWidget *wtest=new QWidget;
  wtest->setObjectName("wtest");
  QVBoxLayout *vlayoutTest=new QVBoxLayout(wtest);
  QLabel *title=new QLabel("PID controller",wtest);
  title->setStyleSheet("QLabel{padding-bottom:10px;margin-bottom:10px;color:white;border:1px solid transparent;border-bottom-color:white;font-weight:bold;}");
  title->setAlignment(Qt::AlignCenter);
  vlayoutTest->addWidget(title);
  QLabel *pgain=new QLabel(tr("P gain(HZ)"));
  vlayoutTest->addWidget(pgain);
  QLineEdit *edit=new QLineEdit(wtest);
  edit->setText("100");
  edit->setMinimumWidth(200);
  vlayoutTest->addWidget(edit);
  QLabel *igain=new QLabel(tr("I gain(ms)"),wtest);
  vlayoutTest->addWidget(igain);
  edit=new QLineEdit(wtest);
  edit->setText("200");
  edit->setMinimumWidth(200);
  vlayoutTest->addWidget(edit);

  wtest->setLayout(vlayoutTest);



  u0=new WidgetItem;
  u0->setObjectName("PID");
  u0->setWidget(wtest,true);
  scene->addItem(u0);
  u0->setPos(50,50);



  connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(onSliderValueChanged(int)));

  SumItemWidget *sw=new SumItemWidget;
  sw->setStyleSheet("SumItemWidget{background-color:transparent;border:1px solid white;qproperty-lineColor: blue;} SumItemWidget:hover{background-color:red;}");
  u1=new WidgetItem;
  u1->setObjectName("SUM");
  u1->setWidget(sw);
  scene->addItem(u1);



  QLabel *feedback=new QLabel("current feedback");
  QString s="QLabel{\
            background-color: rgb(0, 0, 255);\
            border:2px solid red;\
            border-radius:10px;\
                        }";
  feedback->setStyleSheet(s);
  u2=new WidgetItem;
  u2->setObjectName("CurFeedback");
  u2->setWidget(feedback,true);
  scene->addItem(u2);




  QLabel *aheadback=new QLabel("current feedback");
  aheadback->setStyleSheet(s);
  u3=new WidgetItem;
  u3->setObjectName("AHeadback");
  u3->setWidget(aheadback,true);
  scene->addItem(u3);



  TargetItemWidget *curBegin=new TargetItemWidget;
  t4=new WidgetItem;
  t4->setWidget(curBegin);
  scene->addItem(t4);



  TargetItemWidget *tt1=new TargetItemWidget;
  t1=new WidgetItem;
  t1->setWidget(tt1);
  scene->addItem(t1);
  TargetItemWidget *tt2=new TargetItemWidget;
  t2=new WidgetItem;
  t2->setWidget(tt2);
  scene->addItem(t2);
  TargetItemWidget *tt3=new TargetItemWidget;
  t3=new WidgetItem;
  t3->setWidget(tt3);
  scene->addItem(t3);

  a1=new ArrowItem(t1->pointF(WidgetItem::POINT_TYPE_RIGHT),t2->pointF(WidgetItem::POINT_TYPE_LEFT),ArrowItem::ARROW_TYPE_STRAIGHT,"",false);
  scene->addItem(a1);
  a2=new ArrowItem(t2->pointF(WidgetItem::POINT_TYPE_RIGHT),u1->pointF(WidgetItem::POINT_TYPE_LEFT));
  scene->addItem(a2);
  a3=new ArrowItem(t2->pointF(WidgetItem::POINT_TYPE_TOP),u3->pointF(WidgetItem::POINT_TYPE_LEFT),ArrowItem::ARROW_TYPE_CORNER);
  scene->addItem(a3);
  a4=new ArrowItem(t2->pointF(WidgetItem::POINT_TYPE_TOP),t3->pointF(WidgetItem::POINT_TYPE_LEFT),ArrowItem::ARROW_TYPE_CORNER);
  scene->addItem(a4);

  a5=new ArrowItem(u1->pointF(WidgetItem::POINT_TYPE_RIGHT),u0->pointF(WidgetItem::POINT_TYPE_LEFT));
  scene->addItem(a5);

  a6=new ArrowItem(u2->pointF(WidgetItem::POINT_TYPE_LEFT),u1->pointF(WidgetItem::POINT_TYPE_BOTTOM),ArrowItem::ARROW_TYPE_CORNER,"-");
  scene->addItem(a6);

  a7=new ArrowItem(u3->pointF(WidgetItem::POINT_TYPE_RIGHT),u0->pointF(WidgetItem::POINT_TYPE_TOP),ArrowItem::ARROW_TYPE_CORNER,"+",false);
  scene->addItem(a7);

  a8=new ArrowItem(t4->pointF(WidgetItem::POINT_TYPE_LEFT),u2->pointF(WidgetItem::POINT_TYPE_RIGHT));
  scene->addItem(a8);

  anchorHelper=new AnchorItemHelper;

  anchorHelper->addAnchor(u0,u1,AnchorItemHelper::AnchorRight,-1*u0->boundingRect().width()*1.5);
  anchorHelper->addAnchor(u0,u1,AnchorItemHelper::AnchorVerticalCenter);

  anchorHelper->addAnchor(u0,u2,AnchorItemHelper::AnchorHorizontalCenter);
  anchorHelper->addAnchor(u0,u2,AnchorItemHelper::AnchorBottom,u2->boundingRect().height()*3);

  anchorHelper->addAnchor(u2,t4,AnchorItemHelper::AnchorRight,u2->boundingRect().width());
  anchorHelper->addAnchor(u2,t4,AnchorItemHelper::AnchorVerticalCenter);

  anchorHelper->addAnchor(u0,u3,AnchorItemHelper::AnchorLeft,-1*u3->boundingRect().width()-u0->boundingRect().width()/2);
  anchorHelper->addAnchor(u0,u3,AnchorItemHelper::AnchorTop,-1*u0->boundingRect().height()/2);

  anchorHelper->addAnchor(u3,t3,AnchorItemHelper::AnchorHorizontalCenter);
  anchorHelper->addAnchor(u3,t3,AnchorItemHelper::AnchorTop,-1*u3->boundingRect().height());

  anchorHelper->addAnchor(u3,t2,AnchorItemHelper::AnchorLeft,-1*u3->boundingRect().width()/3);
  anchorHelper->addAnchor(u1,t2,AnchorItemHelper::AnchorVerticalCenter);

  anchorHelper->addAnchor(t2,t1,AnchorItemHelper::AnchorHorizontalCenter,-1*u0->boundingRect().width()/3);
  anchorHelper->addAnchor(t2,t1,AnchorItemHelper::AnchorVerticalCenter);

  adjustItemPostion();

  QLineF line(QPointF(0,0),QPointF(-1,-1));
  qDebug()<<"line dx"<<line.dx();
  qDebug()<<"line dy"<<line.dy();
  qDebug()<<"line angle"<<line.angle();
  double angle=::acos(line.dx()/line.length());
  qDebug()<<"angle"<<angle*180/3.14;

  SaturationItemWidget *ac=new SaturationItemWidget;
  WidgetItem *acw=new WidgetItem;
  acw->setWidget(ac,false);
  scene->addItem(acw);
  acw->setPos(200,50);

}

WidgetLayoutMainWindow::~WidgetLayoutMainWindow()
{
  delete ui;
}


bool WidgetLayoutMainWindow::eventFilter(QObject *obj, QEvent *event)
{
//  static int count=0;
  if(obj==scene)
  {
//    qDebug()<<"scene"<<"count="<<count++;
    if(event->type()==QEvent::GraphicsSceneMouseMove)
    {
      QGraphicsSceneMouseEvent *e=dynamic_cast<QGraphicsSceneMouseEvent *>(event);
      ui->statusBar->showMessage(QString("scene X:%1,Y:%2").arg(e->scenePos().x()).arg(e->scenePos().y()));
    }
  }
  return QMainWindow::eventFilter(obj,event);
}

void WidgetLayoutMainWindow::adjustItemPostion()
{
  qDebug()<<"adjustItemPostion===============";

  anchorHelper->setAnchorsActive();

  QTime dieTime = QTime::currentTime().addMSecs(10);
  while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);



  a1->updatePosition();
  a2->updatePosition();
  a3->updatePosition();
  a4->updatePosition();
  a5->updatePosition();
  a6->updatePosition();
  a7->updatePosition();
  a8->updatePosition();

}

void WidgetLayoutMainWindow::on_actionSetfont_triggered()
{
  static int psize=12;
  QFont font ;
  font.setPixelSize(psize);
  qApp->setFont(font);
  psize++;
  qDebug()<<"psize"<<psize;

  QString s="QWidget#wtest{\
            background-color: rgb(0, 0, 255);\
            border:2px solid red;\
            border-radius:10px;\
                        }";
  qApp->setStyleSheet(s);

//  sumWidget->widget()->setStyleSheet("SumItemWidget{background-color:transparent;border:1px solid white;qproperty-lineColor: blue;}");

  adjustItemPostion();
}

void WidgetLayoutMainWindow::onSliderValueChanged(int value)
{
  qreal scale = qPow(qreal(2), (value - 250) / qreal(50));
  QMatrix matrix;
  matrix.scale(scale, scale);

  view->setMatrix(matrix);
  //  view
}

void WidgetLayoutMainWindow::onActionTest()
{
  a1->setColor(Qt::red);
  a2->setColor(Qt::red);
  a3->setColor(Qt::red);
  a4->setColor(Qt::red);
  a5->setColor(Qt::red);
  a6->setColor(Qt::red);
  a7->setColor(Qt::red);
  a8->setColor(Qt::red);
}
