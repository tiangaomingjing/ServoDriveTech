#include "graphencoder129.h"
#include "ui_graphencoder129.h"
#include "igraphencoder_p.h"

#include "qwt_dial_needle.h"

class GraphEncoder129Private:public IGraphEncoderPrivate
{
  Q_DECLARE_PUBLIC(GraphEncoder129)
public:
  GraphEncoder129Private(){}
  ~GraphEncoder129Private(){}
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
  ui->label_encLineNum->setText(tr("encoder lineNumber:"));

  ui->toolBox_encConfig->setItemText(0,tr("Enc Absolute"));
  ui->toolBox_encConfig->setItemText(1,tr("Enc Increase"));
  ui->toolBox_encConfig->setItemText(2,tr("Enc Resolution"));

  connect(ui->btn_encConfig,SIGNAL(clicked(bool)),this,SLOT(onBtnEncConfigClicked(bool)));
  connect(ui->rbtn_encBit,SIGNAL(toggled(bool)),this,SLOT(onRadioBtnClicked()));
  connect(ui->rbtn_encLine,SIGNAL(toggled(bool)),this,SLOT(onRadioBtnClicked()));
  connect(ui->btn_encSearch,SIGNAL(clicked(bool)),this,SLOT(onBtnSearchPhaseClicked()));
}

GraphEncoder129::~GraphEncoder129()
{
  delete ui;
}
void GraphEncoder129::visitActive(IUiWidget *uiWidget)
{

}
void GraphEncoder129::setUiVersionName()
{
  Q_D(GraphEncoder129);
  d->m_versionName="V129";
}
void GraphEncoder129::onBtnEncConfigClicked(bool checked)
{
  setEncConfigUiEnable(checked);
}
void GraphEncoder129::onRadioBtnClicked()
{
  if(ui->rbtn_encLine->isChecked())
  {
    ui->spinBox_encLine->setVisible(true);
    ui->comboBox_encBitNum->setVisible(false);
    ui->label_encLineNum->setText(tr("encoder lineNumber:"));
  }
  else
  {
    ui->spinBox_encLine->setVisible(false);
    ui->comboBox_encBitNum->setVisible(true);
    ui->label_encLineNum->setText(tr("encoder bitNumber:"));
  }
}
void GraphEncoder129::onBtnSearchPhaseClicked()
{
  static bool en=false;
  setEncErrorUiEnable(en);
  en=!en;
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
