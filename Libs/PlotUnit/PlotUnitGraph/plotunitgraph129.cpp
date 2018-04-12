#include "plotunitgraph129.h"
#include "ui_plotunitgraph129.h"
#include "iplotunitgraph_p.h"
#include "Option"
#include "gtutils.h"
#include "sdtglobaldef.h"
#include "sevdevice.h"

#include <QDebug>
#include <QTimer>

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
#define ICON_NAME_OPEN       "plot_open.png"
#define ICON_NAME_SAVE       "plot_save.png"

class ModeCtlPrms
{
public:
typedef enum{
    MODE_IDLE,
    MODE_ADC,
    MODE_IPA,
    MODE_MPI,
    MODE_COL,
    MODE_CCL,
    MODE_VCL,
    MODE_VPL,
    MODE_VSL,
    MODE_FIX,
    MODE_PT,
    MODE_DB,
    MODE_CSC
  }ModeCtlType;

  bool m_isChecked;
  ModeCtlType m_curMode;
  //mode ipa
  qreal m_ipa;
  //mode col
  qreal m_uaref;
  qreal m_ubref;
  qreal m_ucref;
  qreal m_udref;
  qreal m_uqref;
  //mode ccl
  qreal m_idref;
  qreal m_iqref;
  //mode vcl
  qreal m_vcl;
  //mode vpl
  qreal m_vpl;
  //mode vsl
  qreal m_vsl;
  //mode pt
  qreal m_pt;
};
class MotionCtlPrms
{
public:
  typedef enum{
    MOTION_SRC_PC,
    MOTION_SRC_GLINK2
  }MotionSource;
  typedef enum{
    MOTION_TYPE_NONE,
    MOTION_TYPE_VEL
  }MotionType;

  bool m_isChecked;
  MotionSource m_src;
  MotionType m_type;

  //motion type vel
  bool m_isCircle;
  qreal m_stepAmp;
  quint16 m_stepTimes;
  qreal m_circleAmp;
  quint16 m_circleT;
  quint16 m_circleCount;

};

class PlotTabCtlPrms
{
public:
  explicit PlotTabCtlPrms(quint16 id,quint16 axisCount):m_id(id),m_axisCount(axisCount)
  {
    for(int i=0;i<axisCount;i++)
    {
      ModeCtlPrms *mode=new ModeCtlPrms;
      m_modeCtlPrmsList.append(mode);
      MotionCtlPrms *motion=new MotionCtlPrms;
      m_motionCtlPrmsList.append(motion);
    }
  }
  ~PlotTabCtlPrms()
  {
    GT::deepClearList(m_modeCtlPrmsList);
    GT::deepClearList(m_motionCtlPrmsList);
  }

  quint16 m_id;
  quint16 m_axisCount;
  quint16 m_lastModeAxis;
  quint16 m_lastMotionAxis;

  QList<ModeCtlPrms*>m_modeCtlPrmsList;
  QList<MotionCtlPrms*>m_motionCtlPrmsList;
};

class PlotUnitGraph129Private:public IPlotUnitGraphPrivate
{
  Q_DECLARE_PUBLIC(PlotUnitGraph129)
public:
  PlotUnitGraph129Private(){}
  ~PlotUnitGraph129Private(){}
protected:
  friend class PlotUnitGraph129;
  QList<PlotTabCtlPrms*>m_ctlPrms;//每个设备对应一个
  QTimer *m_timer;

};

PlotUnitGraph129::PlotUnitGraph129(const QList<SevDevice *> &sevList, QWidget *parent) :
  IPlotUnitGraph(*(new PlotUnitGraph129Private),parent),
  ui(new Ui::PlotUnitGraph129)
{
  Q_D(PlotUnitGraph129);
  d->m_sevList=sevList;

  ui->setupUi(this);
//  connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(onPushButtonTestClicked(bool)));
  ui->splitter_plot_tab->setStretchFactor(0,2);
  ui->splitter_plot_tab->setStretchFactor(1,1);
  ui->splitter_plot_curve->setStretchFactor(0,1);
  ui->splitter_plot_curve->setStretchFactor(1,0);

  ui->tbtn_plot_floatin->setCheckable(true);
  ui->tbtn_plot_floatin->setChecked(true);
  ui->tbtn_plot_startSampling->setCheckable(true);
  ui->tbtn_plot_startSampling->setChecked(false);
  ui->tbtn_plot_mea_horizontal->setCheckable(true);
  ui->tbtn_plot_mea_vertical->setCheckable(true);

  d->m_timer=new QTimer(this);
  d->m_timer->setInterval(1000);

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

void PlotUnitGraph129::onSevDeviceListChanged(const QList<SevDevice *> &sevlist)
{
  Q_D(PlotUnitGraph129);
  d->m_sevList=sevlist;
  d->m_timer->stop();
  ctlPanelInit();
}

void PlotUnitGraph129::createConnections()
{
  Q_D(PlotUnitGraph129);
  connect(ui->tbtn_plot_floatin,SIGNAL(clicked(bool)),this,SLOT(onBtnFloatInClicked(bool)));
  OptFace *face=dynamic_cast<OptFace *>(OptContainer::instance()->optItem("optface"));
  connect(face,SIGNAL(faceCssChanged(QString)),this,SLOT(onOptFaceCssChanged(QString)));
  connect(ui->tbtn_plot_mea_horizontal,SIGNAL(clicked(bool)),this,SLOT(onBtnMeaHClicked(bool)));
  connect(ui->tbtn_plot_mea_vertical,SIGNAL(clicked(bool)),this,SLOT(onBtnMeaVClicked(bool)));
  connect(ui->tbtn_plot_fit,SIGNAL(clicked(bool)),this,SLOT(onBtnFitClicked()));
  connect(ui->tbtn_plot_config,SIGNAL(clicked(bool)),this,SLOT(onBtnConfigClicked()));

  connect(ui->plot,SIGNAL(currentPosChanged(QPointF)),this,SLOT(onPlotPosHoverChanged(QPointF)));
  connect(ui->plot,SIGNAL(horizMeaDataChanged(qreal,qreal,qreal)),this,SLOT(onPlotMeaHposChanged(qreal,qreal,qreal)));
  connect(ui->plot,SIGNAL(vertiMeaDataChanged(qreal,qreal,qreal)),this,SLOT(onPlotMeaVposChanged(qreal,qreal,qreal)));

  connect(d->m_timer,SIGNAL(timeout()),this,SLOT(onTimeOut()));

  connect(ui->modeCtlPanel,SIGNAL(checkChanged(quint16,int)),this,SLOT(onModeCtlPanelCheckChanged(quint16,int)));
  connect(ui->modeCtlPanel,SIGNAL(modeChanged(quint16,int)),this,SLOT(onModeCtlPanelModeChanged(quint16,int)));
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
  setPlotIcons(css);
}

void PlotUnitGraph129::onBtnMeaHClicked(bool checked)
{
  if(checked)
    ui->plot->createHorizMea();
  else
    ui->plot->clearHorizMea();
}

void PlotUnitGraph129::onBtnMeaVClicked(bool checked)
{
  if(checked)
    ui->plot->createVertiMea();
  else
    ui->plot->clearVertiMea();
}

void PlotUnitGraph129::onBtnFitClicked()
{
  ui->plot->rescaleAxes();
  ui->plot->replot();
}

void PlotUnitGraph129::onBtnConfigClicked()
{
  bool checked=ui->tbtn_plot_startSampling->isChecked();
  ui->tbtn_plot_startSampling->setChecked(!checked);
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
  Q_D(PlotUnitGraph129);
  static quint32 i=0;
  qDebug()<<"time out"<<i;
  i++;

  //实时读取设备当前的模式
//  SevDevice *sd=d->m_sevList.at(d->m_curSevInx);
//  PlotTabCtlPrms *prms=d->m_ctlPrms.at(d->m_curSevInx);
//  if(sd->isConnecting())
//  {
//    for(int i=0;i<sd->axisNum();i++)
//    {
//      //read axis mode from servo
//      prms->m_modeCtlPrmsList.at(i)->ModeCtlType=0;
//      ui->modeCtlPanel->setMode(i,prms->m_modeCtlPrmsList.at(i)->ModeCtlType);
//    }
//    int lastAxisMode=prms->m_modeCtlPrmsList.at(prms->m_lastModeAxis)->ModeCtlType;
//    ui->stackedWidget->setCurrentIndex(lastAxisMode);
//  }

}

void PlotUnitGraph129::onModeCtlPanelCheckChanged(quint16 axis, int mode)
{
  qDebug()<<axis<<mode;
  if(mode<ui->stackedWidget_plot_mode->count())
  {
    ui->stackedWidget_plot_mode->setCurrentIndex(mode);
  }
}

void PlotUnitGraph129::onModeCtlPanelModeChanged(quint16 axis, int mode)
{
  qDebug()<<axis<<mode;
  if(mode<ui->stackedWidget_plot_mode->count())
  {
    ui->stackedWidget_plot_mode->setCurrentIndex(mode);
  }
}

void PlotUnitGraph129::setPlotIcons(const QString &css)
{

  QString iconPath=GTUtils::customPath()+"option/style/"+css+"/icon/";
  QIcon samplStartIcon;
  samplStartIcon.addPixmap(QPixmap(iconPath+ICON_NAME_START),QIcon::Selected,QIcon::Off);
  samplStartIcon.addPixmap(QPixmap(iconPath+ICON_NAME_STOP),QIcon::Selected,QIcon::On);
  ui->tbtn_plot_startSampling->setIcon(samplStartIcon);
  ui->tbtn_plot_startSampling->setIconSize(QSize(30,30));

  ui->tbtn_plot_config->setIcon(QIcon(QPixmap(iconPath+ICON_NAME_CONFIG)));
  ui->tbtn_plot_config->setIconSize(QSize(30,30));

  ui->tbtn_plot_auto->setIcon(QIcon(QPixmap(iconPath+ICON_NAME_AUTO)));
  ui->tbtn_plot_auto->setIconSize(QSize(30,30));

  ui->tbtn_plot_fit->setIcon(QIcon(QPixmap(iconPath+ICON_NAME_FIT)));
  ui->tbtn_plot_fit->setIconSize(QSize(30,30));

  ui->tbtn_plot_tag->setIcon(QIcon(QPixmap(iconPath+ICON_NAME_TAG)));
  ui->tbtn_plot_tag->setIconSize(QSize(30,30));

  ui->tbtn_plot_mea_horizontal->setIcon(QIcon(QPixmap(iconPath+ICON_NAME_MEAH)));
  ui->tbtn_plot_mea_horizontal->setIconSize(QSize(30,30));

  ui->tbtn_plot_mea_vertical->setIcon(QIcon(QPixmap(iconPath+ICON_NAME_MEAV)));
  ui->tbtn_plot_mea_vertical->setIconSize(QSize(30,30));

  ui->tbtn_plot_open->setIcon(QIcon(QPixmap(iconPath+ICON_NAME_OPEN)));
  ui->tbtn_plot_open->setIconSize(QSize(30,30));

  ui->tbtn_plot_save->setIcon(QIcon(QPixmap(iconPath+ICON_NAME_SAVE)));
  ui->tbtn_plot_save->setIconSize(QSize(30,30));

//  qDebug()<<"PlotUnitGraph129 css changed"<<css<<iconPath;
}

void PlotUnitGraph129::gtPlotInit()
{
  setupSimpleDemo(ui->plot);
  ui->plot->xAxis2->setVisible(false);
  ui->plot->xAxis2->setTickLabels(false);
  ui->plot->yAxis2->setVisible(false);
  ui->plot->yAxis2->setTickLabels(false);
  ui->plot->setBackground(QBrush(QColor(240,240,240)));
}

void PlotUnitGraph129::ctlPanelInit()
{
  Q_D(PlotUnitGraph129);
  GT::deepClearList(d->m_ctlPrms);
  ui->listWidget_plot_device->clear();

  for(int i=0;i<d->m_sevList.size();i++)
  {
    PlotTabCtlPrms *prms=new PlotTabCtlPrms(i,d->m_sevList.at(i)->axisNum());
    d->m_ctlPrms.append(prms);
    ui->listWidget_plot_device->addItem(d->m_sevList.at(i)->aliasName());
  }
  d->m_curSevInx=0;
  ui->listWidget_plot_device->setCurrentRow(d->m_curSevInx);
  bool isShow=(d->m_sevList.count()>1);
  ui->widget_plot_device_nav->setVisible(isShow);
  ui->modeCtlPanel->setAxis(d->m_sevList.at(d->m_curSevInx)->axisNum());
  ui->modeCtlPanel->setChecked(0,true);
}

//void PlotUnitGraph129::onPushButtonTestClicked(bool checked)
//{
//  Q_D(PlotUnitGraph129);
//  d->m_winIsIn=!d->m_winIsIn;
//  emit winFloatingChange(d->m_winIsIn);
//}

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
