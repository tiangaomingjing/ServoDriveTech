﻿#include "graphencoder129.h"
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

class GraphEncoder129Private:public IGraphEncoderPrivate
{
  Q_DECLARE_PUBLIC(GraphEncoder129)
public:
  GraphEncoder129Private():m_curEncConfigItem(NULL),m_iDataBinding(NULL){}
  ~GraphEncoder129Private(){}
protected:
  IEncConfigItem *m_curEncConfigItem;
  EncConfigManage m_encConfigManage;
  IDataBinding *m_iDataBinding;
};

GraphEncoder129::GraphEncoder129(QWidget *parent) :
  IGraphEncoder(*(new GraphEncoder129Private),parent),
  ui(new Ui::GraphEncoder129)
{
  ui->setupUi(this);
  initDial(ui->Dial_encElectronic);
  initDial(ui->Dial_encMachine);

  setEncErrorUiEnable(false);

  setEncConfigUiEnable(false);
  ui->btn_encConfig->setCheckable(true);
  ui->spinBox_encLine->setVisible(true);
  ui->comboBox_encBitNum->setVisible(false);
  QStringList comList;
  comList<<"11"<<"13"<<"17"<<"20"<<"21"<<"22"<<"23";
  ui->comboBox_encBitNum->addItems(comList);
  ui->label_encLineNum->setText(tr("encoder lineNumber:"));

  //-------------------初始化编码器设置框--------------------
  ui->toolBox_encConfig->setItemText(0,tr("Enc Absolute"));
  ui->toolBox_encConfig->setItemText(1,tr("Enc Increase"));
  ui->toolBox_encConfig->setItemText(2,tr("Enc Resolution"));
//  QStringList list;
//  list<<tr("0 DuoMoChuan")<<tr("1 NiKang")<<tr("2 Haidehan")<<tr("3 SanXie")<<tr("4 XiongXia")<<tr("5 AnChuan");
//  ui->listWidget_encAbsolute->addItems(list);

  connect(ui->btn_encConfig,SIGNAL(clicked(bool)),this,SLOT(onBtnEncConfigClicked(bool)));
  connect(ui->btn_encSaveConfig,SIGNAL(clicked(bool)),this,SLOT(onBtnEncConfigSaveClicked()));

  connect(ui->rbtn_encBit,SIGNAL(toggled(bool)),this,SLOT(onRadioBtnClicked()));
  connect(ui->rbtn_encLine,SIGNAL(toggled(bool)),this,SLOT(onRadioBtnClicked()));
  connect(ui->btn_encSearch,SIGNAL(clicked(bool)),this,SLOT(onBtnSearchPhaseClicked()));
}

GraphEncoder129::~GraphEncoder129()
{
  Q_D(GraphEncoder129);
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

}
void GraphEncoder129::setUiVersionName()
{
  Q_D(GraphEncoder129);
  d->m_versionName="V129";
}
void GraphEncoder129::syncTreeDataToUiFace()
{

}

//!
//! \brief GraphEncoder129::onBtnEncConfigClicked 打开编码器设置对话框
//! \param checked
//!
void GraphEncoder129::onBtnEncConfigClicked(bool checked)
{
  setEncConfigUiEnable(checked);
  Q_D(GraphEncoder129);
  if(checked)
  {
    IEncConfigItem *encItem=new EncConfigDuoMoItem;
    d->m_encConfigManage.addEncConfigItem(encItem);
    encItem=new EncConfigHaidehanItem;
    d->m_encConfigManage.addEncConfigItem(encItem);
    encItem=new EncConfigNiKangItem;
    d->m_encConfigManage.addEncConfigItem(encItem);
    encItem=new EncConfigSanXieItem;
    d->m_encConfigManage.addEncConfigItem(encItem);
    encItem=new EncConfigSongXiaItem;
    d->m_encConfigManage.addEncConfigItem(encItem);
    encItem=new EncConfigYaskawaItem;
    d->m_encConfigManage.addEncConfigItem(encItem);
    if(ui->listWidget_encAbsolute->count()==0)
      ui->listWidget_encAbsolute->addItems(d->m_encConfigManage.itemNames());
    syncTreeDataToUiFace();
    qDebug()<<"open encItemcount"<<d->m_encConfigManage.itemNames().count();

  }
  else
  {
    d->m_curEncConfigItem=NULL;
    d->m_encConfigManage.clearAllEncConfigItem();
    qDebug()<<"close encItemcount"<<d->m_encConfigManage.itemNames().count();
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
void GraphEncoder129::onBtnEncConfigSaveClicked()
{
  Q_D(GraphEncoder129);
  quint8 inx=ui->listWidget_encAbsolute->currentRow();

  d->m_curEncConfigItem=d->m_encConfigManage.encConfigItem(inx);
  if(d->m_curEncConfigItem!=NULL)
  {
    if(ui->rbtn_encBit->isChecked())
    {
      quint32 lineNum=ui->comboBox_encBitNum->currentText().toUInt();
      d->m_curEncConfigItem->setLineNumber(qPow(2,lineNum));
      qDebug()<<"lineNumer"<<d->m_curEncConfigItem->lineNumber();
    }
    else
      d->m_curEncConfigItem->setLineNumber(ui->spinBox_encLine->value());

    qDebug()<<"ssssssssssssssssssssssss";
    d->m_iDataBinding->multiBind(static_cast<QObject*>(d->m_curEncConfigItem),d->m_treeWidget);
    qDebug()<<"ssssssssssssssssssssssss";
    d->m_iDataBinding->syncMultiUiDataToTree();
  }
//  syncUiDataToTree();
//  uiSaveFunction();

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
