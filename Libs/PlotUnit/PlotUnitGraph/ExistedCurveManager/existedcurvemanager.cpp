#include "existedcurvemanager.h"

#include <QTableWidgetItem>
#include <QTableWidget>
#include <QDebug>

class ExistedCurveManagerPrivate {
public:
    QColor m_showColor;
    QColor m_backShowColor;
    QColor m_hideColor;
    QColor m_backHideColor;
    GtPlot *m_plotHistory;
    QTableWidget *m_tableHistory;
    QList<ICurve*> m_curveList;
};

typedef enum {
  COL_TABLE_CURVE_SHOW,
  COL_TABLE_CURVE_NAME,
  COL_TABLE_CURVE_AXIS,
  COL_TABLE_CURVE_SIZE
}TableCurveColumnInx;

typedef enum{
  ROLE_TABLE_CURVE_ICURVE_PTR = Qt::UserRole+1,
  ROLE_TABLE_CURVE_GRAPH_PTR = Qt::UserRole+2
}CurveTableDataRole;

Q_DECLARE_METATYPE(ICurve*)
Q_DECLARE_METATYPE(QCPGraph *)

ExistedCurveManager::ExistedCurveManager(const QList<ICurve*> &curveList, QObject *parent) : QObject(parent)
{
    dd = new ExistedCurveManagerPrivate;
    dd->m_plotHistory = new GtPlot;
    dd->m_plotHistory->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    dd->m_tableHistory = new QTableWidget;
    dd->m_curveList = curveList;
    initUi();
}

ExistedCurveManager::~ExistedCurveManager()
{
    delete dd->m_plotHistory;
    delete dd->m_tableHistory;
}

void ExistedCurveManager::addCurvesToTable()
{
    for (int i = 0; i < dd->m_curveList.size(); i++) {
        dd->m_plotHistory->addGraph();
        dd->m_plotHistory->graph(dd->m_plotHistory->graphCount() - 1)->setPen(QPen(dd->m_curveList.at(i)->color()));
        dd->m_plotHistory->graph(dd->m_plotHistory->graphCount() - 1)->setVisible(dd->m_curveList.at(i)->isDraw());
        dd->m_plotHistory->graph(dd->m_plotHistory->graphCount() - 1)->addData(dd->m_curveList.at(i)->sData()->keys,dd->m_curveList.at(i)->sData()->values);
        insertCurveRow(dd->m_curveList.at(i), dd->m_plotHistory->graph(dd->m_plotHistory->graphCount() - 1));
    }
    dd->m_plotHistory->replot();
    onBtnFitClicked();
    connect(dd->m_tableHistory, SIGNAL(itemEntered(QTableWidgetItem*)), this, SIGNAL(sendItemEnetered(QTableWidgetItem*)));
    connect(dd->m_tableHistory,SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(onCurveTableItemClicked(QTableWidgetItem*)));
    connect(dd->m_tableHistory,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(onCurveTableItemDoubleClicked(QTableWidgetItem*)));
    connect(dd->m_plotHistory,SIGNAL(currentPosChanged(QPointF)),this,SIGNAL(sendNewPos(QPointF)));
}

void ExistedCurveManager::insertTable(QVBoxLayout *layout, int index)
{
    layout->insertWidget(index, dd->m_tableHistory);
}

void ExistedCurveManager::insertPlot(QVBoxLayout *layout, int index)
{
    layout->insertWidget(index, dd->m_plotHistory);
}

void ExistedCurveManager::removeTable(QVBoxLayout *layout)
{
    layout->removeWidget(dd->m_tableHistory);
}

void ExistedCurveManager::removePlot(QVBoxLayout *layout)
{
    layout->removeWidget(dd->m_plotHistory);
}

void ExistedCurveManager::initUi()
{
    int curveTableWidth = 250;
    int columnCount = 3;
    dd->m_tableHistory->setColumnCount(columnCount);
    dd->m_tableHistory->setMinimumWidth(curveTableWidth);
    dd->m_tableHistory->setEditTriggers(QAbstractItemView::NoEditTriggers);
    dd->m_tableHistory->setAlternatingRowColors(true);
    dd->m_tableHistory->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QStringList headerList;
    //headerList<<tr("checked")<<tr("name")<<tr("axis")<<tr("dev");
    headerList<<tr("checked")<<tr("name")<<tr("axis");
    dd->m_tableHistory->setHorizontalHeaderLabels(headerList);
    dd->m_tableHistory->setMouseTracking(true);

    dd->m_plotHistory->xAxis2->setVisible(false);
    dd->m_plotHistory->xAxis2->setTickLabels(false);
    dd->m_plotHistory->yAxis2->setVisible(false);
    dd->m_plotHistory->yAxis2->setTickLabels(false);
    dd->m_plotHistory->setBackground(QBrush(QColor(240,240,240)));
    dd->m_plotHistory->setOpenGl(false);
}

void ExistedCurveManager::insertCurveRow(ICurve *curve, QCPGraph *graph)
{
    int rowCount = dd->m_tableHistory->rowCount();
    dd->m_tableHistory->insertRow(rowCount);

    QString str;
    QColor color;

    for (int nCol = 0; nCol < COL_TABLE_CURVE_SIZE; nCol++)
    {
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        switch (nCol)
        {
            case COL_TABLE_CURVE_SHOW:
            {
                if(curve->isDraw())
                {
                    str = tr("on");
                    color = dd->m_backShowColor;
                    item->setTextColor(dd->m_showColor);
                }
                else
                {
                    str = tr("off");
                    color = dd->m_backHideColor;
                    item->setTextColor(dd->m_hideColor);
                }
                item->setBackgroundColor(color);
            }
            break;

            case COL_TABLE_CURVE_NAME:
            {
                str = curve->displayName();
                color = curve->color();
                item->setTextColor(color);
            }
            break;

            case COL_TABLE_CURVE_AXIS:
            {
                str = QString::number(curve->axisInx() + 1);
            }
            break;
            default:
            break;
        }
        QVariant v;
        v.setValue(curve);
        item->setData(ROLE_TABLE_CURVE_ICURVE_PTR, v);
        QVariant v2;
        v2.setValue(graph);
        item->setData(ROLE_TABLE_CURVE_GRAPH_PTR, v2);
        item->setText(str);
        dd->m_tableHistory->setItem(rowCount, nCol, item);
    }
}

void ExistedCurveManager::getTableColor(const QColor &showColor, const QColor &backShowColor, const QColor &hideColor, const QColor &backHideColor)
{
    dd->m_backHideColor = backHideColor;
    dd->m_backShowColor = backShowColor;
    dd->m_showColor = showColor;
    dd->m_hideColor = hideColor;
}

void ExistedCurveManager::onCurveTableItemClicked(QTableWidgetItem *item)
{
    if(item->column() == COL_TABLE_CURVE_SHOW)
    {
      int row = item->row();
      QString str;
      QColor color;
      ICurve *curve = item->data(ROLE_TABLE_CURVE_ICURVE_PTR).value<ICurve *>();
      if(curve->isDraw())
      {
        str = tr("off");
        color = dd->m_backHideColor;
        curve->setIsDraw(false);
      }
      else
      {
        str = tr("on");
        color = dd->m_backShowColor;
        curve->setIsDraw(true);
      }
      item->setText(str);
      item->setBackgroundColor(color);
      dd->m_plotHistory->graph(row)->setVisible(curve->isDraw());
      dd->m_plotHistory->replot();
    }
}

void ExistedCurveManager::onCurveTableItemDoubleClicked(QTableWidgetItem *item)
{
    if (item->column() == COL_TABLE_CURVE_NAME)
    {
        int row = item->row();
        ICurve *curve = item->data(ROLE_TABLE_CURVE_ICURVE_PTR).value<ICurve *>();
        QColor clr = curve->color();
        clr = QColorDialog::getColor(clr);
        if (clr.isValid())
        {
            curve->setColor(clr);
            item->setTextColor(clr);
            dd->m_plotHistory->graph(row)->setPen(QPen(clr));
            dd->m_plotHistory->replot();
        }
    }
}

void ExistedCurveManager::onBtnMeaHClicked(bool checked)
{
  if(checked)
    dd->m_plotHistory->createVertiMea();
  else
    dd->m_plotHistory->clearVertiMea();
}

void ExistedCurveManager::onBtnMeaVClicked(bool checked)
{
  if(checked)
    dd->m_plotHistory->createHorizMea();
  else
    dd->m_plotHistory->clearHorizMea();
}

void ExistedCurveManager::onBtnFitClicked()
{
  dd->m_plotHistory->rescaleAxes(true);

  double low = dd->m_plotHistory->yAxis->range().lower;
  double upper = dd->m_plotHistory->yAxis->range().upper;
  double size = dd->m_plotHistory->yAxis->range().size();
  double dsize = 0.1*size;
  QCPRange plottableRange(low - dsize,upper + dsize);
  //qDebug()<<"before:"<<dd->m_plotHistory->yAxis->range().lower<<dd->m_plotHistory->yAxis->range().upper<<dd->m_plotHistory->yAxis->range().size();
  dd->m_plotHistory->yAxis->setRange(plottableRange);
  //qDebug()<<"after:"<<dd->m_plotHistory->yAxis->range().lower<<dd->m_plotHistory->yAxis->range().upper<<dd->m_plotHistory->yAxis->range().size();
  dd->m_plotHistory->replot();
}

void ExistedCurveManager::onBtnCurveShowAllClicked()
{
  static bool checked = false;
  ICurve *c = NULL;
  QCPGraph *graph = NULL;
  for(int row = 0; row < dd->m_tableHistory->rowCount(); row++)
  {
    QTableWidgetItem *item = dd->m_tableHistory->item(row,COL_TABLE_CURVE_NAME);
    c = item->data(ROLE_TABLE_CURVE_ICURVE_PTR).value<ICurve *>();
    c->setIsDraw(checked);
    graph = item->data(ROLE_TABLE_CURVE_GRAPH_PTR).value<QCPGraph *>();
    graph->setVisible(checked);
    setUiStatusCurveTableWidgetOnOff(row,checked);
  }
  checked = !checked;
  dd->m_plotHistory->replot();
}

void ExistedCurveManager::setUiStatusCurveTableWidgetOnOff(int row, bool on)
{
  if(on)
  {
    dd->m_tableHistory->item(row,COL_TABLE_CURVE_SHOW)->setText(tr("on"));
    dd->m_tableHistory->item(row,COL_TABLE_CURVE_SHOW)->setTextColor(dd->m_showColor);
    dd->m_tableHistory->item(row,COL_TABLE_CURVE_SHOW)->setBackgroundColor(dd->m_backShowColor);
  }
  else
  {
    dd->m_tableHistory->item(row,COL_TABLE_CURVE_SHOW)->setText(tr("off"));
    dd->m_tableHistory->item(row,COL_TABLE_CURVE_SHOW)->setTextColor(dd->m_hideColor);
    dd->m_tableHistory->item(row,COL_TABLE_CURVE_SHOW)->setBackgroundColor(dd->m_backHideColor);
  }
}
