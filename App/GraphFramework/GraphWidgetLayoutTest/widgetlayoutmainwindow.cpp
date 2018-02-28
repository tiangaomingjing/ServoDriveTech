#include "widgetlayoutmainwindow.h"
#include "ui_widgetlayoutmainwindow.h"
#include "interactiveview.h"

#include "piditem.h"
#include "sumitem.h"
#include "sumitemwidget.h"
#include "widgetitem.h"
#include "arrowitem.h"
#include "targetitemwidget.h"

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

  pid=new WidgetItem;
  pid->setObjectName("PID");
  pid->setWidget(wtest,true);
  scene->addItem(pid->item());
  pid->item()->setPos(50,50);

  sumItem=new SumItem;
  scene->addItem(sumItem);



  connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(onSliderValueChanged(int)));

  SumItemWidget *sw=new SumItemWidget;
  sw->setStyleSheet("SumItemWidget{background-color:transparent;border:1px solid white;qproperty-lineColor: blue;} SumItemWidget:hover{background-color:red;}");
  sumWidget=new WidgetItem;
  sumWidget->setObjectName("SUM");
  sumWidget->setWidget(sw);
  scene->addItem(sumWidget->item());

  arrow=new ArrowItem(sumWidget->pointF(WidgetItem::POINT_TYPE_RIGHT),pid->pointF(WidgetItem::POINT_TYPE_LEFT));
  scene->addItem(arrow);

  QLabel *feedback=new QLabel("current feedback");
  QString s="QLabel{\
            background-color: rgb(0, 0, 255);\
            border:2px solid red;\
            border-radius:10px;\
                        }";
  feedback->setStyleSheet(s);
  currentFeedback=new WidgetItem;
  currentFeedback->setObjectName("CurFeedback");
  currentFeedback->setWidget(feedback,true);
  scene->addItem(currentFeedback->item());

  arrowFeedback=new ArrowItem(currentFeedback->pointF(WidgetItem::POINT_TYPE_LEFT),sumWidget->pointF(WidgetItem::POINT_TYPE_BOTTOM),ArrowItem::ARROW_TYPE_CORNER,"-");
  scene->addItem(arrowFeedback);


  QLabel *aheadback=new QLabel("current feedback");
  aheadback->setStyleSheet(s);
  aheadFeed=new WidgetItem;
  aheadFeed->setObjectName("AHeadback");
  aheadFeed->setWidget(aheadback,true);
  scene->addItem(aheadFeed->item());

  arrowAhead=new ArrowItem(aheadFeed->pointF(WidgetItem::POINT_TYPE_RIGHT),pid->pointF(WidgetItem::POINT_TYPE_TOP),ArrowItem::ARROW_TYPE_CORNER,"+",false);
  scene->addItem(arrowAhead);


  TargetItemWidget *curBegin=new TargetItemWidget;
  curFeedbackBegin=new WidgetItem;
  curFeedbackBegin->setWidget(curBegin);
  scene->addItem(curFeedbackBegin->item());

  arrowCurFeedback=new ArrowItem(curFeedbackBegin->pointF(WidgetItem::POINT_TYPE_LEFT),currentFeedback->pointF(WidgetItem::POINT_TYPE_RIGHT));
  scene->addItem(arrowCurFeedback);



  TargetItemWidget *tt1=new TargetItemWidget;
  t1=new WidgetItem;
  t1->setWidget(tt1);
  scene->addItem(t1->item());
  TargetItemWidget *tt2=new TargetItemWidget;
  t2=new WidgetItem;
  t2->setWidget(tt2);
  scene->addItem(t2->item());
  TargetItemWidget *tt3=new TargetItemWidget;
  t3=new WidgetItem;
  t3->setWidget(tt3);
  scene->addItem(t3->item());

  a1=new ArrowItem(t1->pointF(WidgetItem::POINT_TYPE_RIGHT),t2->pointF(WidgetItem::POINT_TYPE_LEFT),ArrowItem::ARROW_TYPE_STRAIGHT,"",false);
  scene->addItem(a1);
  a2=new ArrowItem(t2->pointF(WidgetItem::POINT_TYPE_RIGHT),sumWidget->pointF(WidgetItem::POINT_TYPE_LEFT));
  scene->addItem(a2);
  a3=new ArrowItem(t2->pointF(WidgetItem::POINT_TYPE_TOP),aheadFeed->pointF(WidgetItem::POINT_TYPE_LEFT),ArrowItem::ARROW_TYPE_CORNER);
  scene->addItem(a3);
  a4=new ArrowItem(t2->pointF(WidgetItem::POINT_TYPE_TOP),t3->pointF(WidgetItem::POINT_TYPE_LEFT),ArrowItem::ARROW_TYPE_CORNER);
  scene->addItem(a4);



  adjustItemPostion();

  QLineF line(QPointF(0,0),QPointF(-1,-1));
  qDebug()<<"line dx"<<line.dx();
  qDebug()<<"line dy"<<line.dy();
  qDebug()<<"line angle"<<line.angle();
  double angle=::acos(line.dx()/line.length());
  qDebug()<<"angle"<<angle*180/3.14;

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
  static qreal x=0,y=0;
//  pid->item()->setPos(x,y);
  x+=10;
  y+=5;
  qreal sx,sy;
  sx=pid->item()->pos().x()-pid->item()->boundingRect().width()/2;
  sy=pid->item()->pos().y()+(pid->item()->boundingRect().height()/2-sumItem->boundingRect().height()/2);
  sumItem->setPos(sx,sy);

  sx=pid->item()->pos().x()-pid->item()->boundingRect().width();
  sy=pid->item()->pos().y()+(pid->item()->boundingRect().height()/2-sumWidget->item()->boundingRect().height()/2);
  sumWidget->item()->setPos(sx,sy);


  sx=pid->item()->pos().x();
  sy=pid->item()->pos().y()+pid->item()->boundingRect().height()*1.5;
  currentFeedback->item()->setPos(sx,sy);

  sy=currentFeedback->item()->pos().y()+(currentFeedback->item()->boundingRect().height()/2-curFeedbackBegin->item()->boundingRect().height()/2);
  sx=currentFeedback->item()->pos().x()+currentFeedback->item()->boundingRect().width()*1.5;
  curFeedbackBegin->item()->setPos(sx,sy);


  sy=pid->item()->pos().y()-pid->item()->boundingRect().height()*0.5;
  aheadFeed->item()->setPos(sumWidget->item()->pos().x(),sy);


  sx=sumWidget->item()->pos().x()-40;
  sy=sumWidget->item()->pos().y()+sumWidget->item()->boundingRect().height()/2-t2->item()->boundingRect().height()/2;
  t2->item()->setPos(sx,sy);

  t1->item()->setPos(sx-40,sy);

  sx=aheadFeed->item()->pos().x();
  sy=aheadFeed->item()->pos().y()-aheadFeed->item()->boundingRect().height();
  t3->item()->setPos(sx,sy);

  QTime dieTime = QTime::currentTime().addMSecs(10);
  while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

  arrow->updatePosition();
  arrowFeedback->updatePosition();
  arrowAhead->updatePosition();
  arrowCurFeedback->updatePosition();

  a1->updatePosition();
  a2->updatePosition();
  a3->updatePosition();
  a4->updatePosition();
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
  arrow->setColor(Qt::red);
  arrowFeedback->setColor(Qt::red);
  arrowAhead->setColor(Qt::red);
}
