#include "widgetlayoutmainwindow.h"
#include "ui_widgetlayoutmainwindow.h"

#include "piditem.h"
#include "sumitem.h"
#include "sumitemwidget.h"

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
  scene=new QGraphicsScene(this);
  scene->setSceneRect(-400, -200, 800, 400);
  view=new QGraphicsView;
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
  title->setStyleSheet("QLabel{color:white;border:1px solid transparent;border-bottom-color:white;font-weight:bold;}");
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

  pid=new PidItem;
  pid->setWidget(wtest);
  scene->addItem(pid->item());
  pid->item()->setPos(50,50);

  sumItem=new SumItem;
  scene->addItem(sumItem);



  connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(onSliderValueChanged(int)));

  SumItemWidget *sw=new SumItemWidget;
  sw->setStyleSheet("SumItemWidget{background-color:transparent;border:1px solid white;qproperty-lineColor: blue;} SumItemWidget:hover{background-color:red;}");
  sumWidget=scene->addWidget(sw);

  adjustItemPostion();
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
  qreal sx,sy;
  sx=pid->item()->pos().x()-pid->item()->boundingRect().width()/2;
  sy=pid->item()->pos().y()+(pid->item()->boundingRect().height()/2-sumItem->boundingRect().height()/2);
  sumItem->setPos(sx,sy);

  sx=sumItem->pos().x()-pid->item()->boundingRect().width()/2;
  sumWidget->setPos(sx,sy);
}

void WidgetLayoutMainWindow::on_actionSetfont_triggered()
{
  QFont font = qApp->font();
  int psize=font.pixelSize()+2;
  font.setPixelSize(psize);
  qApp->setFont(font);
  qDebug()<<pid->item()->boundingRect();

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
