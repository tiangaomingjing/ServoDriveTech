#include "sdtmainwindow.h"
#include "ui_sdtmainwindow.h"

#include "optautoload.h"
#include "iopt.h"
#include "optcontainer.h"
#include "optface.h"
#include "optplot.h"
#include "optuser.h"
#include "dialogoption.h"

#include "gtutils.h"
#include "appiconname.h"

#include "deviceconfig.h"
#include "idevreadwriter.h"
#include "devtextrwriter.h"
#include "sdassembly.h"
#include "sdtglobaldef.h"
#include "sevdevice.h"

#include "sdtstatusbar.h"

#include "globaluicontroler.h"
#include "iuiwidget.h"

#include "sdtglobaldef.h"

#include <QToolButton>
#include <QDebug>
#include <QTranslator>
#include <QtQml>
#include <QProgressBar>

using namespace GT;

SDTMainWindow::SDTMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::SDTMainWindow),
  m_currentUiStatus(UI_STA_FUNCNF)
{
  ui->setupUi(this);
  qmlRegisterType<SevDevice>("QtCppClass", 1, 0, "SevDevice");
  clearStackedWidget();
  staticUiInit();
  ui->dockWidgetPlot->hide();
}

SDTMainWindow::~SDTMainWindow()
{
  delete ui;
}
bool SDTMainWindow::init()
{
  deviceInit();
  navigationTreeInit();
  globalUiPageInit();
  stackedWidgetInit();
  return true;
}
QTreeWidget *SDTMainWindow::navTreeWidget() const
{
  return ui->treeWidget;
}

void SDTMainWindow::staticUiInit()
{
  createActions();
  setAppIcon();

  m_optc=OptContainer::instance();

  m_statusBar=new SdtStatusBar(ui->treeWidget,this);
  mp_progressBar=m_statusBar->statusProgressBar();
  ui->statusBar->addPermanentWidget(m_statusBar,0);
  ui->statusBar->setToolTipDuration(2000);
  createConnections();
}
void SDTMainWindow::createActions()
{
  ui->mainToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
  ui->mainToolBar->setIconSize(QSize(24,24));
  m_actnConnect=new QAction(this);
  m_actnConnect->setText(tr("connet"));
  m_actnConnect->setStatusTip(tr("connect to servo"));
  m_actnConnect->setToolTip(tr("connect to servo"));

  m_actnDisNet=new QAction(this);
  m_actnDisNet->setText(tr("disnet"));

  m_actnConnect->setCheckable(true);
  m_actnDisNet->setCheckable(true);
  m_actnDisNet->setChecked(true);
  QActionGroup *netGroup=new QActionGroup(this);
  netGroup->addAction(m_actnConnect);
  netGroup->addAction(m_actnDisNet);

  m_actnNewConfig=new QAction(this);
  m_actnNewConfig->setText(tr("new"));

  m_actnDownload=new QAction(this);
  m_actnDownload->setText(tr("dwnload"));

  m_actnUpload=new QAction(this);
  m_actnUpload->setText(tr("upload"));

  m_actnCompare=new QAction(this);
  m_actnCompare->setText(tr("compare"));

  m_actnConfig=new QAction(this);
  m_actnConfig->setText(tr("config"));

  m_actnSave=new QAction(this);
  m_actnSave->setText(tr("save"));

  QWidget *spacer=new QWidget(this);
  spacer->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

  m_tbtnHelp=new QToolButton(this);
  m_tbtnHelp->setPopupMode(QToolButton::MenuButtonPopup);
  m_tbtnHelp->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
  m_tbtnHelp->setText(tr("help"));
  m_actnAboutHardware=new QAction(this);
  m_actnAboutHardware->setText(tr("hinfo"));
  m_actnAboutSoftware=new QAction(this);
  m_actnAboutSoftware->setText(tr("sinfo"));
  m_tbtnHelp->addAction(m_actnAboutHardware);
  m_tbtnHelp->addAction(m_actnAboutSoftware);


  //----------------more toolbutton----------------------------
  m_tbtnMore=new QToolButton(this);
//  m_tbtnMore->setToolButtonStyle(Qt::ToolButtonIconOnly);
  m_tbtnMore->setPopupMode(QToolButton::MenuButtonPopup);
//  m_tbtnMore->setPopupMode(QToolButton::InstantPopup);

  m_actnOnMode=new QAction(m_tbtnMore);
  m_actnOnMode->setText(tr("online"));
  m_actnOnMode->setCheckable(true);

  m_actnOffMode=new QAction(m_tbtnMore);
  m_actnOffMode->setText(tr("offline"));
  m_actnOffMode->setCheckable(true);

  QActionGroup *modeGroup=new QActionGroup(m_tbtnMore);
  m_actnOnMode->setChecked(true);
  modeGroup->addAction(m_actnOffMode);
  modeGroup->addAction(m_actnOnMode);

  m_actnUpdateFlash=new QAction(tr("update"),m_tbtnMore);
  m_actnReset=new QAction(tr("rstdsp"),m_tbtnMore);

  m_actnOption=new QAction(tr("option"),m_tbtnMore);
  m_actnProduce=new QAction(tr("produce"),m_tbtnMore);

//  m_tbtnMore->addAction(m_actnOnMode);
//  m_tbtnMore->addAction(m_actnOffMode);
//  m_tbtnMore->addAction(actspacer1);
//  m_tbtnMore->addAction(act1);
//  m_tbtnMore->addAction(act2);
//  m_tbtnMore->addAction(act3);
//  m_tbtnMore->addAction(act4);
//  m_tbtnMore->addAction(act5);
  QMenu *menu=new QMenu(m_tbtnMore);//menu action 不能共存
  QMenu *menuUpdateFlash=new QMenu(tr("UpdateFirmware"),menu);
  QMenu *menuSoftMode=new QMenu(tr("softmode"),menu);

  menu->addMenu(menuUpdateFlash);
  menuUpdateFlash->addAction(m_actnUpdateFlash);
  menuUpdateFlash->addAction(m_actnReset);
  menu->addAction(m_actnOption);
  menu->addAction(m_actnProduce);
  menu->addMenu(menuSoftMode);
  menuSoftMode->addAction(m_actnOnMode);
  menuSoftMode->addAction(m_actnOffMode);
  m_tbtnMore->setMenu(menu);

  //按顺序增加
  ui->mainToolBar->addAction(m_actnConnect);
  ui->mainToolBar->addAction(m_actnDisNet);
  ui->mainToolBar->addAction(m_actnNewConfig);
  ui->mainToolBar->addAction(m_actnDownload);
  ui->mainToolBar->addAction(m_actnUpload);
  ui->mainToolBar->addAction(m_actnCompare);
  ui->mainToolBar->addAction(m_actnConfig);
  ui->mainToolBar->addAction(m_actnSave);
  ui->mainToolBar->addWidget(m_tbtnHelp);
  ui->mainToolBar->addWidget(spacer);
  ui->mainToolBar->addWidget(m_tbtnMore);

}

void SDTMainWindow::setAppIcon()
{
  OptFace *face=dynamic_cast<OptFace *>(OptContainer::instance()->optItem("optface"));
  QString iconPath=GTUtils::customPath()+"/option/style/"+face->css()+"/icon/";
  m_actnConnect->setIcon(QIcon(iconPath+ICON_CONNECT));
  m_actnDisNet->setIcon(QIcon(iconPath+ICON_DISNET));
  m_actnNewConfig->setIcon(QIcon(iconPath+ICON_NEWCONFIG));
  m_actnDownload->setIcon(QIcon(iconPath+ICON_DOWNLOAD));
  m_actnUpload->setIcon(QIcon(iconPath+ICON_UPLOAD));
  m_actnCompare->setIcon(QIcon(iconPath+ICON_COMPARE));
  m_actnConfig->setIcon(QIcon(iconPath+ICON_CONFIG));
  m_actnSave->setIcon(QIcon(iconPath+ICON_SAVE));

  m_tbtnHelp->setIcon(QIcon(iconPath+ICON_HELP));
  m_tbtnMore->setIcon(QIcon(iconPath+ICON_MORE));
}

void SDTMainWindow::createConnections()
{
  //创建连接slots
  connect(m_actnOption,SIGNAL(triggered(bool)),this,SLOT(onActnOptionClicked()));

  OptAutoLoad *optAuto=dynamic_cast<OptAutoLoad *>(OptContainer::instance()->optItem("optautoload"));
  if(optAuto!=NULL)
  {
    connect(optAuto,SIGNAL(autoLoadChanged(bool)),this,SLOT(onOptAutoLoadChanged(bool)));
    m_actnNewConfig->setVisible(!optAuto->autoLoad());
  }
  OptFace *optface=dynamic_cast<OptFace *>(OptContainer::instance()->optItem("optface"));
  if(optface!=NULL)
    connect(optface,SIGNAL(faceCssChanged(QString)),this,SLOT(onOptFaceCssChanged(QString)));

  connect(ui->treeWidget,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(onNavTreeWidgetItemClicked(QTreeWidgetItem*,int)));

  connect(m_statusBar,SIGNAL(statusPageChanged(int)),this,SLOT(onStatusBarPageChanged(int)));
}
void SDTMainWindow::clearStackedWidget()
{
  int i=0;
  while (ui->stackedWidget->count()) {
    delete ui->stackedWidget->widget(0);
    qDebug()<<"delete stackedWidget "<<i;
    i++;
  }
}

void SDTMainWindow::closeEvent(QCloseEvent *e)
{
  OptContainer *optc=OptContainer::instance();
  optc->saveOpt();
  QMainWindow::closeEvent(e);
}
void SDTMainWindow::processCallBack(void *argv,short *value)
{
  QProgressBar *pBar=static_cast<QProgressBar *>(argv);
  pBar->setValue(*value);
  qDebug()<<"progress value ="<<*value;
}

bool SDTMainWindow::deviceInit()
{
  QList<DeviceConfig*> devConfigList;

  IDevReadWriter *idevRWriter=new DevTextRWriter(NULL);
  bool isOk;
  devConfigList=idevRWriter->createConfig(processCallBack,(void *)mp_progressBar,isOk);
  Q_ASSERT(isOk);

  for(int i=0;i<devConfigList.count();i++)
  {
    qDebug()<<"************************new SdAssembly "<<i;
    SdAssembly *sdriver=new SdAssembly();
    connect(sdriver,SIGNAL(initProgressInfo(int,QString)),this,SLOT(onProgressInfo(int,QString)));
    sdriver->init(devConfigList.at(i),m_optc);
    m_sdAssemblyList.append(sdriver);
  }

  delete idevRWriter;
  GT::deepClearList(devConfigList);
  return true;
}

void SDTMainWindow::navigationTreeInit()
{
  qDebug()<<"build nav show mix";
  QTreeWidgetItem *deviceItem;
  QTreeWidgetItem *plotItem;
  QTreeWidgetItem *axisItem;
  QTreeWidgetItem *globalItem=NULL;
  SdAssembly * sd;
  int pageIndex=0;
  for(int  i=0;i<m_sdAssemblyList.count();i++)
  {
    int axisNum;
    sd=m_sdAssemblyList.at(i);
    axisNum=sd->sevDevice()->axisNum();
    deviceItem=new QTreeWidgetItem(ui->treeWidget);
    deviceItem->setText(COL_TARGET_CONFIG_NAME,sd->sevDevice()->modelName());
    deviceItem->setText(COL_TARGET_CONFIG_PRM,QString::number(axisNum));
    qDebug()<<"deviceItem->setText";


    for(int i=0;i<axisNum;i++)
    {
      axisItem=sd->sevDevice()->targetTree()->child(ROW_TARGET_CONFIG_AXIS)->clone();
      axisItem->setText(COL_TARGET_CONFIG_NAME,tr("Axis_%1").arg(i+1));
      for(int j=0;j<axisItem->childCount();j++)
      {
        axisItem->child(j)->setText(COL_TARGET_CONFIG_PRM,QString::number(i));
        axisItem->child(j)->setText(COL_TARGET_CONFIG_INDEX,QString::number(pageIndex));
        axisItem->child(j)->setText(COL_TARGET_CONFIG_ISPLOT,"-1");
        pageIndex++;
      }
      deviceItem->addChild(axisItem);
    }

    globalItem=sd->sevDevice()->targetTree()->child(ROW_TARGET_CONFIG_GLOBAL);
    int globalCount=globalItem->childCount();
    QTreeWidgetItem *item=NULL;
    for(int i=0;i<globalCount;i++)
    {
      item=globalItem->child(i)->clone();
      item->setText(COL_TARGET_CONFIG_INDEX,QString::number(pageIndex));
      item->setText(COL_TARGET_CONFIG_ISPLOT,"-1");
      deviceItem->addChild(item);
      pageIndex++;
    }

//    ui->treeWidget->addTopLevelItem(deviceItem);
  }
  plotItem=new QTreeWidgetItem(ui->treeWidget);
  plotItem->setText(COL_TARGET_CONFIG_NAME,tr("Plot"));
  plotItem->setText(COL_TARGET_CONFIG_PRM,tr("-1"));//代表不是设备
  plotItem->setText(COL_TARGET_CONFIG_INDEX,QString::number(pageIndex));
  plotItem->setText(COL_TARGET_CONFIG_ISPLOT,"1");
//  ui->treeWidget->addTopLevelItem(plotItem);

  QStringList headList;
  headList<<"name"<<"prm"<<"classname"<<"filename"<<"ui index"<<"file src select"<<"is plot ui";
  ui->treeWidget->setHeaderLabels(headList);
  ui->treeWidget->setColumnCount(headList.count());
  ui->treeWidget->expandItem(ui->treeWidget->topLevelItem(0));
  ui->treeWidget->expandItem(ui->treeWidget->topLevelItem(0)->child(0));
  ui->treeWidget->topLevelItem(0)->child(0)->child(0)->setSelected(true);
//  ui->treeWidget->setHeaderHidden(false);
  ui->treeWidget->setHeaderHidden(true);
  ui->treeWidget->setColumnHidden(1,true);
  ui->treeWidget->setColumnHidden(2,true);
  ui->treeWidget->setColumnHidden(3,true);
  ui->treeWidget->setColumnHidden(4,true);
  ui->treeWidget->setColumnHidden(5,true);
  ui->treeWidget->setColumnHidden(6,true);

  m_statusBar->updateDeviceWhenChanged(ui->treeWidget);
}

void SDTMainWindow::globalUiPageInit()
{
  m_gUiControl=new GlobalUiControler(m_optc);
  m_gUiControl->createUis();
}
void SDTMainWindow::stackedWidgetInit()
{
  IUiControler *uiCtr;
  QWidget *w;
  SdAssembly * sd;
  int uiCount;
  for(int i=0;i<m_sdAssemblyList.count();i++)
  {
    sd=m_sdAssemblyList.at(i);
    uiCtr=sd->uiControler();
    uiCount=uiCtr->uiCount();
    qDebug()<<"sd"<<i<<"uiCount"<<uiCount;
    for(int i=0;i<uiCount;i++)
    {
      w=static_cast<QWidget *>(uiCtr->uiAt(i));
      ui->stackedWidget->addWidget(w);
    }
    qApp->processEvents();
  }

  uiCtr=m_gUiControl;
  uiCount=uiCtr->uiCount();
  qDebug()<<"ui global Count"<<uiCount;
  for(int i=0;i<uiCount;i++)
  {
    w=static_cast<QWidget *>(uiCtr->uiAt(i));
    ui->stackedWidget->addWidget(w);
  }
}

void SDTMainWindow::disactiveAllUi()
{
  IUiWidget *uiWidget;
  for(int i=0;i<ui->stackedWidget->count();i++)
  {
    uiWidget=dynamic_cast<IUiWidget *>(ui->stackedWidget->widget(i));
    uiWidget->setUiActive(false);
  }
}

void SDTMainWindow::activeCurrentUi()
{
  IUiWidget *uiWidget=dynamic_cast<IUiWidget *>(ui->stackedWidget->currentWidget());
  uiWidget->setUiActive(true);
}

void SDTMainWindow::changeConfigSaveBtnStatus()
{
  IUiWidget *uiWidget=dynamic_cast<IUiWidget *>(ui->stackedWidget->currentWidget());
  m_actnConfig->setEnabled(uiWidget->hasConfigFunc());
  m_actnSave->setEnabled(uiWidget->hasSaveFunc());
}

void SDTMainWindow::removeDockWidgetAll()
{
  removeDockWidget(ui->dockWidgetNav);
  removeDockWidget(ui->dockWidgetPlot);
}
void SDTMainWindow::setUiShowStatus(UiShowStatus status)
{
  removeDockWidgetAll();
  addDockWidget(Qt::LeftDockWidgetArea,ui->dockWidgetNav);

  switch (status)
  {
  case UI_STA_FUNCF:
    centralWidget()->show();
    ui->dockWidgetNav->show();
    ui->dockWidgetPlot->show();
    break;
  case UI_STA_FUNCNF:
    ui->dockWidgetNav->show();
    centralWidget()->show();
    ui->dockWidgetPlot->hide();
    break;
  case UI_STA_PLOTF:
    centralWidget()->show();
    ui->dockWidgetNav->show();
    ui->dockWidgetPlot->show();
    break;
  case UI_STA_PLOTNF:
    centralWidget()->hide();
    splitDockWidget(ui->dockWidgetNav,ui->dockWidgetPlot,Qt::Horizontal);
    ui->dockWidgetPlot->show();
    ui->dockWidgetNav->show();
    break;
  default:
    centralWidget()->show();
    ui->dockWidgetNav->show();
    ui->dockWidgetPlot->hide();
    break;
  }
  ui->dockWidgetNav->setBaseSize(QSize(300,500));
}

void SDTMainWindow::showPlotUiOnly(bool show)
{
  if(show)
  {
    centralWidget()->hide();
    ui->dockWidgetPlot->show();
  }
  else
  {
    centralWidget()->show();
    ui->dockWidgetPlot->hide();
  }

//  bool isFloat=ui->dockWidgetPlot->isFloating();
//  if(isFloat)
//  {
//    if(show)
//      m_currentUiStatus=UI_STA_PLOTF;
//    else
//      m_currentUiStatus=UI_STA_FUNCF;
//  }
//  else
//  {
//    if(show)
//      m_currentUiStatus=UI_STA_PLOTNF;
//    else
//      m_currentUiStatus=UI_STA_FUNCNF;
//  }
//  setUiShowStatus(m_currentUiStatus);
}

void SDTMainWindow::onActnOptionClicked()
{
  DialogOption dialogOpt;
  OptContainer *optc=OptContainer::instance();
  foreach (IOpt *opt, optc->optItems())
  {
    opt->uiInit();
  }
  dialogOpt.exec();
}
void SDTMainWindow::onOptAutoLoadChanged(bool changed)
{
  m_actnNewConfig->setVisible(!changed);
  qDebug()<<"m_actnNewConfig->setVisible"<<!changed;
}
void SDTMainWindow::onOptFaceCssChanged(QString css)
{
  setAppIcon();
  qDebug()<<"setAppIcon"<<css;
}
void SDTMainWindow::onProgressInfo(int barValue,QString msg)
{
  qDebug()<<"value"<<barValue<<"msg"<<msg;
  emit initProgressInfo(barValue,msg);
}
void SDTMainWindow::onNavTreeWidgetItemClicked(QTreeWidgetItem *item, int column)
{
  Q_UNUSED(column);
  if(item->childCount()==0)
  {
    int index=item->text(COL_TARGET_CONFIG_INDEX).toInt();
    if(index<ui->stackedWidget->count())
    {
      ui->stackedWidget->setCurrentIndex(index);
      qDebug()<<"index"<<index <<"ui->stackedWidget->count()"<<ui->stackedWidget->count();
      GTUtils::delayms(10);

      disactiveAllUi();
      activeCurrentUi();
      changeConfigSaveBtnStatus();
      bool plotShow=false;
      if(item->text(COL_TARGET_CONFIG_ISPLOT)=="1")
        plotShow=true;
      showPlotUiOnly(plotShow);
    }
  }
}

void SDTMainWindow::onStatusBarPageChanged(int pIndex)
{
  IUiWidget *uiWidget=NULL;
  ui->stackedWidget->setCurrentIndex(pIndex);
  QWidget *w=ui->stackedWidget->widget(pIndex);
  uiWidget=dynamic_cast<IUiWidget *>(w);
  UiIndexs index=uiWidget->uiIndexs();
  qDebug()<<"UiIndexs"<<tr("dev:%1,axis:%2,page:%3").arg(index.devInx).arg(index.aixsInx).arg(index.pageInx);
  ui->treeWidget->clearSelection();
  ui->treeWidget->collapseAll();
  QTreeWidgetItem *selectDevItem=ui->treeWidget->topLevelItem(index.devInx);
  QTreeWidgetItem *selectAxisItem=selectDevItem->child(index.aixsInx);
  QTreeWidgetItem *selectItem=selectAxisItem->child(index.pageInx);
  ui->treeWidget->expandItem(selectDevItem);
  ui->treeWidget->expandItem(selectAxisItem);
  ui->treeWidget->expandItem(selectItem);
  selectItem->setSelected(true);
}
