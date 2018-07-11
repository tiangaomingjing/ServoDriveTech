#include "sdtmainwindow.h"
#include "ui_sdtmainwindow.h"

#include "Option"
#include "iadvuser.h"
#include "advusercheck.h"
#include "advusermask.h"
#include "advusercontainer.h"
#include "dialogoption.h"
#include "dialogadvusr.h"

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

#include "configdialog.h"

#include "ivermatching.h"
#include "memeryvermatching.h"
#include "dbvermatching.h"

#include "statusmonitor.h"

#include "icom.h"
#include "sdterror.h"
#include "messageserver.h"

#include "deviceinfodialog.h"
#include "qttreemanager.h"
#include "downloaddialog.h"
#include "uploaddialog.h"
#include "servofile.h"
#include "firmwareflashdialog.h"
#include "comparisondialog.h"
#include "infodialog.h"
#include "resetdspselectdialog.h"

#include <QToolButton>
#include <QDebug>
#include <QTranslator>
#include <QtQml>
#include <QProgressBar>
#include <QMessageBox>
#include <QCloseEvent>
#include <QFileDialog>
#include <QDir>
#include <QDate>

#define UI_TREE_SHOW_COLUMN 0
#define OPT_START_INI "opt.ini"
#define ADVUSR_INI "advusr.ini"
#define FLASH_NAME "FLASH"
#define RAM_NAME "RAM"

#define ICON_SDT_LOGO_NAME            "sdtlogo.png"
#define SDT_VERSION                   "2.0.0"

using namespace GT;

SDTMainWindow::SDTMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::SDTMainWindow),
  m_currentUiStatus(UI_STA_FUNCNF),
  m_connecting(false),
  m_statusMonitor(new StatusMonitor(this))
{
  ui->setupUi(this);

  setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
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
  updateStatusMonitorDevice(sevList());

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
  m_statusBar->resetStatus();

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
  m_actnAboutVersion = new QAction(this);
  m_actnAboutVersion->setText(tr("vinfo"));
  m_actnAboutSoftware=new QAction(this);
  m_actnAboutSoftware->setText(tr("sinfo"));
  m_tbtnHelp->addAction(m_actnAboutHardware);
  m_tbtnHelp->addAction(m_actnAboutVersion);
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
  m_produceClicked = false;
  m_actnProduce=new QAction(tr("produce"),m_tbtnMore);

  m_actnAdvUser = new QAction(tr("Advanced User"), m_tbtnMore);

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
  menu->addAction(m_actnAdvUser);
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
  connect(m_actnAboutVersion, SIGNAL(triggered()), this, SLOT(onActnVersionInfoClicked()));
  connect(m_actnAboutSoftware,SIGNAL(triggered(bool)),this,SLOT(onActnHelpSoftInfoClicked()));
  connect(m_actnNewConfig,SIGNAL(triggered(bool)),this,SLOT(onActnNewConfigClicked()));
  connect(m_actnSave,SIGNAL(triggered(bool)),this,SLOT(onActnSaveClicked()));
  connect(m_actnConfig,SIGNAL(triggered(bool)),this,SLOT(onActnConfigClicked()));
  connect(m_actnProduce, SIGNAL(triggered()), this, SLOT(onActnProduceClicked()));
  connect(m_actnAdvUser, SIGNAL(triggered()), this, SLOT(onActnAdvUserClicked()));
  connect(m_actnCompare,SIGNAL(triggered(bool)),this,SLOT(onActnCompareClicked()));
  connect(m_actnUpdateFlash, SIGNAL(triggered()), this, SLOT(onActnUpdateFirmwareClicked()));
  connect(m_actnDownload, SIGNAL(triggered(bool)), this, SLOT(onActnDownloadClicked()));
  connect(m_actnUpload, SIGNAL(triggered(bool)), this, SLOT(onActnUploadClicked()));
  connect(m_actnReset,SIGNAL(triggered(bool)),this,SLOT(onActnResetDspClicked()));


  OptAutoLoad *optAuto=dynamic_cast<OptAutoLoad *>(OptContainer::instance()->optItem("optautoload"));
  if(optAuto!=NULL)
  {
    connect(optAuto,SIGNAL(autoLoadChanged(bool)),this,SLOT(onOptAutoLoadChanged(bool)));
    m_actnNewConfig->setVisible(!optAuto->autoLoad());
  }
  OptFace *optface=dynamic_cast<OptFace *>(OptContainer::instance()->optItem("optface"));
  if(optface!=NULL)
    connect(optface,SIGNAL(faceCssChanged(QString)),this,SLOT(onOptFaceCssChanged(QString)));

  OptUser *optuser = dynamic_cast<OptUser *>(OptContainer::instance()->optItem("optuser"));
  if (optuser != NULL) {
      connect(optuser, SIGNAL(usrChange(bool)), this, SLOT(onOptUserChanged(bool)));
  }

  OptPath *optpath = dynamic_cast<OptPath *>(OptContainer::instance()->optItem("optpath"));
  if (optpath != NULL) {
      connect(optpath, SIGNAL(pathesChanged(QStringList)), this, SLOT(onOptPathChanged(QStringList)));
  }
  m_downloadPath = optpath->file2ServoPath();
  QDir downDir(m_downloadPath);
  if (!downDir.exists()) {
      m_downloadPath = ".";
  }
  m_uploadPath = optpath->servo2FilePath();
  QDir upDir(m_uploadPath);
  if (!upDir.exists()) {
      m_uploadPath = ".";
  }
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
//  bool close=MessageBoxAsk(tr("Do you want to close the application?"));
//  if(close)
//  {
    emit appClosed();
    qDebug()<<"emit appclose !";
    GTUtils::delayms(2000);
    disactiveAllUi();

    m_connecting=false;
    setUiStatusConnect(m_connecting);
    m_statusMonitor->stopMonitor();
    setConnect(false);

    GTUtils::delayms(10);
    OptContainer *optc=OptContainer::instance();
    optc->saveOpt();

    AdvUserContainer *advc = AdvUserContainer::instance();
    advc->saveAdv();

    //保存当前的配置

    IDevReadWriter *idevRWriter=new DevTextRWriter(NULL);
    QList<DeviceConfig*> devConfigList;
    for(int i = 0;i<sevList().size();i++)
    {
      SevDevice *sev = sevList().at(i);
      devConfigList.append(sev->deviceConfig());
    }
    idevRWriter->saveConfig(devConfigList);
    delete idevRWriter;

    delete m_gUiControl;
    delete m_optc;
    GT::deepClearList(m_sdAssemblyList);
    e->accept();
//  }
//  else
//    e->ignore();
}
void SDTMainWindow::processCallBack(void *argv,short *value)
{
  QProgressBar *pBar=static_cast<QProgressBar *>(argv);
  pBar->setValue(*value);
  qDebug()<<"progress value ="<<*value;
  qApp->processEvents();
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
  bool hasNickName=m_sdAssemblyList.count()>1;

  QHash<QString ,QString>navTreeNameSwitchHash;
  navTreeNameSwitchHash.insert("Motor",tr("Motor"));
  navTreeNameSwitchHash.insert("Encoder",tr("Encoder"));
  navTreeNameSwitchHash.insert("Power",tr("Power"));
  navTreeNameSwitchHash.insert("Current",tr("Current"));
  navTreeNameSwitchHash.insert("Velocity",tr("Velocity"));
  navTreeNameSwitchHash.insert("Position",tr("Position"));
  navTreeNameSwitchHash.insert("Brake",tr("Brake"));
  navTreeNameSwitchHash.insert("Status",tr("Status"));
  navTreeNameSwitchHash.insert("RAM",tr("RAM"));
  navTreeNameSwitchHash.insert("FLASH",tr("FLASH"));
  navTreeNameSwitchHash.insert("IO",tr("IO"));

  for(int  i=0;i<m_sdAssemblyList.count();i++)
  {
    int axisNum;
    sd=m_sdAssemblyList.at(i);
    axisNum=sd->sevDevice()->axisNum();
    deviceItem=new QTreeWidgetItem(ui->treeWidget);
    QString prefix;
    prefix=hasNickName?tr("[%1] ").arg(sd->sevDevice()->aliasName()):"";
    deviceItem->setText(COL_TARGET_CONFIG_NAME,prefix+sd->sevDevice()->modelName());
    deviceItem->setText(COL_TARGET_CONFIG_PRM,QString::number(axisNum));
    qDebug()<<"deviceItem->setText";


    for(int i=0;i<axisNum;i++)
    {
      axisItem=sd->sevDevice()->targetTree()->child(ROW_TARGET_CONFIG_AXIS)->clone();
      axisItem->setText(COL_TARGET_CONFIG_NAME,tr("Axis_%1").arg(i+1));

      for(int j=0;j<axisItem->childCount();j++)
      {
        QString keyName = axisItem->child(j)->text(COL_TARGET_CONFIG_NAME);
        axisItem->child(j)->setText(COL_TARGET_CONFIG_NAME,navTreeNameSwitchHash.value(keyName));
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

#if UI_TREE_SHOW_COLUMN==1
  ui->treeWidget->setHeaderHidden(false);
  ui->treeWidget->setColumnCount(7);
#endif
#if UI_TREE_SHOW_COLUMN==0

  ui->treeWidget->setHeaderHidden(true);
  ui->treeWidget->setColumnHidden(1,true);
  ui->treeWidget->setColumnHidden(2,true);
  ui->treeWidget->setColumnHidden(3,true);
  ui->treeWidget->setColumnHidden(4,true);
  ui->treeWidget->setColumnHidden(5,true);
  ui->treeWidget->setColumnHidden(6,true);
#endif

  m_statusBar->updateDeviceNavTreeWhenChanged(ui->treeWidget);

  OptUser *optuser = dynamic_cast<OptUser *>(OptContainer::instance()->optItem("optuser"));
  if (optuser != NULL) {
      qDebug()<<"isAdmin"<<optuser->isAdmin();
      onOptUserChanged(optuser->isAdmin());
  }

}

void SDTMainWindow::clearNavigationTree()
{
  ui->treeWidget->clear();
}

void SDTMainWindow::globalUiPageInit()
{
  QList<SevDevice *>sevList;
  for(int i=0;i<m_sdAssemblyList.count();i++)
    sevList.append(m_sdAssemblyList.at(i)->sevDevice());
  m_gUiControl=new GlobalUiControler(sevList);
  connect(this,SIGNAL(appClosed()),m_gUiControl,SIGNAL(appClosed()),Qt::QueuedConnection);
  connect(this,SIGNAL(beforeSevDeviceChanged()),m_gUiControl,SIGNAL(beforeSevDeviceChanged()));
  connect(m_gUiControl, SIGNAL(sendSaveMsgToMain(int,QString,bool)), this, SLOT(onSaveMsgReceived(int,QString,bool)));
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
//  if(show)
//    m_plot->show();
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
  info.prepend(item->text(2)+" ");
  info.prepend(item->text(0)+" ");
  emit currentTitleChanged(info);
//  ui->dockWidgetNav->setWindowTitle(info);
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
    if (!m_produceClicked) {
        startListen();
        m_produceClicked = true;

        qDebug()<<"bool"<<m_produceClicked;
        QString path;
        QString exeName;
        #ifdef QT_NO_DEBUG
            exeName = "EpromManager.exe";
        #else
            exeName = "EpromManager_d.exe";
        #endif
        qDebug()<<"exe name"<<exeName;
        path = GTUtils::exePath();
        path = path + "/" + exeName;
        m_process = new QProcess(this);
        m_process->start(path);
        qDebug()<<"path"<<path;

//        tcpClient = new TcpConnect(block);
//        connect(tcpClient, SIGNAL(closeSignal()), this, SLOT(onProduceClosed()));
//        qDebug()<<"ss";
//        tcpClient->connectToServer();
//        qDebug()<<"aa";
    }
}

void SDTMainWindow::onActnAdvUserClicked()
{
    DialogAdvUsr dialogAdv;
    AdvUserContainer *advc = AdvUserContainer::instance();
    QList<IAdvUser*> advList = advc->advItems();
    for (int i = 0; i < advList.count(); i++) {
        IAdvUser* adv = advList.at(i);
        if (adv->name().compare("advusermask") == 0) {
            AdvUserMask *advMask = dynamic_cast<AdvUserMask*>(adv);
            advMask->setSevList(sevList());
            advMask->uiInit();
        } else {
            adv->uiInit();
        }
    }
    dialogAdv.exec();
}

void SDTMainWindow::onActnCompareClicked()
{
    ComparisonDialog compareDialog;
    compareDialog.exec();
}

void SDTMainWindow::onActnUpdateFirmwareClicked()
{
    FirmwareFlashDialog flashDialog(sevList(), 0);
    flashDialog.exec();
}

void SDTMainWindow::onActnResetDspClicked()
{
  QList<SevDevice *>rstSevList;

  if(sevList().size()>1)
  {
    //弹出窗口选择
    ResetDspSelectDialog sDialog(&rstSevList,sevList(),0);
    sDialog.exec();
    for(int i = 0;i<rstSevList.size();i++)
    {
      qDebug()<<"device name ="<<rstSevList.at(i)->modelName();
    }
    if(rstSevList.isEmpty())
      return ;
  }
  else
  {
    rstSevList.append(sevList().at(0));
  }

  //查询是否正在上伺服
  SevDevice *sev = NULL;
  for(int i = 0;i<rstSevList.size();i++)
  {
    sev = rstSevList.at(i);
    for(int axis = 0;axis<sev->axisNum();axis++)
    {
      if(sev->axisServoIsOn(axis))
      {
        QMessageBox::warning(0,tr("error"),tr("refuse to reset dsp :\ndevice :%1 axis =%2 servo is on \n ").arg(sev->modelName()).arg(axis+1));
        return ;
      }
    }
  }

  QMessageBox::StandardButton rb=QMessageBox::question(this,tr("Warning"),tr("Do you want to reset device ?"),QMessageBox::Yes|QMessageBox::No,QMessageBox::No);
  if (rb==QMessageBox::No)
  {
    return;
  }

  setUiAllEnable(false);
  m_statusMonitor->stopMonitor();

  for(int i = 0;i<rstSevList.size();i++)
  {
    bool ok = true;
    sev = rstSevList.at(i);
    ok = sev->resetDSP();
    if(!ok)
      QMessageBox::warning(0,tr("error"),tr("reset device = %1 dsp fail:\n ").arg(sev->modelName()));
    else
      m_statusBar->setMsg(tr("reset dsp successfully"));
  }

  GTUtils::delayms(3000);
  m_statusMonitor->startMonitor();
  m_statusBar->setMsg("");
  activeCurrentUi();
  setUiAllEnable(true);

}

void SDTMainWindow::startListen() {
    m_server = new MessageServer;
    if(!m_server->listen(QHostAddress::Any, 6178)) {
        qDebug()<<"Listen Failed!";
        return;
    }
    connect(m_server, SIGNAL(getStartMsg()), this, SLOT(onStartMsgReceived()));
    connect(m_server, SIGNAL(getCloseMsg()), this, SLOT(onCloseMsgReceived()));
}

void SDTMainWindow::onStartMsgReceived() {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    QString mode = m_sdAssemblyList.at(0)->sevDevice()->modelName();
    QString type = m_sdAssemblyList.at(0)->sevDevice()->typeName();
    int comNumber = m_sdAssemblyList.at(0)->sevDevice()->deviceConfig()->m_comType;
    int axisNum = m_sdAssemblyList.at(0)->sevDevice()->axisNum();
    QString dspNum = QString::number(axisNum / 2);
    QString comType;
    if (comNumber == 0) {
        comType = tr("PcDebug");
    } else {
        comType = tr("RnNet");
    }
    qDebug()<<"mode"<<mode;
    qDebug()<<"comType"<<comType;
    out<<quint16(0)<<mode<<type<<comType<<dspNum;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    qDebug()<<"type"<<type;
    m_server->replyMsg(block);
}

void SDTMainWindow::onCloseMsgReceived() {
    qDebug()<<"process released!";
    m_produceClicked = false;
    //GTUtils::delayms(20);
    m_process->close();
    delete m_process;
    delete m_server;
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
      //IVerMatching *vMatch=new MemeryVerMatching;
      IVerMatching *dbMatch=new DbVerMatching;
      IVerMatching::CheckStatus checkStatus=IVerMatching::CHECK_STA_OK;
      dbMatch->open();
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
          //checkStatus=vMatch->check(verInfo);
          checkStatus = dbMatch->check(verInfo);
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
//      vMatch->close();
//      delete vMatch;
      dbMatch->close();
      delete dbMatch;

      if(isContinue)
      {
        m_connecting=true;
        m_statusBar->statusProgressBar()->setValue(100);
        activeCurrentUi();
        m_statusMonitor->startMonitor(1000);
        m_actnNewConfig->setEnabled(false);
      }
      else
      {
        m_connecting=false;
        setConnect(false);
        m_actnNewConfig->setEnabled(true);
      }

    }
    else
    {
      m_statusBar->statusProgressBar()->setValue(50);
      if(!isAutoLoad())
      {
        SdtError::instance()->errorStringList()->append(tr("your connect com is wrong"));
        SdtError::instance()->errorStringList()->append(tr("your select com type is wrong"));
      }
      QMessageBox::information(0,tr("connect error"),tr("Net Error\n\nexception cause maybe:\n%1\n").arg(SdtError::instance()->errorStringList()->join("\n")));
    }

    setUiStatusConnect(m_connecting);
    setUiAllEnable(true);
    m_statusBar->statusProgressBar()->setVisible(false);
  }
  m_statusBar->resetStatus();

}
void SDTMainWindow::onActnDisConnectClicked(bool checked)
{
  m_connecting=false;
  setUiStatusConnect(m_connecting);
  m_statusMonitor->stopMonitor();
  disactiveAllUi();
  setConnect(false);

  m_actnNewConfig->setEnabled(true);

  qDebug()<<"checked"<<checked;
}
void SDTMainWindow::onActnHelpDeviceInfoClicked()
{
  DeviceInfoDialog devInfo;
  QList<SevDevice*>devList;
  foreach (SdAssembly *sd, m_sdAssemblyList) {
    devList.append(sd->sevDevice());
  }
  devInfo.setModal(true);
  devInfo.show();
  GTUtils::delayms(10);
  devInfo.readInfo(devList);
  devInfo.exec();
}

void SDTMainWindow::onActnVersionInfoClicked()
{
    InfoDialog infoDialog;
    infoDialog.uiInit(sevList());
    infoDialog.exec();
}


void SDTMainWindow::onActnHelpSoftInfoClicked()
{
  QMessageBox mess;
  mess.setIcon(QMessageBox::NoIcon);
  QString info;
  info=tr("Version:%1\n\nget more help from:"
          "\nhttp://www.googoltech.com").arg(SDT_VERSION);
  mess.setText(info);
  QString iconPath = GTUtils::iconPath()+ICON_SDT_LOGO_NAME;
  mess.setIconPixmap(QPixmap(iconPath));
  mess.exec();
}

void SDTMainWindow::onActnNewConfigClicked()
{
  setUiAllEnable(false);
  QList<DeviceConfig *>list;
  ConfigDialog dia(&list,0);
  if(QDialog::Rejected==dia.exec())
  {
    setUiAllEnable(true);
    return;
  }

  emit beforeSevDeviceChanged();
  m_statusBar->statusProgressBar()->setVisible(true);
  m_statusBar->statusProgressBar()->setValue(0);
  updateSDTMainUiByConfigList(list);
  m_statusBar->statusProgressBar()->setVisible(false);
  m_statusBar->statusProgressBar()->setValue(100);
  m_statusBar->setMsg("");
  setUiAllEnable(true);
}
void SDTMainWindow::onActnSaveClicked()
{
  qDebug()<<"act add write flash test clicked";
  QWidget *cw=ui->mainStackedWidget->currentWidget();
  IUiWidget *ui=dynamic_cast<IUiWidget *>(cw);//向下转型时使用dynamic_cast
  qDebug()<<ui->objectName();
  ui->writePageFLASH();
}

void SDTMainWindow::onActnConfigClicked()
{
  qDebug()<<"act add write flash test clicked";
  QWidget *cw=ui->mainStackedWidget->currentWidget();
  IUiWidget *ui=dynamic_cast<IUiWidget *>(cw);//向下转型时使用dynamic_cast
  qDebug()<<ui->objectName();
  ui->writeGenPageRAM();
}

void SDTMainWindow::onActnDownloadClicked()
{
    if (!m_connecting) {
        QMessageBox::information(0, tr("Warning"), tr("Please open com first!"));
        return;
    }
    QString downloadFileName = QString::null;
    int downloadIndex = -1;
    QList<SevDevice *> devList = sevList();
    if (devList.count() == 1) {
        downloadIndex = 0;
        downloadFileName = QFileDialog::getOpenFileName(this, tr("Open XML File"), m_downloadPath, tr("XML Files(*.xml)"));
    } else {
        DownloadDialog downloadDialog;
        downloadDialog.uiInit(devList, m_downloadPath, downloadFileName, downloadIndex);
        downloadDialog.exec();
        qDebug()<<"downloadfilename"<<downloadFileName;
        qDebug()<<"downloadIndex"<<downloadIndex;
    }
    qDebug()<<"1";
    //fileName = QFileDialog::getOpenFileName(this, tr("Open XML File"), m_downloadPath, tr("XML Files(*.xml)"));
    if (downloadFileName.isNull() || downloadIndex == -1) {
        return;
    }
    qDebug()<<"2";
    QFileInfo fileInfo;
    fileInfo.setFile(downloadFileName);
    m_downloadPath = fileInfo.filePath() + "/";
    m_statusBar->statusProgressBar()->setVisible(true);
    m_statusBar->statusProgressBar()->setValue(0);
    ServoFile *servoFile = new ServoFile(0);
    connect(servoFile, SIGNAL(sendProgressbarMsg(int,QString)), this, SLOT(onProgressInfo(int,QString)));
    qDebug()<<"3";
    bool downOk = false;
    downOk = servoFile->downLoadFile(processCallBack, (void *)(mp_progressBar), downloadFileName, devList.at(downloadIndex));
    disconnect(servoFile, SIGNAL(sendProgressbarMsg(int,QString)), this, SLOT(onProgressInfo(int,QString)));
    qDebug()<<"4";
    delete servoFile;
    m_statusBar->statusProgressBar()->setVisible(false);
    if(downOk)
    {
      m_statusBar->setMsg(tr("Download xml file OK !"));
    }
    else
    {
      m_statusBar->setMsg(tr("Error: Download xml file fails !"));
    }
    GTUtils::delayms(2000);
    m_statusBar->setMsg("");
}

void SDTMainWindow::onActnUploadClicked()
{
    if (!m_connecting) {
        QMessageBox::information(0, tr("Warning"), tr("Please open com first!"));
        return;
    }

    QString uploadFileName = QString::null;
    int uploadIndex = -1;
    QList<SevDevice *> devList = sevList();
    if (devList.count() == 1) {
        uploadIndex = 0;
        QDate curDate = QDate::currentDate();
        QString defaultName = devList.at(0)->modelName() + "_" + devList.at(0)->versionName() + "_" + QString::number(curDate.year()) + QString::number(curDate.month()) + QString::number(curDate.day());
        uploadFileName = QFileDialog::getSaveFileName(this, tr("Open XML File"), m_uploadPath + "/" + defaultName + ".xml", tr("XML Files(*.xml)"));
    } else {
        UploadDialog uploadDialog;
        uploadDialog.uiInit(devList, m_uploadPath, uploadFileName, uploadIndex);
        uploadDialog.exec();
        qDebug()<<"uploadfilename"<<uploadFileName;
        qDebug()<<"uploadindex"<<uploadIndex;
    }
    qDebug()<<"1";
    //fileName = QFileDialog::getOpenFileName(this, tr("Open XML File"), m_downloadPath, tr("XML Files(*.xml)"));
    if (uploadFileName.isNull() || uploadIndex == -1) {
        return;
    }
    qDebug()<<"2";
    QFileInfo fileInfo;
    fileInfo.setFile(uploadFileName);
    m_uploadPath = fileInfo.filePath() + "/";
    m_statusBar->statusProgressBar()->setVisible(true);
    m_statusBar->statusProgressBar()->setValue(0);
    ServoFile *servoFile = new ServoFile(0);
    connect(servoFile, SIGNAL(sendProgressbarMsg(int,QString)), this, SLOT(onProgressInfo(int,QString)));
    qDebug()<<"3";
    bool upOK = false;
    upOK = servoFile->upLoadFile(processCallBack, (void *)(mp_progressBar), uploadFileName, devList.at(uploadIndex));
    disconnect(servoFile, SIGNAL(sendProgressbarMsg(int,QString)), this, SLOT(onProgressInfo(int,QString)));
    qDebug()<<"4";
    delete servoFile;
    m_statusBar->statusProgressBar()->setVisible(false);
    if(upOK)
    {
      m_statusBar->setMsg(tr("Upload xml file OK !"));
    }
    else
    {
      m_statusBar->setMsg(tr("Error: Upload xml file fails !"));
    }
    GTUtils::delayms(2000);
    m_statusBar->setMsg("");
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

void SDTMainWindow::onOptUserChanged(bool isAdmin)
{
    if (isAdmin) {
        m_actnAdvUser->setVisible(true);
        for (int i = 0; i < ui->treeWidget->topLevelItemCount(); i++) {
            for (int j = 0; j < ui->treeWidget->topLevelItem(i)->childCount(); j++) {
                QTreeWidgetItem *flashItem = GTUtils::findItemInItem(FLASH_NAME, ui->treeWidget->topLevelItem(i)->child(j), 0);
                if (flashItem != NULL) {
                    flashItem->setHidden(false);
                }
                QTreeWidgetItem *ramItem = GTUtils::findItemInItem(RAM_NAME, ui->treeWidget->topLevelItem(i)->child(j), 0);
                if (ramItem != NULL) {
                    ramItem->setHidden(false);
                }
            }
        }
    } else {
        m_actnAdvUser->setVisible(false);
        for (int i = 0; i < ui->treeWidget->topLevelItemCount(); i++) {
            for (int j = 0; j < ui->treeWidget->topLevelItem(i)->childCount(); j++) {
                QTreeWidgetItem *flashItem = GTUtils::findItemInItem(FLASH_NAME, ui->treeWidget->topLevelItem(i)->child(j), 0);
                if (flashItem != NULL) {
                    flashItem->setHidden(true);
                }
                QTreeWidgetItem *ramItem = GTUtils::findItemInItem(RAM_NAME, ui->treeWidget->topLevelItem(i)->child(j), 0);
                if (ramItem != NULL) {
                    ramItem->setHidden(true);
                }
            }
        }
    }
}

void SDTMainWindow::onOptPathChanged(const QStringList &list)
{
    m_uploadPath = list.at(0);
    m_downloadPath = list.at(1);
}

void SDTMainWindow::onProgressInfo(int barValue, const QString &msg)
{
  //qDebug()<<"value"<<barValue<<"msg"<<msg;
//  static int styleTest=0;
  if(this->isVisible())
  {
    mp_progressBar->setValue(barValue);
    m_statusBar->setMsg(msg);
//    m_statusBar->setMsg(msg,(SdtStatusBar::MsgType)styleTest);
//    qDebug()<<"visible processbar value="<<barValue;
//    styleTest++;
//    if(styleTest>2)
//      styleTest=0;
  }
  emit initProgressInfo(barValue,msg);
}
void SDTMainWindow::onNavTreeWidgetItemClicked(QTreeWidgetItem *item, int column)
{
  Q_UNUSED(column);

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

  disactiveAllUi();
  activeCurrentUi();
  changeConfigSaveBtnStatus();
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

  int errDev = -1 ;
  errDev =  m_statusMonitor->sysHasAlarmError();
//  qDebug()<<"error dev "<<errDev;
  if( errDev == -1)
      m_statusBar->setErrorStatus(false);
  else
    m_statusBar->setErrorStatus(true);
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
  onActnDisConnectClicked(true);
  m_statusBar->setMsg(tr("Device:%1 NetError!").arg(m_sdAssemblyList.at(devId)->sevDevice()->deviceConfig()->m_modeName),SdtStatusBar::MSG_TYPE_ERROR);

}

void SDTMainWindow::onIpaSearchPhaseInfo(int barValue, const QString &msg)
{
  qDebug()<<"phase "<<msg;
  m_statusBar->setVisible(true);
  mp_progressBar->setVisible(true);
  mp_progressBar->setValue(barValue);
  m_statusBar->setMsg(msg,SdtStatusBar::MSG_TYPE_NORMAL);
}

void SDTMainWindow::onIpaWarningMsg(const QString &msg)
{
  QMessageBox::information(0,tr("Error"),msg);
}

void SDTMainWindow::onIpaDone()
{
  mp_progressBar->setVisible(false);
  ui->statusBar->setToolTip(tr("search phase complete !"));
  m_statusBar->setMsg(tr("search phase complete !"),SdtStatusBar::MSG_TYPE_NORMAL);
  GTUtils::delayms(4000);
  m_statusBar->setMsg("",SdtStatusBar::MSG_TYPE_NORMAL);
}

void SDTMainWindow::onSaveMsgReceived(int value, const QString &msg, bool isStart)
{
    if (isStart) {
        mp_progressBar->show();
        onProgressInfo(value, msg);
        setUiAllEnable(false);
    } else {
        onProgressInfo(value, msg);
        mp_progressBar->hide();
        setUiAllEnable(true);
    }
}
SdAssembly *SDTMainWindow::createSdAssembly(DeviceConfig *cfg)
{
  bool initOK=true;
  SdAssembly *sd= new SdAssembly();
  connect(sd,SIGNAL(initProgressInfo(int,QString)),this,SLOT(onProgressInfo(int,QString)));

  initOK=sd->init(cfg);
  if(initOK)
  {
    SevDevice *sev = sd->sevDevice();
    connect(sev,SIGNAL(ipaDone()),this,SLOT(onIpaDone()));
    connect(sev,SIGNAL(ipaSearchPhaseInfo(int,QString)),this,SLOT(onIpaSearchPhaseInfo(int,QString)));
    connect(sev,SIGNAL(ipaWarningMsg(QString)),this,SLOT(onIpaWarningMsg(QString)));

    return sd;
  }
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
      connect(idevRWriter, SIGNAL(sendDevProcessInfo(int,QString)), this, SLOT(onProgressInfo(int,QString)));
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
  QMessageBox::StandardButton rb = QMessageBox::question(this, tr("Warning"), msg, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
  if (rb == QMessageBox::Yes)
    return true;
  else
    return false;
}

void SDTMainWindow::createSdAssemblyListByDevConfig(const QList<DeviceConfig *> &configList)
{
  if(configList.isEmpty())
    return;
//  QList<DeviceConfig *> devConfigBuf;
//  int configCount=configList.count();
//  qDebug()<<"configList.count()"<<configCount;

//  QList<SdAssembly*>sdAssemblyListTemp;
//  DeviceConfig* devConfig;
//  SdAssembly* currentSdAssembly;

//  for(int i=0;i<configCount;i++)
//  {
//    devConfig=configList.at(i);
//    bool cp=false;
//    for(int j=0;j<m_sdAssemblyList.count();j++)
//    {
//      currentSdAssembly=m_sdAssemblyList.at(j);
//      DeviceConfig* tc=currentSdAssembly->sevDevice()->deviceConfig();
//      bool isEqual=devConfig->isEqual(*tc);
//      qDebug()<<"isEqual"<<isEqual;
//      if(isEqual)//与原有的匹配
//      {
//        sdAssemblyListTemp.append(m_sdAssemblyList.takeAt(j));
//        cp=true;
//        break;
//      }
//    }
//    if(!cp)
//    {
//      //新将找不到的devConfig缓存起来
//      //到删除原来的后再新建，这样可以减少内存消耗
//      devConfigBuf.append(devConfig);
//    }
//  }

//  GT::deepClearList(m_sdAssemblyList);

//  for(int i=0;i<devConfigBuf.size();i++)
//  {
//    DeviceConfig *cfg=devConfigBuf.at(i);
//    currentSdAssembly=createSdAssembly(cfg);
//    if(currentSdAssembly!=NULL)
//    {
//      sdAssemblyListTemp.append(currentSdAssembly);
//    }
//  }

//  m_sdAssemblyList=sdAssemblyListTemp;

  //全部移除了再新建，解决界面不响应问题
  disactiveAllUi();
  emit beforeSevDeviceChanged();

  SdAssembly* currentSdAssembly;
  GT::deepClearList(m_sdAssemblyList);

  for(int i=0;i<configList.size();i++)
  {
    DeviceConfig *cfg=configList.at(i);
    currentSdAssembly=createSdAssembly(cfg);
    if(currentSdAssembly!=NULL)
    {
      m_sdAssemblyList.append(currentSdAssembly);
    }
  }
  //------全部移除了再新建，解决界面不响应问题




  for(int i=0;i<m_sdAssemblyList.size();i++)
  {
    currentSdAssembly=m_sdAssemblyList.at(i);
    currentSdAssembly->sevDevice()->resetDevId(i);
    qDebug()<<"---------------------------------------------alias name "<<currentSdAssembly->sevDevice()->aliasName();
  }


  qDebug()<<"after sdAssembly list count"<<m_sdAssemblyList.count();

}

QList<SevDevice *> SDTMainWindow::sevList()
{
  QList<SevDevice *> list;
  foreach (SdAssembly *sda, m_sdAssemblyList) {
    list.append(sda->sevDevice());
  }

  return list;
}

void SDTMainWindow::updateSDTMainUiByConfigList(const QList<DeviceConfig *> &configList)
{
  ui->mainStackedWidget->hide();
  createSdAssemblyListByDevConfig(configList);
  removeAllStackedWidget();
  clearNavigationTree();

  navigationTreeInit();
  stackedWidgetInit();
//  ui->progressBar->setValue(100);

//  qDebug()<<"stackedWidget count="<<ui->mainStackedWidget->count();

  updateStatusMonitorDevice(sevList());
  m_gUiControl->setSevDeviceList(sevList());
  ui->mainStackedWidget->show();

}

void SDTMainWindow::updateStatusMonitorDevice(const QList<SevDevice *> &list)
{
  m_statusMonitor->setMonitorDeviceList(list);
}
