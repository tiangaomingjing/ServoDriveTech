#include "sdtmainwindow.h"
#include "ui_sdtmainwindow.h"

#include "Option"
#include "dialogoption.h"

#include "gtutils.h"
#include "appiconname.h"

#include "deviceconfig.h"
#include "idevreadwriter.h"
#include "devtextrwriter.h"
#include "devcomrwriter.h"
#include "sdassembly.h"
#include "sdtglobaldef.h"
#include "sevdevice.h"

#include "sdtstatusbar.h"

#include "globaluicontroler.h"
#include "iuiwidget.h"

#include "sdtglobaldef.h"

#include "plotunit.h"
#include "UiPlot/uiplot.h"

#include <QToolButton>
#include <QDebug>
#include <QTranslator>
#include <QtQml>
#include <QProgressBar>
#include <QMessageBox>

using namespace GT;

SDTMainWindow::SDTMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::SDTMainWindow),
  m_currentUiStatus(UI_STA_FUNCNF),
  m_connecting(false)
{
  ui->setupUi(this);
  qmlRegisterType<SevDevice>("QtCppClass", 1, 0, "SevDevice");
  qmlRegisterType<QmlStyleHelper>("QtCppClass", 1, 0, "QmlStyleHelper");
  clearStackedWidget();
  staticUiInit();
}

SDTMainWindow::~SDTMainWindow()
{
//  delete m_plot;
//  GT::deepClearList(m_sdAssemblyList);
//  delete m_gUiControl;
//  delete m_optc;
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
  m_optc=OptContainer::instance();

  m_statusBar=new SdtStatusBar(ui->treeWidget,this);
  mp_progressBar=m_statusBar->statusProgressBar();
  ui->statusBar->addPermanentWidget(m_statusBar,0);
  ui->statusBar->setToolTipDuration(2000);

  createActions();
  setAppIcon();
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
  m_actnConfig->setEnabled(false);

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
//  m_tbtnMore->setPopupMode(QToolButton::MenuButtonPopup);
  m_tbtnMore->setPopupMode(QToolButton::InstantPopup);

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
  connect(m_actnOption,SIGNAL(triggered(bool)),this,SLOT(onActnOptionClicked()));
//  connect(m_tbtnMore,SIGNAL(clicked(bool)),this,SLOT(onActnTbtnMoreClicked()));
  connect(m_actnConnect,SIGNAL(triggered(bool)),this,SLOT(onActnConnectClicked(bool)));
  connect(m_actnDisNet,SIGNAL(triggered(bool)),this,SLOT(onActnDisConnectClicked(bool)));
  connect(m_tbtnHelp,SIGNAL(clicked(bool)),this,SLOT(onActnHelpDeviceInfo()));
  connect(m_actnAboutHardware,SIGNAL(triggered(bool)),this,SLOT(onActnHelpDeviceInfo()));

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
  while (ui->mainStackedWidget->count()) {
    delete ui->mainStackedWidget->widget(0);
    qDebug()<<"delete stackedWidget "<<i;
    i++;
  }
}

void SDTMainWindow::closeEvent(QCloseEvent *e)
{
  OptContainer *optc=OptContainer::instance();
  optc->saveOpt();

  delete m_plot;
  GT::deepClearList(m_sdAssemblyList);
  delete m_gUiControl;
  delete m_optc;

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
    SdAssembly *sdriver=createSdAssembly(devConfigList.at(i));
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

void SDTMainWindow::clearNavigationTree()
{
  ui->treeWidget->clear();
}

void SDTMainWindow::globalUiPageInit()
{
  m_gUiControl=new GlobalUiControler(m_optc);
  m_gUiControl->createUis();

  m_plot=new PlotUnit;
  connect(m_plot,SIGNAL(floatingChanged(bool)),this,SLOT(onPlotFloatingChanged(bool)));
  UiPlot *uiplot=dynamic_cast<UiPlot *>(m_gUiControl->getUiWidgetByClassName("UiPlot"));
  uiplot->hBoxLayout()->addWidget(m_plot);
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
      ui->mainStackedWidget->addWidget(w);
    }
    qApp->processEvents();
  }

  uiCtr=m_gUiControl;
  uiCount=uiCtr->uiCount();
  qDebug()<<"ui global Count"<<uiCount;
  for(int i=0;i<uiCount;i++)
  {
    w=static_cast<QWidget *>(uiCtr->uiAt(i));
    ui->mainStackedWidget->addWidget(w);
  }
}

void SDTMainWindow::removeAllStackedWidget()
{
  int i=0;
  QWidget *w;
  while (ui->mainStackedWidget->count()) {
    w=ui->mainStackedWidget->widget(0);
    ui->mainStackedWidget->removeWidget(w);
    w->setParent(0);
    qDebug()<<"remove stackedWidget "<<i;
    i++;
    m_statusBar->statusProgressBar()->setValue(i);
    qApp->processEvents();
  }
}

void SDTMainWindow::disactiveAllUi()
{
  IUiWidget *uiWidget;
  for(int i=0;i<ui->mainStackedWidget->count();i++)
  {
    uiWidget=dynamic_cast<IUiWidget *>(ui->mainStackedWidget->widget(i));
    uiWidget->setUiActive(false);
  }
}

void SDTMainWindow::activeCurrentUi()
{
  IUiWidget *uiWidget=dynamic_cast<IUiWidget *>(ui->mainStackedWidget->currentWidget());
  uiWidget->setUiActive(true);
}

void SDTMainWindow::changeConfigSaveBtnStatus()
{
  IUiWidget *uiWidget=dynamic_cast<IUiWidget *>(ui->mainStackedWidget->currentWidget());
  m_actnConfig->setEnabled(uiWidget->hasConfigFunc());
  m_actnSave->setEnabled(uiWidget->hasSaveFunc());
}

void SDTMainWindow::showPlotUiOnly(bool show)
{
  qDebug()<<"showPlotUiOnly "<<show;
  if(show)
    m_plot->show();
}
void SDTMainWindow::setNavCurrentSelectedInfo()
{
  QTreeWidgetItem *item=ui->treeWidget->currentItem();
  QString info;
  QTreeWidgetItem *itemParent=NULL;
  while ((itemParent=item->parent())!=NULL)
  {
    info.prepend(item->text(0)+" ");
    item=itemParent;
  }
  info.prepend(item->text(0)+" ");
  ui->dockWidgetNav->setWindowTitle(info);
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
void SDTMainWindow::onActnTbtnMoreClicked()
{
  m_tbtnMore->showMenu();
  qDebug()<<"btn more show menu";
}
void SDTMainWindow::onActnConnectClicked(bool checked)
{

  if(!m_connecting)
  {
     m_statusBar->statusProgressBar()->setVisible(true);
    setUiAllEnable(false);
    bool isOpen=setConnect(true);
    if(isOpen)
    {
      m_connecting=true;
    }
    else
    {
      setUiStatusConnect(false);
    }
    setUiAllEnable(true);
    m_statusBar->statusProgressBar()->setVisible(false);
  }
  qDebug()<<"checked"<<checked;

}
void SDTMainWindow::onActnDisConnectClicked(bool checked)
{
  if(m_connecting)
  {
    setConnect(false);
    m_connecting=false;
  }
  qDebug()<<"checked"<<checked;
}
void SDTMainWindow::onActnHelpDeviceInfo()
{
  static bool test=true;
  if(test)
    this->showFullScreen();
  else
    showMaximized();
  test=!test;
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
  QFont font;
  font.setBold(false);
  QTreeWidgetItemIterator it(ui->treeWidget);
  while (*it) {
    (*it)->setFont(column,font);
    it++;
  }
  font.setBold(true);
  item->setFont(column,font);

  if(item->childCount()==0)
  {
    int index=item->text(COL_TARGET_CONFIG_INDEX).toInt();
    if(index<ui->mainStackedWidget->count())
    {
      ui->mainStackedWidget->setCurrentIndex(index);
      qDebug()<<"index"<<index <<"ui->mainStackedWidget->count()"<<ui->mainStackedWidget->count();
      GTUtils::delayms(10);

      disactiveAllUi();
      activeCurrentUi();
      changeConfigSaveBtnStatus();
      bool plotShow=false;
      if(item->text(COL_TARGET_CONFIG_ISPLOT)=="1")
        plotShow=true;
      showPlotUiOnly(plotShow);
      setNavCurrentSelectedInfo();
    }
  }
}

void SDTMainWindow::onStatusBarPageChanged(int pIndex)
{
  IUiWidget *uiWidget=NULL;
  ui->mainStackedWidget->setCurrentIndex(pIndex);
  QWidget *w=ui->mainStackedWidget->widget(pIndex);
  uiWidget=dynamic_cast<IUiWidget *>(w);
  UiIndexs index=uiWidget->uiIndexs();
  qDebug()<<"UiIndexs"<<tr("dev:%1,axis:%2,page:%3").arg(index.devInx).arg(index.axisInx).arg(index.pageInx);
  ui->treeWidget->clearSelection();
  ui->treeWidget->collapseAll();
  QTreeWidgetItem *selectDevItem=ui->treeWidget->topLevelItem(index.devInx);
  QTreeWidgetItem *selectAxisItem=selectDevItem->child(index.axisInx);
  QTreeWidgetItem *selectItem=selectAxisItem->child(index.pageInx);
  ui->treeWidget->expandItem(selectDevItem);
  ui->treeWidget->expandItem(selectAxisItem);
  ui->treeWidget->expandItem(selectItem);
  selectItem->setSelected(true);
}

void SDTMainWindow::onPlotFloatingChanged(bool floating)
{
  UiPlot *uiplot=dynamic_cast<UiPlot *>(m_gUiControl->getUiWidgetByClassName("UiPlot"));
  if(floating)
  {
    uiplot->hBoxLayout()->removeWidget(m_plot);
    m_plot->setParent(0);
    m_plot->showMaximized();
  }
  else
  {
    uiplot->hBoxLayout()->addWidget(m_plot);
    m_plot->show();
  }


}
SdAssembly *SDTMainWindow::createSdAssembly(DeviceConfig *cfg)
{
  SdAssembly *sd= new SdAssembly();
  connect(sd,SIGNAL(initProgressInfo(int,QString)),this,SLOT(onProgressInfo(int,QString)));
  sd->init(cfg);
  return sd;
}
void SDTMainWindow::setUiStatusConnect(bool isNet)
{
  m_actnConnect->setChecked(isNet);
  m_actnDisNet->setChecked(!isNet);
}
void SDTMainWindow::setUiAllEnable(bool en)
{
  ui->treeWidget->setEnabled(en);
  ui->mainToolBar->setEnabled(en);
  ui->mainStackedWidget->setEnabled(en);
}

bool SDTMainWindow::setConnect(bool net)
{
  //打开
  if(net)
  {
    OptAutoLoad *optAuto=dynamic_cast<OptAutoLoad *>(OptContainer::instance()->optItem("optautoload"));
    QProgressBar *bar=m_statusBar->statusProgressBar();
    if(optAuto->autoLoad())
    {
      QList<DeviceConfig*> configList;
      bool isOk;
      IDevReadWriter *idevRWriter=new DevComRWriter(0);
      configList=idevRWriter->createConfig(processCallBack,(void *)(bar),isOk);
      if(isOk)
      {
        createSdAssemblyByDevConfig(configList);
        GT::deepClearList(configList);
        delete idevRWriter;
      }
      else
      {
        QMessageBox::information(0,tr("connect error"),tr("can not connect \nmaybe \n1 net is not connecting \n2 net cable is not 1000M\n3 device net error"));
        delete idevRWriter;
        return false;
      }
    }

    bool isConnect=true;
    foreach (SdAssembly *sd, m_sdAssemblyList)
    {
      isConnect=sd->sevDevice()->enableConnection(processCallBack,(void *)(bar));
      if(isConnect==false)
      {
        bar->setValue(0);
        sd->sevDevice()->disableConnection();
        QMessageBox::information(0,tr("connect error"),tr("can not connect \nmaybe \n1 net is not connecting \n2 net cable is not 1000M\n3 device net error"));
        break;
      }
      qDebug()<<isConnect;
    }
    return isConnect;
  }
  else//关闭
  {
    foreach (SdAssembly *sd, m_sdAssemblyList)
    {
      sd->sevDevice()->disableConnection();
      qDebug()<<"disconnect ";
    }
    return true;
  }
}

void SDTMainWindow::createSdAssemblyByDevConfig(const QList<DeviceConfig *> &configList)
{

  QList<DeviceConfig *> devConfigBuf;
  int configCount=configList.count();
  qDebug()<<"configList.count()"<<configCount;

  QList<SdAssembly*>sdAssemblyListTemp;
  DeviceConfig* devConfig;
  SdAssembly* currentSdAssembly;

  for(int i=0;i<configCount;i++)
  {
    devConfig=configList.at(i);
    bool cp=false;
    for(int j=0;j<m_sdAssemblyList.count();j++)
    {
      currentSdAssembly=m_sdAssemblyList.at(j);
      DeviceConfig* tc=currentSdAssembly->sevDevice()->deviceConfig();
      bool isEqual=devConfig->isEqual(*tc);
      qDebug()<<"isEqual"<<isEqual;
      if(isEqual)//与原有的匹配
      {
        qDebug()<<"sdAssemblyListTemp.append(sdAssemblyList.takeAt(j))";
        sdAssemblyListTemp.append(m_sdAssemblyList.takeAt(j));
        cp=true;
        break;
      }
    }
    if(!cp)
    {
      //新将找不到的devConfig缓存起来
      //到删除原来的后再新建，这样可以减少内存消耗
      devConfigBuf.append(devConfig);
    }
  }

  GT::deepClearList(m_sdAssemblyList);

  foreach (DeviceConfig *cfg, devConfigBuf)
  {
    qDebug()<<"new SdAssembly()";
    currentSdAssembly=createSdAssembly(cfg);
    sdAssemblyListTemp.append(currentSdAssembly);
  }

  m_sdAssemblyList=sdAssemblyListTemp;
  qDebug()<<"after sdAssembly list count"<<m_sdAssemblyList.count();

  removeAllStackedWidget();
  clearNavigationTree();

  navigationTreeInit();
  stackedWidgetInit();
//  ui->progressBar->setValue(100);

  qDebug()<<"stackedWidget count="<<ui->mainStackedWidget->count();
}
