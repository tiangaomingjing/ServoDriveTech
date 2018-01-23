#include "graphmainwindow.h"
#include "ui_graphmainwindow.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QGLFormat>

GraphMainWindow::GraphMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::GraphMainWindow)
{
  ui->setupUi(this);
  m_scene=new QGraphicsScene(this);
  m_scene->setSceneRect(-200, -200, 400, 400);
  m_view=new QGraphicsView;
  m_view->setScene(m_scene);
  m_view->setCacheMode(QGraphicsView::CacheBackground);
  m_view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
  m_view->setRenderHint(QPainter::Antialiasing);
  m_view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
  m_view->scale(qreal(1), qreal(1));
  ui->vlayout_graph->addWidget(m_view);

  QGraphicsTextItem *item=new QGraphicsTextItem;
  item->setPlainText("QGraphicsTextItem");
  m_scene->addItem(item);
  item->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
  item->setPos(10,10);

  QGraphicsRectItem *item2 = new QGraphicsRectItem(QRectF(0, 0, 60, 60));
  m_scene->addItem (item2);

  QPen pen;               //定义一个画笔
  pen.setWidth (3);       //设置画笔的宽度
  pen.setColor (QColor(qrand() % 256, qrand() % 256, qrand() % 256));
  item2->setPen (pen);
//  item2->setBrush (QColor(qrand() % 256, qrand() % 256, qrand() % 256));
  item2->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);

  item2->setPos (qrand () % ((int)m_scene->sceneRect ().width ()) - 200,
                qrand () % ((int)m_scene->sceneRect ().height ()) - 200);

  m_view=new QGraphicsView;
  m_view->setScene(m_scene);
  m_view->setCacheMode(QGraphicsView::CacheBackground);
  m_view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
  m_view->setRenderHint(QPainter::Antialiasing);
  m_view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
  m_view->scale(qreal(1), qreal(1));
  m_view->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
  m_view->show();
  QString style="QWidget{backgroud-color:gray}";
  qApp->setStyleSheet(style);
}

GraphMainWindow::~GraphMainWindow()
{
  delete ui;
}
