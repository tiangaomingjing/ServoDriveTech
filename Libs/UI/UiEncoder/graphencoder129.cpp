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
#include <QTimer>

#define KEY_NAME_POS          "gSevDrv.sev_obj.cur.rsv.pos"
#define KEY_NAME_POS_IN       "gSevDrv.sev_obj.cur.rsv.pos_in"
#define KEY_NAME_POS_OFFSET   "gSevDrv.sev_obj.cur.rsv.prm.pos_ofst_3"
#define KEY_NAME_PPN          "gSevDrv.sev_obj.cur.mot.PPN_1"
#define KEY_NAME_SEQ_DIR      "gSevDrv.sev_obj.cur.rsv.prm.seq_dir"
#define KEY_NAME_ENC_INFO     "gSevDrv.sev_obj.cur.pro.enc_info.all"
#define KEY_NAME_LOST         "gSevDrv.sev_obj.cur.rsv.prm.abs_type.all"

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

  //-------------------初始化编码器配置设置框--------------------
  ui->toolBox_encConfig->setItemText(0,tr("Enc None"));
  ui->toolBox_encConfig->setItemText(1,tr("Enc Absolute"));
  ui->toolBox_encConfig->setItemText(2,tr("Enc Increase"));
  ui->toolBox_encConfig->setItemText(3,tr("Enc Resolution"));
  Q_D(GraphEncoder129);
  d->m_encConfigManage=new EncConfigManage;
//  QStringList list;
//  list<<tr("0 DuoMoChuan")<<tr("1 NiKang")<<tr("2 Haidehan")<<tr("3 SanXie")<<tr("4 XiongXia")<<tr("5 AnChuan");
//  ui->listWidget_encAbsolute->addItems(list);

  connect(ui->btn_encConfig,SIGNAL(clicked(bool)),this,SLOT(onBtnEncConfigClicked(bool)));
  connect(ui->btn_encSaveConfig,SIGNAL(clicked(bool)),this,SLOT(onBtnEncConfigSaveClicked()));
  connect(ui->listWidget_encAbsolute,SIGNAL(currentRowChanged(int)),this,SLOT(onEncConfigListWidgetRowChanged(int)));

  connect(ui->rbtn_encBit,SIGNAL(toggled(bool)),this,SLOT(onRadioBtnClicked()));
  connect(ui->rbtn_encLine,SIGNAL(toggled(bool)),this,SLOT(onRadioBtnClicked()));
  connect(ui->btn_encSearch,SIGNAL(clicked(bool)),this,SLOT(onBtnSearchPhaseClicked()));
}

GraphEncoder129::~GraphEncoder129()
{
  Q_D(GraphEncoder129);
  GT::deletePtrObject(d->m_encConfigManage);
  delete ui;
}
void GraphEncoder129::visitActive(IUiWidget *uiWidget)
{
  Q_D(GraphEncoder129);
  d->m_iDataBinding=new EncConfigBinding129(this);
  qDebug()<<"d->m_iDataBinding=new EncConfigBinding129(this);";

  d->m_dev=uiWidget->device();
  int axis=uiWidget->uiIndexs().axisInx;
  int page=uiWidget->uiIndexs().pageInx;
  d->m_treeWidget=d->m_dev->axisTreeSource(axis,page);

  d->m_uiWidget=uiWidget;

}
void GraphEncoder129::setUiVersionName()
{
  Q_D(GraphEncoder129);
  d->m_versionName="V129";
}
void GraphEncoder129::syncTreeDataToUiFace()
{
  Q_D(GraphEncoder129);
  qDebug()<<"TEST_OUT syncMultiTreeToUiData";
  d->m_iDataBinding->syncMultiTreeToUiData();//just sync tree data to encconfigdata
}
void GraphEncoder129::onUpdateTimeOut()
{
  Q_D(GraphEncoder129);

//  static int count=0;
//  static int statusCount=0;
//  ui->Dial_encElectronic->setValue(count);
//  ui->Dial_encMachine->setValue(count);
//  switch (statusCount) {
//  case 0:
//    count+=10;
//    if(count>360)
//      statusCount=1;
//    break;
//  case 1:
//    count-=10;
//    if(count<0)
//      statusCount=0;
//    break;
//  default:
//    break;
//  }

   quint32 pos;
   quint32 posIn;
   quint32 posOfst;
   quint16 ppn;
   qint16 seqDir;
   quint16 encInfo;
   quint16 absType;
   pos=readPos(KEY_NAME_POS);
   qDebug()<<"pos"<<pos;
   posIn=readPosInput(KEY_NAME_POS_IN);
   qDebug()<<"posIn"<<posIn;
   posOfst=readPosOffset(KEY_NAME_POS_OFFSET);
   qDebug()<<"posOfst"<<posOfst;
   ppn=readPPN(KEY_NAME_PPN);
   qDebug()<<"ppn"<<ppn;
   seqDir=readSeqDir(KEY_NAME_SEQ_DIR);
   qDebug()<<"seqDir"<<seqDir;
   encInfo=readEncInfo(KEY_NAME_ENC_INFO);
   qDebug()<<"encInfo"<<encInfo;
   absType=readErrLost(KEY_NAME_LOST);
   qDebug()<<"absType"<<absType;

  qDebug()<<"encoder axisSize:"<<d->m_dev->axisNum()<<"current axis"<<d->m_uiWidget->uiIndexs().axisInx<<"update ...";
//  var strPos=m_cmd.readCommand("gSevDrv.sev_obj.cur.rsv.pos");
//  pos.text=parseInt(strPos);


//  var strPosIn=m_cmd.readCommand("gSevDrv.sev_obj.cur.rsv.pos_in");
//  posIn.text=parseInt(strPosIn);
//  var precision=parseInt(m_cmd.readCommand("gSevDrv.sev_obj.cur.rsv.prm.line_num_3"));
//  if(strPosIn!=="NULL")
//      gauge.value=360*parseInt(strPosIn)/precision;


//  var strPos_ofst=m_cmd.readCommand("gSevDrv.sev_obj.cur.rsv.prm.pos_ofst_3");
//  posOffset.text=parseInt(strPos_ofst);


//  var strPPN=m_cmd.readCommand("gSevDrv.sev_obj.cur.mot.PPN_1");
//  if(strPPN!=="NULL"){
//      var PPN=parseInt(strPPN);
//      var angleEle=(gauge.value*PPN)%360;
//      gauge_Electric.value=parseInt(angleEle);
//  }

//  //读相序
//  var strPseq=m_cmd.readCommand("gSevDrv.sev_obj.cur.rsv.prm.seq_dir");
//  var pSeqNum=parseInt(strPseq);
//  pseq.text=pSeqNum;

//  //读取编码器报警信息
//  var errorCodeStr=m_cmd.readCommand("gSevDrv.sev_obj.cur.pro.enc_info.all");
////            console.log("errorCodeStr="+errorCodeStr);
//  var lostenc=m_cmd.readCommand("gSevDrv.sev_obj.cur.rsv.prm.abs_type.all");

}

//!
//! \brief GraphEncoder129::onBtnEncConfigClicked 打开编码器设置对话框 open close 两个状态
//! \param checked
//!
void GraphEncoder129::onBtnEncConfigClicked(bool checked)
{
  setEncConfigUiEnable(checked);
  Q_D(GraphEncoder129);
  if(checked)
  {
    //初始化的顺序不能错
    IEncConfigItem *encItem=new EncConfigDuoMoItem;
    encItem->createAttributeUi();
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

    if(ui->listWidget_encAbsolute->count()==0)
      ui->listWidget_encAbsolute->addItems(d->m_encConfigManage->itemNames());

    ui->rbtn_encLine->setChecked(true);

    //获取当前文件中的编码器配置信息
    d->m_iDataBinding->bind(ui->listWidget_encAbsolute,d->m_treeWidget->topLevelItem(3));//FPGA.prm.ABS_ENC_CFG.all
    d->m_iDataBinding->syncTreeItemToUiData();
    d->m_curEncConfigItem=d->m_encConfigManage->encItem(ui->listWidget_encAbsolute->currentRow());
    d->m_encConfigManage->setCurAttributeWidget(d->m_curEncConfigItem->attributeUi());
    d->m_iDataBinding->multiBind(static_cast<QObject*>(d->m_curEncConfigItem),d->m_treeWidget);

    syncTreeDataToUiFace();
    updateEncConfigUiByCurrentConfigItem();

    qDebug()<<"open encItemcount"<<d->m_encConfigManage->itemNames().count();

  }
  else
  {
    d->m_curEncConfigItem=NULL;
    d->m_encConfigManage->clearAllEncItem();
    qDebug()<<"close encItemcount"<<d->m_encConfigManage->itemNames().count();
  }
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
  static bool en=false;
  setEncErrorUiEnable(en);
  en=!en;
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

  //const QColor base( QColor( "DimGray" ) );
  const QColor base( QColor( Qt::darkGray ).dark( 110 ) );
//  const QColor base( QColor( Qt::blue ).dark( 100 ) );

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
    d->m_curEncConfigItem->attributeUiUpdate();
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
