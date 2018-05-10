#include "plotunitgraph129.h"
#include "ui_plotunitgraph129.h"
#include "iplotunitgraph_p.h"
#include "Option"
#include "gtutils.h"
#include "sdtglobaldef.h"
#include "sevdevice.h"
#include "tabctlpanel129.h"
#include "plottabctlprms.h"
#include "dialogpickcurve.h"
#include "sdtglobaldef.h"
#include "curvemanager.h"
#include "curvetableaxisitem.h"
#include "threadsample.h"
#include "threadcalculate.h"

#include "pluginsmanager.h"
#include "icurve.h"

#include <QDebug>
#include <QTimer>
#include <QEvent>
#include <QTreeWidgetItem>
#include <QMultiHash>

#define TEST_DEBUG 1

#define ICON_NAME_ADD       "plot_add.png"
#define ICON_NAME_ALL       "plot_all.png"
#define ICON_NAME_AUTO      "plot_auto.png"
#define ICON_NAME_CLEAR     "plot_clear.png"
#define ICON_NAME_MEAH      "plot_meaH.png"
#define ICON_NAME_MEAV      "plot_meaV.png"
#define ICON_NAME_SOFF      "plot_soff.png"
#define ICON_NAME_SON       "plot_son.png"
#define ICON_NAME_START     "plot_start.png"
#define ICON_NAME_STOP      "plot_stop.png"
#define ICON_NAME_CONFIG    "plot_config.png"
#define ICON_NAME_FIT       "plot_fit.png"
#define ICON_NAME_TAG       "plot_tag.png"
#define ICON_NAME_OPEN      "plot_open.png"
#define ICON_NAME_SAVE      "plot_save.png"
#define ICON_NAME_EXTEND    "plot_extend.png"
#define ICON_NAME_SHRINK    "plot_shrink.png"

#define ICON_NAME_CURVE_ALL    "plot_all.png"
#define ICON_NAME_CURVE_ADD    "plot_add.png"
#define ICON_NAME_CURVE_REMOVE "plot_remove.png"
#define ICON_NAME_CURVE_CLEAR  "plot_clear.png"

#define CURVE_MAX_NUM           16

class VarCurvePrm
{
public:
  int axis;
  CurvePrm varPrm;
};

typedef enum {
  COL_TABLE_CURVE_SHOW,
  COL_TABLE_CURVE_NAME,
  COL_TABLE_CURVE_AXIS,
  COL_TABLE_CURVE_DEV,
  COL_TABLE_CURVE_SIZE
}TableCurveColumnInx;

typedef enum{
  ROLE_TABLE_CURVE_ICURVE_PTR = Qt::UserRole+1,
  ROLE_TABLE_CURVE_GRAPH_PTR = Qt::UserRole+2
}CurveTableDataRole;

//为了QTreeTable 里面包裸ICurve * 指针
Q_DECLARE_METATYPE(ICurve*)
Q_DECLARE_METATYPE(QCPGraph *)

class PlotUnitGraph129Private:public IPlotUnitGraphPrivate
{
  Q_DECLARE_PUBLIC(PlotUnitGraph129)
public:
  PlotUnitGraph129Private():m_pluginManager(NULL),
    m_timer(NULL),
    m_showColor(QColor(Qt::white)),
    m_backShowColor(QColor(Qt::green).darker()),
    m_hideColor(QColor(Qt::white)),
    m_backHideColor(QColor(Qt::gray)),
    m_threadSample(NULL),
    m_threadCalcultate(NULL)
  {

  }
  ~PlotUnitGraph129Private(){}
protected:
  friend class PlotUnitGraph129;
  QList<PlotTabCtlPrms*>m_ctlPrms;//每个设备对应一个
  QList<TabCtlPanel129 *>m_tabCtl;
  QTimer *m_timer;
  PluginsManager *m_pluginManager;
  CurveManager *m_curveManager;
  QColor m_showColor;
  QColor m_backShowColor;
  QColor m_hideColor;
  QColor m_backHideColor;
  ThreadSample *m_threadSample;
  ThreadCalculate *m_threadCalcultate;
};

PlotUnitGraph129::PlotUnitGraph129(const QList<SevDevice *> &sevList, QWidget *parent) :
  IPlotUnitGraph(*(new PlotUnitGraph129Private),parent),
  ui(new Ui::PlotUnitGraph129)
{
  Q_D(PlotUnitGraph129);
  d->m_sevList=sevList;

  ui->setupUi(this);
//  connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(onPushButtonTestClicked(bool)));
  ui->splitter_plot_tab->setStretchFactor(0,1);
  ui->splitter_plot_tab->setStretchFactor(1,0);
  ui->splitter_plot_curve->setStretchFactor(0,1);
  ui->splitter_plot_curve->setStretchFactor(1,0);

  ui->tbtn_plot_floatin->setCheckable(true);
  ui->tbtn_plot_floatin->setChecked(true);
  ui->tbtn_plot_startSampling->setCheckable(true);
  ui->tbtn_plot_startSampling->setChecked(false);
  ui->tbtn_plot_mea_horizontal->setCheckable(true);
  ui->tbtn_plot_mea_vertical->setCheckable(true);
  ui->tbtn_plot_auto->setCheckable(true);
  ui->tbtn_plot_auto->setChecked(false);

  d->m_timer=new QTimer(this);
  d->m_timer->setInterval(1000);

  while(ui->stackedWidget_tabCtlPanel->count()>0)
  {
    QWidget *w=ui->stackedWidget_tabCtlPanel->widget(0);
    ui->stackedWidget_tabCtlPanel->removeWidget(w);
  }
  //加载插件
  bool loadPluginOk=true;
  d->m_pluginManager=new PluginsManager(this);
  loadPluginOk=d->m_pluginManager->loadPlugins();
  if(!loadPluginOk)
    QMessageBox::information(0,tr("error"),tr("load plugin error!\n"));

  d->m_curveManager=new CurveManager(this);


  //曲线表格初始化
  int curveTableWidth = 250;
  int columnCount=4;
//  if(sevList.size()>1)
//    columnCount=4;
  ui->tableWidget_plot_curve->setColumnCount(columnCount);
  ui->tableWidget_plot_curve->setMinimumWidth(curveTableWidth);
  ui->tableWidget_plot_curve->setEditTriggers(QAbstractItemView::NoEditTriggers);//编辑触发模式
  ui->tableWidget_plot_curve->setAlternatingRowColors(true);
  ui->tableWidget_plot_curve->setContextMenuPolicy(Qt::CustomContextMenu);//设置其右键弹出菜单方法
//  connect(ui->tableWidget,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(onTablePopMenu(QPoint)));
//  m_popuMenuTable=new QMenu(this);
//  addTableMenuAction(mp_userConfig->model.axisCount);//初始化m_popuMenuTable 右键弹出QAction
  QStringList headerList;
  headerList<<tr("checked")<<tr("name")<<tr("axis")<<tr("dev");
  ui->tableWidget_plot_curve->setHorizontalHeaderLabels(headerList);
//  ui->tableWidget_plot_curve->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//  ui->tableWidget_plot_curve->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
  ui->tableWidget_plot_curve->setMouseTracking(true);
  resizeSectionCurveTableWidget(sevList);

  ui->label_plot_detailName->setMaximumWidth(250);
  ui->label_plot_detailName->setWordWrap(true);
  ui->label_plot_detailName->setAlignment(Qt::AlignTop|Qt::AlignLeft);


  gtPlotInit();
  ctlPanelInit();

  OptFace *face=dynamic_cast<OptFace *>(OptContainer::instance()->optItem("optface"));
  setPlotIcons(face->css());
  createConnections();
}

PlotUnitGraph129::~PlotUnitGraph129()
{
  delete ui;
}

void PlotUnitGraph129::respondUiActive(bool actived)
{
  Q_D(PlotUnitGraph129);
  d->m_isActiving=actived;
  qDebug()<<"respond Ui active "<<actived;
  setTimerStatus();
}

QColor PlotUnitGraph129::curveShowColor() const
{
  Q_D(const PlotUnitGraph129);
  return d->m_showColor;
}

void PlotUnitGraph129::setCurveShowColor(const QColor &color)
{
  Q_D(PlotUnitGraph129);
  d->m_showColor=color;
}

QColor PlotUnitGraph129::curveBackShowColor() const
{
  Q_D(const PlotUnitGraph129);
  return d->m_backShowColor;
}

void PlotUnitGraph129::setCurveBackShowColor(const QColor &color)
{
  Q_D(PlotUnitGraph129);
  d->m_backShowColor=color;
}

QColor PlotUnitGraph129::curveHideColor() const
{
  Q_D(const PlotUnitGraph129);
  return d->m_hideColor;
}

void PlotUnitGraph129::setCurveHideColor(const QColor &color)
{
  Q_D(PlotUnitGraph129);
  d->m_hideColor=color;
}

QColor PlotUnitGraph129::curveBackHideColor() const
{
  Q_D(const PlotUnitGraph129);
  return d->m_backHideColor;
}

void PlotUnitGraph129::setCurveBackHideColor(const QColor &color)
{
  Q_D(PlotUnitGraph129);
  d->m_backHideColor=color;
}

void PlotUnitGraph129::resizeSectionCurveTableWidget(const QList<SevDevice *> &sevlist)
{
  int columnWidth;
  if(sevlist.size()>1)
    columnWidth=(ui->tableWidget_plot_curve->minimumWidth()-10)/4;
  else
    columnWidth=(ui->tableWidget_plot_curve->minimumWidth()-10)/3;
  for(int i=0;i<4;i++)
    ui->tableWidget_plot_curve->horizontalHeader()->resizeSection(i,columnWidth);
}

void PlotUnitGraph129::onSevDeviceListChanged(const QList<SevDevice *> &sevlist)
{
  Q_D(PlotUnitGraph129);

  d->m_sevList=sevlist;
  d->m_timer->stop();
  ctlPanelInit();
  resizeSectionCurveTableWidget(sevlist);
  checkCurveValid();

  for(int i = 0;i<sevlist.size();i++)
    connect(sevlist.at(i),SIGNAL(connectionChanged(bool)),this,SLOT(onSocketConnectionChanged(bool)));

}

void PlotUnitGraph129::onAppClosed()
{
  //关闭画图
  //保存当前曲线列表信息
  onBtnStartSampleClicked(false);
  ui->tbtn_plot_startSampling->setChecked(false);
  qDebug()<<"-------PlotUnitGraph129 appclose ---------";
}

void PlotUnitGraph129::onSocketConnectionChanged(bool isConnected)
{
  qDebug()<<"socket connection changed "<<isConnected;
  if(!isConnected)
  {
    if(ui->tbtn_plot_startSampling->isChecked())
    {
      ui->tbtn_plot_startSampling->setChecked(false);
      onBtnStartSampleClicked(false);
    }
  }
}

void PlotUnitGraph129::createConnections()
{
  Q_D(PlotUnitGraph129);
  for(int i = 0;i<d->m_sevList.size();i++)
    connect(d->m_sevList.at(i),SIGNAL(connectionChanged(bool)),this,SLOT(onSocketConnectionChanged(bool)));

  connect(ui->tbtn_plot_floatin,SIGNAL(clicked(bool)),this,SLOT(onBtnFloatInClicked(bool)));
  OptFace *face=dynamic_cast<OptFace *>(OptContainer::instance()->optItem("optface"));
  connect(face,SIGNAL(faceCssChanged(QString)),this,SLOT(onOptFaceCssChanged(QString)));
  connect(ui->tbtn_plot_mea_horizontal,SIGNAL(clicked(bool)),this,SLOT(onBtnMeaHClicked(bool)));
  connect(ui->tbtn_plot_mea_vertical,SIGNAL(clicked(bool)),this,SLOT(onBtnMeaVClicked(bool)));
  connect(ui->tbtn_plot_fit,SIGNAL(clicked(bool)),this,SLOT(onBtnFitClicked()));
  connect(ui->tbtn_plot_startSampling,SIGNAL(clicked(bool)),this,SLOT(onBtnStartSampleClicked(bool)));

  connect(ui->plot,SIGNAL(currentPosChanged(QPointF)),this,SLOT(onPlotPosHoverChanged(QPointF)));
  connect(ui->plot,SIGNAL(horizMeaDataChanged(qreal,qreal,qreal)),this,SLOT(onPlotMeaHposChanged(qreal,qreal,qreal)));
  connect(ui->plot,SIGNAL(vertiMeaDataChanged(qreal,qreal,qreal)),this,SLOT(onPlotMeaVposChanged(qreal,qreal,qreal)));

  connect(d->m_timer,SIGNAL(timeout()),this,SLOT(onTimeOut()));

  connect(ui->listWidget_plot_device,SIGNAL(currentRowChanged(int)),this,SLOT(onListWidgetDeviceCurrentRowChanged(int)));

  connect(ui->tbtn_plot_curveAdd,SIGNAL(clicked(bool)),this,SLOT(onBtnCurveAddClicked()));
  connect(ui->tbtn_plot_curveAll,SIGNAL(clicked(bool)),this,SLOT(onBtnCurveShowAllClicked()));
  connect(ui->tbtn_plot_curveClear,SIGNAL(clicked(bool)),this,SLOT(onBtnCurveClearClicked()));
  connect(ui->tbtn_plot_curveRemove,SIGNAL(clicked(bool)),this,SLOT(onBtnCurveRemoveClicked()));
  connect(ui->tableWidget_plot_curve,SIGNAL(itemEntered(QTableWidgetItem*)),this,SLOT(onCurveTableItemEnteredMoreDetail(QTableWidgetItem*)));
  connect(ui->tableWidget_plot_curve,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(onCurveTableItemClicked(QTableWidgetItem*)));
  connect(ui->tableWidget_plot_curve,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(onCurveTableItemDoubleClicked(QTableWidgetItem*)));

  connect(this,SIGNAL(winFloatingChange(bool)),this,SLOT(onWinFloatingChanged(bool)));
  //  //tab mode

  //  //tab motion
}
void PlotUnitGraph129::onBtnFloatInClicked(bool checked)
{
  Q_UNUSED(checked);
  Q_D(PlotUnitGraph129);
  d->m_winIsIn=!d->m_winIsIn;
  setTimerStatus();
  emit winFloatingChange(d->m_winIsIn);
}

void PlotUnitGraph129::onOptFaceCssChanged(const QString &css)
{
  Q_D(PlotUnitGraph129);

  setPlotIcons(css);

  for(int i=0;i<d->m_tabCtl.size();i++)
  {
    d->m_tabCtl.at(i)->setupIcons(css);
  }
}

void PlotUnitGraph129::onWinFloatingChanged(bool isFloating)
{
  ui->tbtn_plot_floatin->setChecked(isFloating);
}

void PlotUnitGraph129::onBtnMeaHClicked(bool checked)
{
  if(checked)
    ui->plot->createVertiMea();
  else
    ui->plot->clearVertiMea();
}

void PlotUnitGraph129::onBtnMeaVClicked(bool checked)
{ 
  if(checked)
    ui->plot->createHorizMea();
  else
    ui->plot->clearHorizMea();
}

void PlotUnitGraph129::onBtnFitClicked()
{
  ui->plot->rescaleAxes(true);
  ui->plot->replot();
}

void PlotUnitGraph129::onBtnStartSampleClicked(bool checked)
{
  Q_D(PlotUnitGraph129);
  if(currentSevDevice()->isConnecting() == false)
  {
    ui->tbtn_plot_startSampling->setChecked(false);
    return;
  }

  if(checked)
  {
    clearGraphData();
    //检查曲线参数有效性
//    checkCurveValid();

    qDebug()<<"sampleScale "<<ui->comboBox_plot_sampling->currentText().toInt();
    d->m_curveManager->setSampleScale(ui->comboBox_plot_sampling->currentText().toInt());
    d->m_curveManager->setStoreTime(60);
    d->m_curveManager->updateSamplPrms();
    //读取所有曲线静态变量

    d->m_threadSample = new ThreadSample(d->m_sevList,d->m_curveManager->samplPrms());
    d->m_threadCalcultate = new ThreadCalculate(d->m_curveManager->devCurves());
    connect(d->m_threadSample,SIGNAL(sampleDataIn(SampleData)),d->m_threadCalcultate,SIGNAL(sampleDataIn(SampleData)));
    connect(d->m_threadCalcultate,SIGNAL(plotDataIn(PlotData)),this,SLOT(onPlotDataIn(PlotData)));
    d->m_threadCalcultate->start();
    d->m_threadSample->start();
    qDebug()<<"start thread sample ";
  }
  else
  {
    if(d->m_threadSample == NULL)
      return ;
    disconnect(d->m_threadSample,SIGNAL(sampleDataIn(SampleData)),d->m_threadCalcultate,SIGNAL(sampleDataIn(SampleData)));
    disconnect(d->m_threadCalcultate,SIGNAL(plotDataIn(PlotData)),this,SLOT(onPlotDataIn(PlotData)));
    d->m_threadSample->deleteLater();
    d->m_threadCalcultate->deleteLater();
    d->m_threadSample = NULL;
    d->m_threadCalcultate = NULL;
    qDebug()<<"stop thread sample ";
  }
}

void PlotUnitGraph129::onPlotPosHoverChanged(const QPointF &point)
{
  ui->label_plot_x->setText(QString("X=%1 ms").arg(QString::number(point.x()*1000,'f',2)));
  ui->label_plot_y->setText(QString(" Y=%1").arg(QString::number(point.y(),'f',2)));
}

void PlotUnitGraph129::onPlotMeaVposChanged(qreal v1, qreal v2, qreal dv)
{
  Q_UNUSED(v1);
  Q_UNUSED(v2);
  ui->label_plot_dy->setText(QString(" dY=%1").arg(QString::number(dv,'f',2)));
}

void PlotUnitGraph129::onPlotMeaHposChanged(qreal v1, qreal v2, qreal dv)
{
  Q_UNUSED(v1);
  Q_UNUSED(v2);
  ui->label_plot_dx->setText(QString("dX=%1 ms ,Freq=%2 HZ").arg(QString::number(dv*1000,'f',2)).arg(QString::number(1/dv,'f',2)));
}

void PlotUnitGraph129::onTimeOut()
{
//  Q_D(PlotUnitGraph129);
  static quint32 i=0;
//  qDebug()<<"time out"<<i;
  i++;
}

void PlotUnitGraph129::onListWidgetDeviceCurrentRowChanged(int row)
{
  Q_D(PlotUnitGraph129);
  d->m_curSevInx=row;
  qDebug()<<"updateCtlPanelBySelectDevice"<<row;
  updateCtlPanelBySelectDevice(row);
}

void PlotUnitGraph129::onBtnCurveAddClicked()
{
  Q_D(PlotUnitGraph129);
  DialogPickCurve *dia=new DialogPickCurve();
  SevDevice *dev=d->m_sevList.at(d->m_curSevInx);

  QTreeWidget *treeExpert=dev->axisTreeSource(0,"RAM");
  dia->addExpertTreeWidget(treeExpert);
  dia->setAxisTable(dev->axisNum());

  connect(dia,SIGNAL(expertTreeItemDoubleClicked(QTableWidget*,QTreeWidgetItem*)),this,SLOT(onExpertTreeWidgetDoubleClicked(QTableWidget*,QTreeWidgetItem*)));

  dia->exec();
  dia->deleteLater();
}

void PlotUnitGraph129::onExpertTreeWidgetDoubleClicked(QTableWidget *table,QTreeWidgetItem *item)
{
  if(item->childCount()>0) return;//不是叶子则返回
  int isBit;
  QString name;

  name=item->text(GT::COL_FLASH_RAM_TREE_NAME);

  isBit=item->text(GT::COL_FLASH_RAM_TREE_ISBIT).toInt();
  if(isBit==1)//判断是不是位，如果是位就不增加
  {
    QMessageBox::information(0,tr("warning"),tr("%1 is BIT").arg(name));
    return;
  }
  //找 bytes axisInx(more then one) offsetAddr

  QList<VarCurvePrm>varPrmList;

  for(int i=0;i<table->columnCount();i++)
  {
    if(table->item(0,i)->isSelected())
    {
      VarCurvePrm var; 
      var.axis=i;
      var.varPrm.bytes=GTUtils::byteNumbers(item->text(GT::COL_FLASH_RAM_TREE_TYPE));
      var.varPrm.baseAddr=0;
      var.varPrm.offtAddr=item->text(GT::COL_FLASH_RAM_TREE_ADDR).toUShort();
      varPrmList.append(var);
    }
  }

  int axisInx;
  //检查该曲线名在对应的轴中有没有这个变量
  QVector<int> needRemoveVec;
  needRemoveVec.clear();
  for(int i=0;i<varPrmList.count();i++)
  {
    axisInx=varPrmList.at(i).axis;
    if(axisInx%2!=0)//0 2 4不检查 1 3 5检查
    {
      QTreeWidget *ramTree=currentSevDevice()->axisTreeSource(axisInx,"RAM");
      QTreeWidgetItem *item=GTUtils::findItem(name,ramTree,GT::COL_FLASH_RAM_TREE_NAME);
      if(NULL==item)
      {
        needRemoveVec.append(axisInx);
        qDebug()<<"can not find curve :"<<name<<"in axis "<<axisInx;
      }
      else//更新地址
      {
        varPrmList[i].varPrm.offtAddr=item->text(GT::COL_FLASH_RAM_TREE_ADDR).toUShort();
      }
      qDebug()<<"axis "<<axisInx<<"find item"<<item->text(GT::COL_FLASH_RAM_TREE_NAME);
    }
  }
  qDebug()<<"need remove vector size "<<needRemoveVec.size();
  QMutableListIterator<VarCurvePrm> it(varPrmList);
  for(int i=0;i<needRemoveVec.size();i++)
  {
    int axisInx = needRemoveVec.at(i);

    while (it.hasNext()) {
      if(it.next().axis==axisInx)
        it.remove();
    }
  }


  //判断 下放曲线条数是否大于16条，将多余的移除
  Q_D(PlotUnitGraph129);
  int totalCount;
  totalCount=d->m_curveManager->varCurveTotalCount()+varPrmList.count();
  int dCount=totalCount-CURVE_MAX_NUM;
  bool isOver=false;
  while(dCount>0)
  {
    isOver=true;
    varPrmList.removeLast();
    dCount--;
  }
  if(isOver)
    QMessageBox::information(0,tr("warning"),tr("The numbers of selected curves is too much"));



#if TEST_DEBUG
  for(int i=0;i<varPrmList.count();i++)
  {
    qDebug()<<"add curve axis = "<<varPrmList.at(i).axis;
    qDebug()<<"bytes"<<varPrmList.at(i).varPrm.bytes<<" offset"<<varPrmList.at(i).varPrm.offtAddr<<" base"<<varPrmList.at(i).varPrm.baseAddr;

  }
#endif


  ICurve *curve;
  int curveCount=d->m_curveManager->curveList().count();
  int curveTotalSize;
  for(int i=0;i<varPrmList.count();i++)
  {
    axisInx=varPrmList.at(i).axis;
    curveTotalSize=curveCount+i;
    //生成曲线对象
    curve=d->m_pluginManager->expertCurve()->clone();
//    curve->prepare();
    curve->setAxisInx(axisInx);
    curve->setDevInx(d->m_curSevInx);
    curve->setName(name);
    curve->setNote("");
//    curve->setSamplInterval(62.5);//这里还要从Option-plot里读取
//    curve->setStorePointCount(10/62.5*1000000);//这里还要从Option-plot里读取
    curve->setColor(d->m_curveManager->color(curveTotalSize));
    curve->addVarInputByName(name);
    curve->fillVarInputsPrm(0,varPrmList.at(i).varPrm);
    curve->setAxisCount(currentSevDevice()->axisNum());
    d->m_curveManager->addCurve(curve);


    //gtplot增加曲线
    ui->plot->addGraph();
    ui->plot->graph(curveTotalSize)->setPen(curve->color());

    //表格增加曲线标识
    addTableRowPrm(curve,ui->plot->graph(curveTotalSize));

    qDebug()<<QString("add curve =%1 devInx=%2 dspInx=%3 varSize=%4").arg(curve->fullName()).arg(curve->devInx()).arg(curve->dspInx()).arg(curve->varInputsKeys().size());
  }

  qDebug()<<"curve total size ="<<d->m_curveManager->curveList().size();

}

void PlotUnitGraph129::onBtnCurveRemoveClicked()
{
  int row=ui->tableWidget_plot_curve->currentRow();
  if(row>=0)
  {
    Q_D(PlotUnitGraph129);
    ui->plot->removeGraph(row);
    d->m_curveManager->removeCurve(row);
    ui->tableWidget_plot_curve->removeRow(row);
    ui->plot->replot();
  }
}

void PlotUnitGraph129::onBtnCurveClearClicked()
{
  Q_D(PlotUnitGraph129);
  if(d->m_curveManager->curveList().size()>0)
  {
    d->m_curveManager->clearCurve();
    ui->plot->clearGraphs();
    ui->tableWidget_plot_curve->setRowCount(0);
    ui->tableWidget_plot_curve->clearContents();
    ui->plot->replot();
  }
}

void PlotUnitGraph129::onBtnCurveShowAllClicked()
{
//  Q_D(PlotUnitGraph129);
//  for(int i=0;i<d->m_pluginManager->usrCurves().size();i++)
//  {
//    qDebug()<<d->m_pluginManager->usrCurves().at(i)->name()<<d->m_pluginManager->usrCurves().at(i)->fullName();
//  }

//  if(ui->tbtn_plot_startSampling->isChecked())
//  {
//    ui->tbtn_plot_startSampling->setChecked(false);
//    onBtnStartSampleClicked(false);
//  }

  showAllData();
}

void PlotUnitGraph129::onCurveTableItemClicked(QTableWidgetItem *item)
{
  if(item->column() == COL_TABLE_CURVE_SHOW)
  {
    Q_D(PlotUnitGraph129);
    int row = item->row();
    QString str;
    QColor color;
    ICurve *curve=item->data(ROLE_TABLE_CURVE_ICURVE_PTR).value<ICurve *>();
    if(curve->isDraw())
    {
      str=tr("off");
      color=d->m_backHideColor;
      curve->setIsDraw(false);
    }
    else
    {
      str=tr("on");
      color=d->m_backShowColor;
      curve->setIsDraw(true);
    }
    item->setText(str);
    item->setBackgroundColor(color);
    ui->plot->graph(row)->setVisible(curve->isDraw());
    ui->plot->replot();
  }
}

void PlotUnitGraph129::onCurveTableItemDoubleClicked(QTableWidgetItem *item)
{
  if(item->column()==COL_TABLE_CURVE_NAME)
  {
    int row=item->row();
    ICurve *curve=item->data(ROLE_TABLE_CURVE_ICURVE_PTR).value<ICurve *>();
    QColor clr=curve->color();
    clr=QColorDialog::getColor(clr);
    if(clr.isValid())
    {
      curve->setColor(clr);
      item->setTextColor(clr);
      ui->plot->graph(row)->setPen(QPen(clr));
      ui->plot->replot();
      qDebug()<<"double clicked -------------select color"<<clr;
    }
  }
}

void PlotUnitGraph129::onCurveTableItemEnteredMoreDetail(QTableWidgetItem * item)
{
  if(item->column() == COL_TABLE_CURVE_NAME)
  {
    ICurve *curve=item->data(ROLE_TABLE_CURVE_ICURVE_PTR).value<ICurve *>();
    ui->label_plot_detailName->setText(curve->fullName());
  }
}

void PlotUnitGraph129::onPlotDataIn(PlotData data)
{
  static quint64 count = 0;
  ICurve *c = NULL;
  double lastkeyValue =0;
  for(int i=0;i<data.m_dataHash.keys().size();i++)
  {
    c=data.m_dataHash.keys().at(i);
    int row = -1;
    for(int j=0;j<ui->tableWidget_plot_curve->rowCount();j++)
    {
      ICurve *curve=ui->tableWidget_plot_curve->item(j,COL_TABLE_CURVE_NAME)->data(ROLE_TABLE_CURVE_ICURVE_PTR).value<ICurve *>();
      if(curve==c)
      {
        row=j;
        break;
      }
    }
    if(row != -1)
    {
      quint8 storeTimeS=20;
      ui->plot->graph(row)->addData(data.m_dataHash.value(c).keys,data.m_dataHash.value(c).values);
      ui->plot->graph(row)->data()->removeBefore(data.m_dataHash.value(c).keys.last() - storeTimeS);
//      ui->plot->graph(row)->removeDataBefore(data.m_dataHash.value(c).keys.last() - storeTimeS);
      lastkeyValue=data.m_dataHash.value(c).keys.last();
//      qDebug()<<"i = "<<i<<" last key = "<<lastkeyValue;
    }
  }
  count ++;
  if(count%4 == 0)
  {
    ui->plot->xAxis->setRange(lastkeyValue, 2, Qt::AlignRight);
    ui->plot->replot();
  }
  if(ui->tbtn_plot_auto->isChecked()&&(count%10 == 0))
  {
    ui->plot->rescaleAxes(true);
  }

}

void PlotUnitGraph129::setPlotIcons(const QString &css)
{
  QSize iconSize(24,24);
  QString iconPath=GTUtils::customPath()+"option/style/"+css+"/icon/";
  QIcon samplStartIcon;
  samplStartIcon.addPixmap(QPixmap(iconPath+ICON_NAME_START),QIcon::Selected,QIcon::Off);
  samplStartIcon.addPixmap(QPixmap(iconPath+ICON_NAME_STOP),QIcon::Selected,QIcon::On);
  ui->tbtn_plot_startSampling->setIcon(samplStartIcon);
  ui->tbtn_plot_startSampling->setIconSize(iconSize);

  QIcon floatIcon;
  floatIcon.addPixmap(QPixmap(iconPath+ICON_NAME_EXTEND),QIcon::Selected,QIcon::On);
  floatIcon.addPixmap(QPixmap(iconPath+ICON_NAME_SHRINK),QIcon::Selected,QIcon::Off);
  ui->tbtn_plot_floatin->setIcon(floatIcon);
  ui->tbtn_plot_floatin->setIconSize(iconSize);

  ui->tbtn_plot_auto->setIcon(QIcon(QPixmap(iconPath+ICON_NAME_AUTO)));
  ui->tbtn_plot_auto->setIconSize(iconSize);

  ui->tbtn_plot_fit->setIcon(QIcon(QPixmap(iconPath+ICON_NAME_FIT)));
  ui->tbtn_plot_fit->setIconSize(iconSize);

  ui->tbtn_plot_mea_horizontal->setIcon(QIcon(QPixmap(iconPath+ICON_NAME_MEAH)));
  ui->tbtn_plot_mea_horizontal->setIconSize(iconSize);

  ui->tbtn_plot_mea_vertical->setIcon(QIcon(QPixmap(iconPath+ICON_NAME_MEAV)));
  ui->tbtn_plot_mea_vertical->setIconSize(iconSize);

  ui->tbtn_plot_open->setIcon(QIcon(QPixmap(iconPath+ICON_NAME_OPEN)));
  ui->tbtn_plot_open->setIconSize(iconSize);

  ui->tbtn_plot_save->setIcon(QIcon(QPixmap(iconPath+ICON_NAME_SAVE)));
  ui->tbtn_plot_save->setIconSize(iconSize);

  ui->tbtn_plot_curveAll->setIcon(QIcon(QPixmap(iconPath+ICON_NAME_CURVE_ALL)));
  ui->tbtn_plot_curveAll->setIconSize(iconSize);

  ui->tbtn_plot_curveAdd->setIcon(QIcon(QPixmap(iconPath+ICON_NAME_CURVE_ADD)));
  ui->tbtn_plot_curveAdd->setIconSize(iconSize);

  ui->tbtn_plot_curveRemove->setIcon(QIcon(QPixmap(iconPath+ICON_NAME_CURVE_REMOVE)));
  ui->tbtn_plot_curveRemove->setIconSize(iconSize);

  ui->tbtn_plot_curveClear->setIcon(QIcon(QPixmap(iconPath+ICON_NAME_CURVE_CLEAR)));
  ui->tbtn_plot_curveClear->setIconSize(iconSize);

//  qDebug()<<"PlotUnitGraph129 css changed"<<css<<iconPath;
}

void PlotUnitGraph129::gtPlotInit()
{
//  setupSimpleDemo(ui->plot);
  ui->plot->xAxis2->setVisible(false);
  ui->plot->xAxis2->setTickLabels(false);
  ui->plot->yAxis2->setVisible(false);
  ui->plot->yAxis2->setTickLabels(false);
  ui->plot->setBackground(QBrush(QColor(240,240,240)));
}

void PlotUnitGraph129::ctlPanelInit()
{
  Q_D(PlotUnitGraph129);

  GT::deepClearList(d->m_tabCtl);
  ui->listWidget_plot_device->clear();

  for(int i=0;i<d->m_sevList.size();i++)
  {
    TabCtlPanel129 *panel=new TabCtlPanel129(d->m_sevList.at(i));
    d->m_tabCtl.append(panel);
    ui->stackedWidget_tabCtlPanel->addWidget(panel);
    ui->listWidget_plot_device->addItem(d->m_sevList.at(i)->aliasName());
  }
  d->m_curSevInx=0;
  ui->listWidget_plot_device->setCurrentRow(d->m_curSevInx);
  bool isShow=(d->m_sevList.count()>1);
  ui->widget_plot_device_nav->setVisible(isShow);
}

void PlotUnitGraph129::updateCtlPanelBySelectDevice(int sevInx)
{
  Q_D(PlotUnitGraph129);
  if(!(sevInx<d->m_sevList.size())||(sevInx==-1))
    return;

  ui->stackedWidget_tabCtlPanel->setCurrentIndex(sevInx);
}

void PlotUnitGraph129::setupSimpleDemo(QCustomPlot *customPlot)
{
  // add two new graphs and set their look:
  customPlot->addGraph();
  customPlot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
  customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue
  customPlot->addGraph();
  customPlot->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph
  // generate some points of data (y0 for first, y1 for second graph):
  QVector<double> x(251), y0(251), y1(251);
  for (int i=0; i<251; ++i)
  {
    x[i] = i;
    y0[i] = 100*qExp(-i/150.0)*qCos(i/10.0); // exponentially decaying cosine
    y1[i] = 100*qExp(-i/150.0);              // exponential envelope
  }
  // configure right and top axis to show ticks but no labels:
  // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
  customPlot->xAxis2->setVisible(true);
  customPlot->xAxis2->setTickLabels(false);
  customPlot->yAxis2->setVisible(true);
  customPlot->yAxis2->setTickLabels(false);
  // make left and bottom axes always transfer their ranges to right and top axes:
  connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
  connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
  // pass data points to graphs:
  customPlot->graph(0)->setData(x, y0);
  customPlot->graph(1)->setData(x, y1);
  // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
  customPlot->graph(0)->rescaleAxes();
  // same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
  customPlot->graph(1)->rescaleAxes(true);
  // Note: we could have also just called customPlot->rescaleAxes(); instead
  // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
  customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom );

  customPlot->setSelectionRectMode(QCP::srmNone);

  QCPItemStraightLine *line=new QCPItemStraightLine(customPlot);
  line->setSelectable(true);
  customPlot->setInteraction(QCP::iSelectItems,true);
  customPlot->setInteraction(QCP::iMultiSelect,true);

  QCPItemText *text=new QCPItemText(customPlot);
  text->setText("hello");
  text->position->setType(QCPItemPosition::ptPlotCoords);
  text->position->setCoords(50,100);
}

void PlotUnitGraph129::setTimerStatus()
{
  Q_D(PlotUnitGraph129);
  bool needOpen;
  needOpen=d->m_isActiving||(!d->m_winIsIn);
  qDebug()<<"needOpen = "<<needOpen;
  if(needOpen)
  {
    if(d->m_timer->isActive()==false)
      d->m_timer->start();
  }
  else
  {
    d->m_timer->stop();
  }
}

SevDevice *PlotUnitGraph129::currentSevDevice() const
{
  Q_D(const PlotUnitGraph129);
  return d->m_sevList.at(d->m_curSevInx);
}

void PlotUnitGraph129::addTableRowPrm(ICurve *curve, QCPGraph *graph)
{
  Q_D(PlotUnitGraph129);

  int rowCount=ui->tableWidget_plot_curve->rowCount();
  ui->tableWidget_plot_curve->insertRow(rowCount);

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
        str=tr("on");
        color=d->m_backShowColor;
        item->setTextColor(d->m_showColor);
      }
      else
      {
        str=tr("off");
        color=d->m_backHideColor;
        item->setTextColor(d->m_hideColor);
      }
      item->setBackgroundColor(color);
    }
    break;

    case COL_TABLE_CURVE_NAME:
    {
      str=curve->displayName();
      color=curve->color();
      item->setTextColor(color);
    }
    break;

    case COL_TABLE_CURVE_AXIS:
    {
      str=QString::number(curve->axisInx());
    }
    break;

    case COL_TABLE_CURVE_DEV:
    {
      str=curve->devName();
    }
    break;

    default:
    break;
    }
    QVariant v;
    v.setValue(curve);
    item->setData(ROLE_TABLE_CURVE_ICURVE_PTR,v);
    QVariant v2;
    v2.setValue(graph);
    item->setData(ROLE_TABLE_CURVE_GRAPH_PTR,v2);
    item->setText(str);
    ui->tableWidget_plot_curve->setItem(rowCount, nCol, item);
  }
}

void PlotUnitGraph129::clearGraphData()
{
  int graphCount =  ui->plot->graphCount();

  for(int i=0;i<graphCount;i++)
  {
    ui->plot->graph(i)->data()->clear();
  }
  ui->plot->rescaleAxes(true);
  ui->plot->replot(QCustomPlot::rpImmediateRefresh);
}

typedef QList<ICurve *> QICurveList;

void PlotUnitGraph129::checkCurveValid()
{
  Q_D(PlotUnitGraph129);
  //最优配对
  //Level 1 devInx == axisCount ==
  //Level 2 axisCount ==
  //Level 3 都不匹配

  QMap<int , QICurveList > m_devCurveMapLevel_1;//存储所有LEVEL 1 配对的曲线 设备->曲线列表
  QMap<int , QICurveList > m_devCurveMapLevel_2;//存储所有LEVEL 2 配对的曲线 设备->曲线列表
  QICurveList clist;

  QICurveList clistOrigin;
  clistOrigin=d->m_curveManager->curveList();

  QList<SevDevice *> sevListLevel_2 ,sevListLevel_3;
  sevListLevel_2 = d->m_sevList;

  sevListLevel_3 = d->m_sevList;

  for(int i = 0;i<d->m_sevList.size();i++)
  {
    SevDevice *dev = d->m_sevList.at(i);
    clist.clear();
    ICurve *c = NULL;
    for(int j = 0;j<clistOrigin.size();j++)
    {
      c = clistOrigin.at(j);
      if((c->axisCount() == dev->axisNum()) && (c->devInx() ==dev->devId()))
      {
        clist.append(c);
      }
    }
    if(!clist.isEmpty())
    {
      m_devCurveMapLevel_1.insert(dev->devId(),clist);
      sevListLevel_2.removeOne(dev);
      sevListLevel_3.removeOne(dev);
    }
  }

  // 1 移除已经level 1 匹配的曲线
  QMapIterator<int , QICurveList > mIt(m_devCurveMapLevel_1);
  while (mIt.hasNext())
  {
    mIt.next();
    for(int i =0 ;i<mIt.value().size();i++)
    {
      ICurve *c=mIt.value().at(i);
      clistOrigin.removeOne(c);
    }
  }

#if TEST_DEBUG
  QMapIterator<int , QICurveList > sIt(m_devCurveMapLevel_1);
  while (sIt.hasNext())
  {
    sIt.next();
    qDebug()<<QString("compare level 1 :devId = %1").arg(sIt.key());
    for(int i =0 ;i<sIt.value().size();i++)
    {
      qDebug()<<QString("curve name = %1").arg(sIt.value().at(i)->fullName());
    }
    qDebug()<<"--------------------------------------";
  }
#endif

  // 2 移除已经level 2 匹配的曲线
  for(int i=0;i<sevListLevel_2.size();i++)
  {
    SevDevice *dev = sevListLevel_2.at(i);
    clist.clear();
    ICurve *c = NULL;
    for(int j = 0;j<clistOrigin.size();j++)
    {
      c = clistOrigin.at(j);
      if(c->axisCount() == dev->axisNum())
      {
        c->setDevInx(dev->devId());
        clist.append(c);
      }
    }
    if(!clist.isEmpty())
    {
      m_devCurveMapLevel_2.insert(dev->devId(),clist);
      sevListLevel_3.removeOne(dev);
    }
  }

#if TEST_DEBUG
  QMapIterator<int , QICurveList > sIt2(m_devCurveMapLevel_2);
  while (sIt2.hasNext())
  {
    sIt2.next();
    qDebug()<<QString("compare level 2 :devId = %1").arg(sIt2.key());
    for(int i =0 ;i<sIt2.value().size();i++)
    {
      qDebug()<<QString("curve name = %1").arg(sIt2.value().at(i)->fullName());
    }
    qDebug()<<"--------------------------------------";
  }
#endif

  QMapIterator<int , QICurveList > mIt_2(m_devCurveMapLevel_2);
  while (mIt_2.hasNext())
  {
    mIt_2.next();
    for(int i =0 ;i<mIt_2.value().size();i++)
    {
      clistOrigin.removeOne(mIt_2.value().at(i));
    }
  }


#if TEST_DEBUG
  qDebug()<<"sevListLevel_2 size = "<<sevListLevel_2.size();
  qDebug()<<"sevListLevel_3 size = "<<sevListLevel_3.size();
  qDebug()<< "clistOrigin size = "<<clistOrigin.size();
  for(int i=0;i<clistOrigin.size();i++)
  {
    qDebug()<<QString("level_3 remain curve : %1").arg(clistOrigin.at(i)->fullName());
  }

  for(int i=0;i<sevListLevel_2.size();i++)
  {
    qDebug()<<"sev level 2 ,dev = "<<sevListLevel_2.at(i)->devId();
  }
  for(int i=0;i<sevListLevel_3.size();i++)
  {
    qDebug()<<"sev level 3 ,dev = "<<sevListLevel_3.at(i)->devId();
  }
#endif

  // 3 找不到任何匹配的设备，给第一个sevListLevel_3[0] 赋全部剩下的曲线
  if(!sevListLevel_3.isEmpty())
  {
    SevDevice *dev = sevListLevel_3.at(0);
    for(int i = 0;i<clistOrigin.size();i++)
    {
      ICurve *c = clistOrigin.at(i);
      c->setAxisCount(dev->axisNum());
      c->setDevInx(dev->devId());
      if(c->axisInx() >dev->axisNum()-1)
        c->setAxisInx(0);
      qDebug()<<"change curve "<<c->fullName()<< "to dev = "<<dev->aliasName();
    }

    clistOrigin.clear();
  }


  // 4 clistOrigin是需要移除的曲线
  for(int i = 0;i < clistOrigin.size(); i++)
  {
    ICurve *rc = clistOrigin.at(i);
    qDebug()<<"4 remove curve = "<<rc->fullName();

    for(int row = 0; row<ui->tableWidget_plot_curve->rowCount(); row ++)
    {

      QTableWidgetItem * item = ui->tableWidget_plot_curve->item(row,COL_TABLE_CURVE_NAME);
      ICurve *c = item->data(ROLE_TABLE_CURVE_ICURVE_PTR).value<ICurve *>();
      if(c == rc)
      {
        ui->tableWidget_plot_curve->removeRow(row);
        ui->plot->removeGraph(row);
        qDebug()<<"remove row = "<<row;
        break;
      }
    }
    d->m_curveManager->removeCurve(rc);
  }

  //5 对应的变量在这个设备中存不存在，不存在的要删除
  //5 curvelist 更改所有相应的地址
  QICurveList needRemoveList;

  for(int i = 0;i < d->m_curveManager->curveList().size(); i ++)
  {
    ICurve *c = d->m_curveManager->curveList().at(i);
    QTreeWidget *ramTree=d->m_sevList.at(c->devInx())->axisTreeSource(c->axisInx(),"RAM");
    qDebug()<<"check curve :"<<c->fullName()<<" dev alias name:= "<<d->m_sevList.at(c->devInx())->aliasName();
    //常变量
    QString ckey;
    bool findInConst = true;
    for(int cinx = 0;cinx < c->constInputs().size(); cinx ++)
    {
      ckey = c->constInputs().at(cinx).keyName;
//      qDebug()<<"ckey "<<ckey;
      QTreeWidgetItem *item=GTUtils::findItem(ckey,ramTree,GT::COL_FLASH_RAM_TREE_NAME);
      if(item == NULL) //not find the key
      {
        needRemoveList.append(c);
        findInConst = false;
        break;
      }
      else//find
      {
//        qDebug()<<"find = "<<item->text(GT::COL_FLASH_RAM_TREE_ADDR).toUShort();
        c->constInputs()[cinx].prm.offtAddr = item->text(GT::COL_FLASH_RAM_TREE_ADDR).toUShort();
      }
    }
    //接着找变量中的参数
    if(findInConst)
    {
      QString vkey;

      for(int vinx = 0;vinx < c->varInputs().size();  vinx ++)
      {
        vkey = c->varInputs().at(vinx).keyName;
//        qDebug()<<"vkey "<<vkey;
        QTreeWidgetItem *item=GTUtils::findItem(vkey,ramTree,GT::COL_FLASH_RAM_TREE_NAME);
        if(item == NULL) //not find the key
        {
          needRemoveList.append(c);
          break;
        }
        else//find
        {
//          qDebug()<<"find = "<<item->text(GT::COL_FLASH_RAM_TREE_ADDR).toUShort();
          c->varInputs()[vinx].prm.offtAddr = item->text(GT::COL_FLASH_RAM_TREE_ADDR).toUShort();
//          qDebug()<<"c->varInputs()[vinx].prm.offtAddr "<<c->varInputs()[vinx].prm.offtAddr;
        }
      }
    }
  }

  // 6 移除找不到的曲线
  for(int i = 0;i < needRemoveList.size(); i++)
  {
    ICurve *rc = needRemoveList.at(i);
    qDebug()<<"need remove :"<<rc->fullName();

    for(int row = 0; row<ui->tableWidget_plot_curve->rowCount(); row ++)
    {
      QTableWidgetItem * item = ui->tableWidget_plot_curve->item(row,COL_TABLE_CURVE_NAME);
      ICurve *c = item->data(ROLE_TABLE_CURVE_ICURVE_PTR).value<ICurve *>();
      if(c == rc)
      {
        ui->tableWidget_plot_curve->removeRow(row);
        ui->plot->removeGraph(row);
        break;
      }
    }
    d->m_curveManager->removeCurve(rc);
  }

  // 7 tablewidget_plot_curve 设备标号更新显示
  for(int row = 0; row < ui->tableWidget_plot_curve->rowCount(); row ++)
  {
    QTableWidgetItem * item = ui->tableWidget_plot_curve->item(row,COL_TABLE_CURVE_NAME);
    ICurve *c = item->data(ROLE_TABLE_CURVE_ICURVE_PTR).value<ICurve *>();
    ui->tableWidget_plot_curve->item(row,COL_TABLE_CURVE_DEV)->setText(c->devName());
    ui->tableWidget_plot_curve->item(row,COL_TABLE_CURVE_AXIS)->setText(QString::number(c->axisInx()));
  }
}

void PlotUnitGraph129::showAllData()
{
  //画全曲线
  for(int row = 0; row < ui->tableWidget_plot_curve->rowCount(); row ++)
  {
    QTableWidgetItem * item = ui->tableWidget_plot_curve->item(row,COL_TABLE_CURVE_NAME);
    ICurve *c = item->data(ROLE_TABLE_CURVE_ICURVE_PTR).value<ICurve *>();
    QCPGraph *graph = item->data(ROLE_TABLE_CURVE_GRAPH_PTR).value<QCPGraph *>();
    c->savePrepare();
    graph->data().clear();
    graph->addData(c->sData()->keys,c->sData()->values);
  }
  ui->plot->replot();
}


