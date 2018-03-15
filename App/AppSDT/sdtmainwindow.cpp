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
#include "deviceidhelper.h"

#include "sdtstatusbar.h"

#include "globaluicontroler.h"
#include "iuiwidget.h"

#include "sdtglobaldef.h"

#include "plotunit.h"
#include "UiPlot/uiplot.h"

#include "configdialog.h"

#include "ivermatching.h"
#include "memeryvermatching.h"
#include "dbvermatching.h"

#include "statusmonitor.h"

#include "icom.h"
#include "sdterror.h"

#include <QToolButton>
#include <QDebug>
#include <QTranslator>
#include <QtQml>
#include <QProgressBar>
#include <QMessageBox>
#include <QCloseEvent>

using namespace GT;

SDTMainWindow::SDTMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::SDTMainWindow),
  m_currentUiStatus(UI_STA_FUNCNF),
  m_connecting(false),
  m_statusMonitor(new StatusMonitor(this))
{
  ui->setupUi(this);
//  qmlRegisterType<SevDevice>("QtCppClass", 1, 0, "SevDevice");
//  qmlRegisterType<QmlStyleHelper>("QtCppClass", 1, 0, "QmlStyleHelper");
  clearStackedWidget();
  staticUiInit();
}

SDTMainWindow::~SDTMainWindow()
{
  //在关闭的时候已经delete
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

  m_statusBar->resetStatus();
  updateStatusMonitorDevice(m_sdAssemblyList);

  connect(m_statusMonitor,SIGNAL(alarmError(quint16,quint16,bool)),this,SLOT(onDeviceAlarmError(quint16,quint16,bool)));
  connect(m_statusMonitor,SIGNAL(netError(quint16)),this,SLOT(onDeviceNetError(quint16)));

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

  ui->treeWidget->setMinimumWidth(150);

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
  m_actnConnect->setStatusTip(tr("connect to servo:you can manul to load by change:toogle More->Option->AutoLoad"));

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
  m_actnNewConfig->setStatusTip(tr("select your correct system"));

  m_actnDownload=new QAction(this);
  m_actnDownload->setText(tr("dwnload"));
  m_actnDownload->setStatusTip(tr("download the  parameters to device"));

  m_actnUpload=new QAction(this);
  m_actnUpload->setText(tr("upload"));
  m_actnUpload->setStatusTip(tr("save the device parameters to xml files"));

  m_actnCompare=new QAction(this);
  m_actnCompare->setText(tr("compare"));
  m_actnCompare->setStatusTip(tr("compare the old xml with new xml files"));

  m_actnConfig=new QAction(this);
  m_actnConfig->setText(tr("config"));
  m_actnConfig->setEnabled(false);
  m_actnConfig->setStatusTip(tr("download the parameters to device and immediately active"));

  m_actnSave=new QAction(this);
  m_actnSave->setText(tr("save"));
  m_actnSave->setStatusTip(tr("permanently save the parameters to device\nyou should reset the system to make it active"));

  QWidget *spacer=new QWidget(this);
  spacer->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

  m_tbtnHelp=new QToolButton(this);
  m_tbtnHelp->setPopupMode(QToolButton::MenuButtonPopup);
  m_tbtnHelp->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
  m_tbtnHelp->setText(tr("help"));
  m_tbtnHelp->setStatusTip(tr("query the hardware and software infomation"));
  m_actnAboutHardware=new QAction(this);
  m_actnAboutHardware->setText(tr("hinfo"));
  m_actnAboutSoftware=new QAction(this);
  m_actnAboutSoftware->setText(tr("sinfo"));
  m_tbtnHelp->addAction(m_actnAboutHardware);
  m_tbtnHelp->addAction(m_actnAboutSoftware);


  //----------------more toolbutton----------------------------
  m_tbtnMore=new QToolButton(this);
  m_tbtnMore->setText(tr("more"));
  m_tbtnMore->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
//  m_tbtnMore->setToolButtonStyle(Qt::ToolButtonIconOnly);
//  m_tbtnMore->setPopupMode(QToolButton::MenuButtonPopup);
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
  connect(m_actnOption,SIGNAL(triggered(bool)),this,SLOT(onActnOptionClicked()));
  connect(m_tbtnMore,SIGNAL(clicked(bool)),this,SLOT(onActnTbtnMoreClicked()));
  connect(m_actnConnect,SIGNAL(triggered(bool)),this,SLOT(onActnConnectClicked(bool)));
  connect(m_actnDisNet,SIGNAL(triggered(bool)),this,SLOT(onActnDisConnectClicked(bool)));
  connect(m_tbtnHelp,SIGNAL(clicked(bool)),this,SLOT(onActnHelpDeviceInfoClicked()));
  connect(m_actnAboutHardware,SIGNAL(triggered(bool)),this,SLOT(onActnHelpDeviceInfoClicked()));
  connect(m_actnNewConfig,SIGNAL(triggered(bool)),this,SLOT(onActnNewConfigClicked()));
  connect(m_actnSave,SIGNAL(triggered(bool)),this,SLOT(onActnSaveClicked()));
  connect(m_actnProduce, SIGNAL(triggered()), this, SLOT(onActnProduceClicked()));

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
  bool close=MessageBoxAsk(tr("Do you want to close the application?"));
  if(close)
  {
    disactiveAllUi();

    setConnect(false);

    OptContainer *optc=OptContainer::instance();
    optc->saveOpt();

    //保存当前的配置

    delete m_plot;
    GT::deepClearList(m_sdAssemblyList);
    delete m_gUiControl;
    delete m_optc;

    e->accept();
  }
  else
    e->ignore();
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

  if(ui->treeWidget->topLevelItem(0)!=NULL)
  {
    ui->treeWidget->expandItem(ui->treeWidget->topLevelItem(0));
    if(ui->treeWidget->topLevelItem(0)->child(0)!=NULL)
    {
      ui->treeWidget->expandItem(ui->treeWidget->topLevelItem(0)->child(0));
      if(ui->treeWidget->topLevelItem(0)->child(0)->child(0)!=NULL)
        ui->treeWidget->topLevelItem(0)->child(0)->child(0)->setSelected(true);
    }
  }
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

void SDTMainWindow::onActnProduceClicked() {
    QString path;
    QString exeName;
#ifdef QT_NO_DEBUG
    exeName = "EpromManager.exe";
#else
    exeName = "EpromManager_d.exe";
#endif
    path = GTUtils::exePath();
    path = path + "/" + exeName;
    QProcess *process = new QProcess(this);
    process->start(path);
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
    bool isContinue=true;
    SdtError::instance()->errorStringList()->clear();
    m_statusBar->statusProgressBar()->setVisible(true);
    setUiAllEnable(false);
    m_statusBar->statusProgressBar()->setValue(5);
    bool isOpen=setConnect(true);
    if(isOpen)
    {
      /*if(isAutoLoad())
      {
        //2 根据版本判断是否加CRC
        //3 是否要进行参数检查 m_versionNeedCheck=(softIsBigger128&&hardIsBigger128);
      }
      else
      {
        //1 读软件版本校验 不对要提示相关信息
        //2 根据版本判断是否加CRC
        //3 是否要进行参数检查 m_versionNeedCheck=(softIsBigger128&&hardIsBigger128);
      }*/
      DeviceIdHelper idHelper;
      IVerMatching *vMatch=new MemeryVerMatching;
      IVerMatching::CheckStatus checkStatus=IVerMatching::CHECK_STA_OK;
      vMatch->open();
      foreach (SdAssembly*sd, m_sdAssemblyList)
      {
        ComDriver::ICom *com=sd->sevDevice()->socketCom();
        idHelper.setCom(com);

        //-------如果不是自动匹配，要进行V版本配对检查------
        if(isAutoLoad()==false)
        {
          bool vok=true;
          QString ver=idHelper.readVersion(vok);
          QString verCurrent=sd->sevDevice()->versionName();
          if(ver!=verCurrent)
          {
            bool accept=MessageBoxAsk(tr("current SDT version = %1\ndevice version = %2\nnot match !\ndo you want to force to continue?\n").arg(verCurrent).arg(ver));
            if(accept==false)
            {
              isContinue=false;
              break;
            }
          }
        }

        //------组合版本匹配-------
        quint32 p,c,v,f;
        p=c=v=f=0;
        if(com->iComType()!=ComDriver::ICOM_TYPE_PCDEBUG)
        {
          bool pok=true;
          bool cok=true;
          bool vok=true;
          bool fok=true;
          p=idHelper.readPwrId(pok);
          c=idHelper.readCtrId(cok);
          v=idHelper.readVersion(vok).remove(0,1).toUInt();
          f=idHelper.readFpgaId(fok);
          VerInfo verInfo;
          verInfo.c=c;
          verInfo.f=f;
          verInfo.p=p;
          verInfo.v=v;
          checkStatus=vMatch->check(verInfo);
        }

        if(checkStatus!=IVerMatching::CHECK_STA_OK)
        {
          QString msg;
          if(checkStatus==IVerMatching::CHECK_STA_NSUPPORT)
            msg=tr("device's componoent C%1-V%2-F%3-P%4 is not supported\nit maybe cause some error!\ndo you want to continue?\n").arg(c).arg(v).arg(f).arg(p);
          else
            msg=tr("device's componoent C%1-V%2-F%3-P%4 can not find in your soft database\nyou should update your software from\nhttp://www.googoltech.com.cn\nif you force to continue it maybe cause some error!\ndo you want to continue?\n").arg(c).arg(v).arg(f).arg(p);
          bool accept=MessageBoxAsk(msg);
          if(accept==false)
          {
            isContinue=false;
            break;
          }
        }

        sd->sevDevice()->setVersionAttributeActive();

      }
      vMatch->close();
      delete vMatch;

      if(isContinue)
      {
        m_connecting=true;
        m_statusBar->statusProgressBar()->setValue(100);
        activeCurrentUi();
        m_statusMonitor->startMonitor(1000);
      }
      else
      {
        m_connecting=false;
        setConnect(false);
      }

    }
    else
    {
      m_statusBar->statusProgressBar()->setValue(50);
      if(!isAutoLoad())
      {
        SdtError::instance()->errorStringList()->append(tr("your connect com is worong"));
        SdtError::instance()->errorStringList()->append(tr("your select com type is wrong"));
      }
      QMessageBox::information(0,tr("connect error"),tr("Net Error\n\nexception cause maybe:\n%1\n").arg(SdtError::instance()->errorStringList()->join("\n")));
    }

    setUiStatusConnect(m_connecting);
    setUiAllEnable(true);
    m_statusBar->statusProgressBar()->setVisible(false);
  }
  qDebug()<<"checked"<<checked;

}
void SDTMainWindow::onActnDisConnectClicked(bool checked)
{
  disactiveAllUi();
  setConnect(false);
  m_connecting=false;
  setUiStatusConnect(m_connecting);
  m_statusMonitor->stopMonitor();
  qDebug()<<"checked"<<checked;
}
void SDTMainWindow::onActnHelpDeviceInfoClicked()
{
  static bool test=true;
  if(test)
    this->showFullScreen();
  else
    showMaximized();
  test=!test;
}
void SDTMainWindow::onActnNewConfigClicked()
{
  QList<DeviceConfig *>list;
  ConfigDialog dia(&list,0);
  dia.exec();
  m_statusBar->statusProgressBar()->setVisible(true);
  m_statusBar->statusProgressBar()->setValue(0);
  updateSDTMainUiByConfigList(list);
  m_statusBar->statusProgressBar()->setVisible(false);
  m_statusBar->statusProgressBar()->setValue(100);
  m_statusBar->setMsg("");
}
void SDTMainWindow::onActnSaveClicked()
{
  qDebug()<<"act add write flash test clicked";
  QWidget *cw=ui->mainStackedWidget->currentWidget();
  IUiWidget *ui=dynamic_cast<IUiWidget *>(cw);//向下转型时使用dynamic_cast
  qDebug()<<ui->objectName();
  ui->writePageFLASH();
}

void SDTMainWindow::onOptAutoLoadChanged(bool changed)
{
  m_actnNewConfig->setVisible(!changed);
  qDebug()<<"m_actnNewConfig->setVisible"<<!changed;
}
void SDTMainWindow::onOptFaceCssChanged(const QString &css)
{
  setAppIcon();
  qDebug()<<"setAppIcon"<<css;
}
void SDTMainWindow::onProgressInfo(int barValue,QString msg)
{
  qDebug()<<"value"<<barValue<<"msg"<<msg;
  static int styleTest=0;
  if(this->isVisible())
  {
    mp_progressBar->setValue(barValue);
    m_statusBar->setMsg(msg,(SdtStatusBar::MsgType)styleTest);
//    qDebug()<<"visible processbar value="<<barValue;
    styleTest++;
    if(styleTest>2)
      styleTest=0;
  }
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
//!
//! \brief SDTMainWindow::onStatusBarPageChanged
//! 响应状态栏弹出导航单击时切换页面
//! \param pIndex
//!
void SDTMainWindow::onStatusBarPageChanged(int pIndex)
{
  //1 set all ui active false
  //2 set current ui active true

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
//!
//! \brief SDTMainWindow::onDeviceAlarmError
//! 驱动器报警时 1更新报警信息到statusBar状态树 2只要有一个报警，就显示报警信息
//! \param devId
//! \param axisInx
//! \param hasError
//!
void SDTMainWindow::onDeviceAlarmError(quint16 devId, quint16 axisInx, bool hasError)
{
  m_statusBar->setAlarmErrorStatus(devId,axisInx,hasError);
  m_statusBar->setErrorStatus(hasError);
}
//!
//! \brief SDTMainWindow::onDeviceNetError
//! 1 编码器刷新页面停止
//! 2 状态刷新页面停止
//! 3 停止画图
//! 4 关闭通信
//! 5 通信断线标志显示
//! 6 设置状态显示Label信息
//!
void SDTMainWindow::onDeviceNetError(quint16 devId)
{


  // 3
  // To be add...

  // 1 2
  //4 5
  onActnDisConnectClicked(true);

}
SdAssembly *SDTMainWindow::createSdAssembly(DeviceConfig *cfg)
{
  bool initOK=true;
  SdAssembly *sd= new SdAssembly();
  connect(sd,SIGNAL(initProgressInfo(int,QString)),this,SLOT(onProgressInfo(int,QString)));
  initOK=sd->init(cfg);
  if(initOK)
    return sd;
  else
  {
    delete sd;
    return NULL;
  }
}
void SDTMainWindow::setUiStatusConnect(bool isNet)
{
  m_actnConnect->setChecked(isNet);
  m_actnDisNet->setChecked(!isNet);
  m_statusBar->setConnectStatus(isNet);
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
    QProgressBar *bar=m_statusBar->statusProgressBar();
    if(isAutoLoad())
    {
      QList<DeviceConfig*> configList;
      bool isOk;
      IDevReadWriter *idevRWriter=new DevComRWriter(0);
      configList=idevRWriter->createConfig(processCallBack,(void *)(bar),isOk);
      if(isOk)
      {
        if(!configList.isEmpty())
        {
          updateSDTMainUiByConfigList(configList);
          GT::deepClearList(configList);
        }
        delete idevRWriter;
      }
      else
      {
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
        break;
      }
      qDebug()<<"isConnect="<<isConnect;
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
bool SDTMainWindow::isAutoLoad()
{
  OptAutoLoad *optAuto=dynamic_cast<OptAutoLoad *>(OptContainer::instance()->optItem("optautoload"));
  return optAuto->autoLoad();
}
bool SDTMainWindow::MessageBoxAsk(const QString &msg)
{
  QMessageBox::StandardButton rb = QMessageBox::question(this, tr("Warring"), msg, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
  if (rb == QMessageBox::Yes)
    return true;
  else
    return false;
}

void SDTMainWindow::createSdAssemblyListByDevConfig(const QList<DeviceConfig *> &configList)
{
  if(configList.isEmpty())
    return;
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
    if(currentSdAssembly!=NULL)
    {
      sdAssemblyListTemp.append(currentSdAssembly);
    }
  }

  m_sdAssemblyList=sdAssemblyListTemp;
  qDebug()<<"after sdAssembly list count"<<m_sdAssemblyList.count();

}

void SDTMainWindow::updateSDTMainUiByConfigList(const QList<DeviceConfig *> &configList)
{
  createSdAssemblyListByDevConfig(configList);
  removeAllStackedWidget();
  clearNavigationTree();

  navigationTreeInit();
  qDebug()<<"stackedWidgetInit";
  stackedWidgetInit();
//  ui->progressBar->setValue(100);

//  qDebug()<<"stackedWidget count="<<ui->mainStackedWidget->count();
  updateStatusMonitorDevice(m_sdAssemblyList);
}

void SDTMainWindow::updateStatusMonitorDevice(const QList<SdAssembly *> &sdAssemblyList)
{
  QList<SevDevice *>list;
  foreach (SdAssembly *sda, sdAssemblyList) {
    list.append(sda->sevDevice());
  }
  m_statusMonitor->setMonitorDeviceList(list);
}
