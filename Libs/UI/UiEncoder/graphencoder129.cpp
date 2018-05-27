#include "graphencoder129.h"
#include "ui_graphencoder129.h"
#include "igraphencoder_p.h"
#include "sdtglobaldef.h"
#include <qmath.h>

#include "EncConfig"
#include "idatabinding.h"
#include "encconfigbinding129.h"

#include "iuiwidget.h"
#include "sevdevice.h"

#include "qwt_dial_needle.h"
#include "uiencoder.h"

#include <QTimer>

#define KEY_NAME_POS          "gSevDrv.sev_obj.cur.rsv.pos"
#define KEY_NAME_POS_IN       "gSevDrv.sev_obj.cur.rsv.pos_in"
#define KEY_NAME_POS_OFFSET   "gSevDrv.sev_obj.cur.rsv.prm.pos_ofst_3"
#define KEY_NAME_PPN          "gSevDrv.sev_obj.cur.mot.PPN_1"
#define KEY_NAME_SEQ_DIR      "gSevDrv.sev_obj.cur.rsv.prm.seq_dir"
#define KEY_NAME_ENC_INFO     "gSevDrv.sev_obj.cur.pro.enc_info.all"
#define KEY_NAME_LOST         "gSevDrv.sev_obj.cur.rsv.prm.abs_type.all"

#define PRM_POS_OFFSET_INX 1
#define LINE_NUMBER_INDEX 2
#define FPGA_ABS_CFG_INDEX 3
#define PRM_SEQ_DIR_INX 4

class GraphEncoder129Private:public IGraphEncoderPrivate
{
  Q_DECLARE_PUBLIC(GraphEncoder129)
public:
  GraphEncoder129Private(){}
  ~GraphEncoder129Private(){}
protected:

};

GraphEncoder129::GraphEncoder129(QWidget *parent) :
  IGraphEncoder(*(new GraphEncoder129Private),parent),
  ui(new Ui::GraphEncoder129)
{
  ui->setupUi(this);
  initDial(ui->Dial_encElectronic);
  initDial(ui->Dial_encMachine);
  ui->Dial_encElectronic->setTitle(tr("Electronic Angle"));
  ui->Dial_encMachine->setTitle(tr("Mechanical Angle"));

  setEncErrorUiEnable(false);

  setEncConfigUiEnable(false);

  ui->btn_encConfig->setCheckable(true);
  ui->spinBox_encLine->setVisible(true);
  ui->comboBox_encBitNum->setVisible(false);
  QStringList comList;
  comList<<"11"<<"13"<<"17"<<"20"<<"21"<<"22"<<"23";
  ui->comboBox_encBitNum->addItems(comList);
  ui->label_encLineNum->setText(tr("encoder lineNumber:"));
  ui->btn_encClearErr->setText(tr("clearAlarm"));
  ui->btn_encSavePhase->setEnabled(false);

  //-------------------初始化编码器配置设置框--------------------
  ui->toolBox_encConfig->setItemText(0,tr("Enc None"));
  ui->toolBox_encConfig->setItemText(1,tr("Enc Absolute"));
  ui->toolBox_encConfig->setItemText(2,tr("Enc Increase"));
  ui->toolBox_encConfig->setItemText(3,tr("Enc Resolution"));

  ui->label_encMsg->setText(tr("active after reset"));
  ui->label_encMsg->setVisible(false);

  ui->label_encSearchValue->setText("5");

//  QStringList list;
//  list<<tr("0 DuoMoChuan")<<tr("1 NiKang")<<tr("2 Haidehan")<<tr("3 SanXie")<<tr("4 XiongXia")<<tr("5 AnChuan");
//  ui->listWidget_encAbsolute->addItems(list);

  connect(ui->btn_encConfig,SIGNAL(clicked(bool)),this,SLOT(onBtnEncConfigClicked(bool)));
  connect(ui->btn_encSaveConfig,SIGNAL(clicked(bool)),this,SLOT(onBtnEncConfigSaveClicked()));
  connect(ui->listWidget_encAbsolute,SIGNAL(currentRowChanged(int)),this,SLOT(onEncConfigListWidgetRowChanged(int)));
  connect(ui->btn_encClearErr,SIGNAL(clicked(bool)),this,SLOT(onBtnClearEcnAlarmClicked()));

  connect(ui->rbtn_encBit,SIGNAL(toggled(bool)),this,SLOT(onRadioBtnClicked()));
  connect(ui->rbtn_encLine,SIGNAL(toggled(bool)),this,SLOT(onRadioBtnClicked()));
  connect(ui->btn_encSearch,SIGNAL(clicked(bool)),this,SLOT(onBtnSearchPhaseClicked()));
  connect(ui->btn_encSavePhase,SIGNAL(clicked(bool)),this,SLOT(onBtnSavePhaseClicked()));
}

GraphEncoder129::~GraphEncoder129()
{
  Q_D(GraphEncoder129);
  GT::deletePtrObject(d->m_encConfigManage);
  delete ui;
}
void GraphEncoder129::setCustomVisitActive(IUiWidget *uiWidget)
{
  Q_D(GraphEncoder129);
  d->m_iDataBinding=new EncConfigBinding129(this);
  qDebug()<<"d->m_iDataBinding=new EncConfigBinding129(this)";

  createSupportEncoderItem();
  qDebug()<<"createSupportEncoderItem()";

  UiEncoder *encUi=dynamic_cast<UiEncoder *>(uiWidget);
  connect(encUi,SIGNAL(encActive()),this,SLOT(onEncActive()));

}
void GraphEncoder129::setUiVersionName()
{
  Q_D(GraphEncoder129);
  d->m_versionName="V129";
}

void GraphEncoder129::setupDataMappings()
{

}
void GraphEncoder129::syncTreeDataToUiFace()
{
  Q_D(GraphEncoder129);
  qDebug()<<"TEST_OUT syncMultiTreeToUiData";
  d->m_iDataBinding->syncMultiTreeToUiData();//just sync tree data to encconfigdata
}
quint32 GraphEncoder129::getLineNumber()
{
  Q_D(GraphEncoder129);
  quint32 num=d->m_treeWidget->topLevelItem(LINE_NUMBER_INDEX)->text(GT::COL_PAGE_TREE_VALUE).toUInt();
  return num;
}
void GraphEncoder129::createSupportEncoderItem()
{
  Q_D(GraphEncoder129);
  d->m_encConfigManage=new EncConfigManage;

  //注意在这里addEncItem的顺序位置不能改变
  IEncConfigItem *encItem=new EncConfigDuoMoItem;
  encItem->createAttributeUi();
  //根据版本不同，还可以增加其它的设置
//  encItem->setWarningsString("aaa");
//  encItem->setLostOper(xxx);
//  encItem->setAlarmOper(xx);
  d->m_encConfigManage->addEncItem(encItem);

  encItem=new EncConfigNiKangItem;
  encItem->createAttributeUi();
  d->m_encConfigManage->addEncItem(encItem);

  encItem=new EncConfigHaidehanItem;
  encItem->createAttributeUi();
  d->m_encConfigManage->addEncItem(encItem);

  encItem=new EncConfigSanXieItem;
  encItem->createAttributeUi();
  d->m_encConfigManage->addEncItem(encItem);

  encItem=new EncConfigSongXiaItem;
  encItem->createAttributeUi();
  d->m_encConfigManage->addEncItem(encItem);

  encItem=new EncConfigYaskawaItem;
  encItem->createAttributeUi();
  d->m_encConfigManage->addEncItem(encItem);

  ui->listWidget_encAbsolute->addItems(d->m_encConfigManage->itemNames());

  ui->rbtn_encLine->setChecked(true);
}

void GraphEncoder129::onUpdateTimeOut()
{
  Q_D(GraphEncoder129);
  quint32 pos;
  quint32 posIn;
  quint32 posOfst;
  quint16 ppn;
  qint16 seqDir;
  quint16 encInfo;
  quint16 absType;
  pos=readPos(KEY_NAME_POS);
//  qDebug()<<"pos"<<pos;
  posIn=readPosInput(KEY_NAME_POS_IN);
//  qDebug()<<"posIn"<<posIn;
  posOfst=readPosOffset(KEY_NAME_POS_OFFSET);
  d->m_posOffset = posOfst;
//  qDebug()<<"posOfst"<<posOfst;
  ppn=readPPN(KEY_NAME_PPN);
//  qDebug()<<"ppn"<<ppn;
  seqDir=readSeqDir(KEY_NAME_SEQ_DIR);
  d->m_phaseDir = seqDir;
//  qDebug()<<"seqDir"<<seqDir;
  encInfo=readEncInfo(KEY_NAME_ENC_INFO);
//  qDebug()<<"encInfo errorcode"<<encInfo;
  absType=readErrLost(KEY_NAME_LOST);
//  qDebug()<<"absType lost"<<absType;

  qDebug()<<"encoder axisSize:"<<d->m_dev->axisNum()<<"current axis"<<d->m_uiWidget->uiIndexs().axisInx<<"update ...";
//  var strPos=m_cmd.readCommand("gSevDrv.sev_obj.cur.rsv.pos");
//  pos.text=parseInt(strPos);
  ui->label_encReal->setText(QString::number(pos));
  ui->label_encOffset->setText(QString::number(posOfst));
  ui->label_encInput->setText(QString::number(posIn));
  ui->label_encPhase->setText(QString::number(seqDir));


//  var strPosIn=m_cmd.readCommand("gSevDrv.sev_obj.cur.rsv.pos_in");
//  posIn.text=parseInt(strPosIn);
//  var precision=parseInt(m_cmd.readCommand("gSevDrv.sev_obj.cur.rsv.prm.line_num_3"));
//  if(strPosIn!=="NULL")
//      gauge.value=360*parseInt(strPosIn)/precision;
  quint32 lineNumber=getLineNumber();
  double machineValue=360*posIn/lineNumber;
  ui->Dial_encMachine->setValue(machineValue);

  double temp=(machineValue*ppn);
  int electronicValue=temp;
  electronicValue%=360;
  ui->Dial_encElectronic->setValue(electronicValue);

//  encInfo=0x10f0;
  showEncoderError(absType,encInfo);

}

//!
//! \brief GraphEncoder129::onBtnEncConfigClicked 打开编码器设置对话框
//! \param checked
//!
void GraphEncoder129::onBtnEncConfigClicked(bool checked)
{
  setEncConfigUiEnable(checked);
  Q_D(GraphEncoder129);

  d->m_uiWidget->readPageFLASH();
  //读一次树数据,获取当前文件中的编码器配置信息
  initCurEncConfigItem();
  d->m_encConfigManage->setCurAttributeWidget(d->m_curEncConfigItem->attributeUi());
  d->m_iDataBinding->multiBind(static_cast<QObject*>(d->m_curEncConfigItem),d->m_treeWidget);
  d->m_iDataBinding->syncMultiTreeToUiData();//just sync tree data to encconfigdata

  updateEncConfigUiByCurrentConfigItem();

  ui->label_encMsg->setVisible(false);

  qDebug()<<"open encItemcount"<<d->m_encConfigManage->itemNames().count();

}
void GraphEncoder129::onRadioBtnClicked()
{
  if(ui->rbtn_encLine->isChecked())
  {
    ui->spinBox_encLine->setVisible(true);
    ui->comboBox_encBitNum->setVisible(false);
    ui->label_encLineNum->setText(tr("EnclineNumber:"));
    ui->spinBox_encLine->setValue(qPow(2,ui->comboBox_encBitNum->currentText().toUInt()));
  }
  else
  {
    ui->spinBox_encLine->setVisible(false);
    ui->comboBox_encBitNum->setVisible(true);
    ui->label_encLineNum->setText(tr("EncbitNumber:"));
  }
}
void GraphEncoder129::onBtnSearchPhaseClicked()
{
  Q_D(GraphEncoder129);
  static int test = 0;
//  if(!d->m_dev->isConnecting())
//    return ;
  qDebug()<<"search phase";
//  if(d->m_dev->searchPhaseStart(d->m_uiWidget->uiIndexs().axisInx,ui->hSlider_encSearchPercent->value()))
    ui->btn_encSavePhase->setEnabled(true);
    d->m_posOffset = 100 + test;
    d->m_phaseDir = test;
    test ++;
}

void GraphEncoder129::onBtnSavePhaseClicked()
{
  Q_D(GraphEncoder129);
  d->m_treeWidget->topLevelItem(PRM_POS_OFFSET_INX)->setText(GT::COL_PAGE_TREE_VALUE,QString::number(d->m_posOffset));
  d->m_treeWidget->topLevelItem(PRM_SEQ_DIR_INX)->setText(GT::COL_PAGE_TREE_VALUE,QString::number(d->m_phaseDir));
  d->m_dev->writeItemFlash(d->m_uiWidget->uiIndexs().axisInx,d->m_treeWidget->topLevelItem(PRM_POS_OFFSET_INX));
  d->m_dev->writeItemFlash(d->m_uiWidget->uiIndexs().axisInx,d->m_treeWidget->topLevelItem(PRM_SEQ_DIR_INX));
}
void GraphEncoder129::onEncConfigListWidgetRowChanged(int curRow)
{
  Q_D(GraphEncoder129);
  if(curRow<d->m_encConfigManage->itemNames().count())
  {
    d->m_curEncConfigItem=d->m_encConfigManage->encItem(curRow);
    updateEncConfigUiByCurrentConfigItem();
  }
  qDebug()<<"current row="<<curRow;
}
void GraphEncoder129::onEncActive()
{
  qDebug()<<"onEncActive";
  initCurEncConfigItem();
}
void GraphEncoder129::onBtnClearEcnAlarmClicked()
{
  Q_D(GraphEncoder129);
  d->m_dev->genCmdWrite(KEY_NAME_ENC_INFO,0,d->m_uiWidget->uiIndexs().axisInx);
  qDebug()<<"clear enc alarm";
}

void GraphEncoder129::onBtnEncConfigSaveClicked()
{
  Q_D(GraphEncoder129);
  quint8 inx=ui->listWidget_encAbsolute->currentRow();

  d->m_curEncConfigItem=d->m_encConfigManage->encItem(inx);
  if(d->m_curEncConfigItem!=NULL)
  {
    if(ui->rbtn_encBit->isChecked())
    {
      quint32 lineNum=ui->comboBox_encBitNum->currentText().toUInt();
      d->m_curEncConfigItem->setLineNumber(qPow(2,lineNum));

    }
    else
      d->m_curEncConfigItem->setLineNumber(ui->spinBox_encLine->value());
    qDebug()<<"lineNumer"<<d->m_curEncConfigItem->lineNumber();

    d->m_curEncConfigItem->execute();

    d->m_iDataBinding->multiBind(static_cast<QObject*>(d->m_curEncConfigItem),d->m_treeWidget);
    d->m_iDataBinding->syncMultiUiDataToTree();
  }
  d->m_uiWidget->writePageFLASH();

  ui->label_encMsg->setVisible(true);

}

void GraphEncoder129::initDial(QwtDial *dial)
{
  QFontMetrics fm(qApp->font());
  QFont font;
  font.setPixelSize(fm.height()*1.5);
  dial->setFont(font);
  dial->setTracking( false );
  dial->setFocusPolicy( Qt::StrongFocus );

  QColor needleColor( Qt::red );

  dial->setOrigin( 90 );
  dial->setScaleArc( 0.0, 360.0 );
  dial->setScaleMaxMinor( 5 );
  dial->setScaleMaxMajor( 18 );
  dial->setScale( 0, 360.0 );

  needleColor = QColor( "Goldenrod" );


  QwtDialSimpleNeedle *needle = new QwtDialSimpleNeedle(
      QwtDialSimpleNeedle::Arrow, true, needleColor,
      QColor( Qt::gray ).light( 130 ) );

  dial->setNeedle( needle );

  const QColor base( QColor( Qt::darkGray ).dark( 110 ) );

  QPalette palette;
  palette.setColor( QPalette::Base, base );
  palette.setColor( QPalette::Window, base.dark( 110 ) );
  palette.setColor( QPalette::Mid, base.dark( 110 ) );
  palette.setColor( QPalette::Light, base.light( 170 ) );
  palette.setColor( QPalette::Dark, base.dark( 170 ) );
  palette.setColor( QPalette::Text, base.dark( 200 ).light( 800 ) );
  palette.setColor( QPalette::WindowText, base.dark( 200 ) );

  dial->setPalette( palette );
  dial->setLineWidth( 3 );
  dial->setFrameShadow( QwtDial::Raised );
}
void GraphEncoder129::setEncConfigUiEnable(bool en)
{
//  ui->comboBox_encBitNum->setVisible(en);
//  ui->label_encLineNum->setVisible(en);
//  ui->spinBox_encLine->setVisible(en);
//  ui->btn_encSaveConfig->setVisible(en);
//  ui->rbtn_encBit->setVisible(en);
//  ui->rbtn_encLine->setVisible(en);
//  ui->toolBox_encConfig->setVisible(en);
//  ui->groupBox_encLineSelect->setVisible(en);
  ui->widget_encConfigEdit->setVisible(en);
}
void GraphEncoder129::setEncErrorUiEnable(bool en)
{
  ui->listWidget_encErr->setVisible(en);
  ui->btn_encClearErr->setVisible(en);
}
void GraphEncoder129::updateEncConfigUiByCurrentConfigItem()
{
  Q_D(GraphEncoder129);
  if(d->m_curEncConfigItem!=NULL)
  {
    //更新编码器大类型
    qDebug()<<"configdata"<<d->m_curEncConfigItem->encConfigData();
    int enctypeInx=(int)d->m_curEncConfigItem->encType();
    qDebug()<<"enctypeInx"<<enctypeInx;
    if(enctypeInx<ui->toolBox_encConfig->count())
      ui->toolBox_encConfig->setCurrentIndex(enctypeInx);
    else
      ui->toolBox_encConfig->setCurrentIndex(0);

    //更新线数
    ui->spinBox_encLine->setValue(d->m_curEncConfigItem->lineNumber());

    //更新编码器对应的特性UI
    QWidget *w=d->m_encConfigManage->curAttributeWidget();
    d->m_curEncConfigItem->updateAttributeUi();
    if(w!=NULL)
    {
      ui->vlayout_attributeWidget->removeWidget(w);
      w->hide();
    }
    ui->vlayout_attributeWidget->addWidget(d->m_curEncConfigItem->attributeUi());
    w=d->m_curEncConfigItem->attributeUi();
    d->m_encConfigManage->setCurAttributeWidget(w);
    if(w!=NULL)
      w->show();
    qDebug()<<"ui->vlayout_encConfigUi->addWidget(d->m_curEncConfigItem->attributeUi()); ";
  }
}
void GraphEncoder129::showEncoderError(quint16 lost,quint16 encinfo)
{
  Q_D(GraphEncoder129);
  if(d->m_curEncConfigItem!=NULL)
  {
    QStringList errList;
    if(d->m_curEncConfigItem->hasLostError(lost))
    {
      qDebug()<<"hasLostError";
      errList<<tr("Enc Lost");
    }
    else
    {
      if(d->m_curEncConfigItem->hasWarning(encinfo))
      {
        errList=d->m_curEncConfigItem->errorStrings(encinfo);
//        qDebug()<<errList;
      }
    }
    if(!errList.isEmpty())
    {
      ui->listWidget_encErr->clear();
      ui->listWidget_encErr->addItems(errList);
      setEncErrorUiEnable(true);
    }
    else
    {
      setEncErrorUiEnable(false);
    }
  }

}
void GraphEncoder129::initCurEncConfigItem()
{
  Q_D(GraphEncoder129);
  //绑编码器类型QList <->QTreeWidgetItem
  //根据QTreeWidgetItem 更新QList
  //初始化当前encConfigItem
  d->m_iDataBinding->bind(ui->listWidget_encAbsolute,d->m_treeWidget->topLevelItem(FPGA_ABS_CFG_INDEX));//FPGA.prm.ABS_ENC_CFG.all
  d->m_iDataBinding->syncTreeItemToUiData();
  d->m_curEncConfigItem=d->m_encConfigManage->encItem(ui->listWidget_encAbsolute->currentRow());
}
