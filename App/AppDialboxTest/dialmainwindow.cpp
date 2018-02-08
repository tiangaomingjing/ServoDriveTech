#include "dialmainwindow.h"
#include "ui_dialmainwindow.h"

#include "qwt_dial_needle.h"

#include <QTimer>
#include <QTime>
#include <QPropertyAnimation>

DialMainWindow::DialMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::DialMainWindow)
{
  ui->setupUi(this);
  initDial(ui->Dial_electronic);
  initDial(ui->Dial_machine);
  m_timerTest=new QTimer;
  m_timerTest->setInterval(50);
  connect(m_timerTest,SIGNAL(timeout()),this,SLOT(onTimeOut()));
  ui->Dial_electronic->setTitle(tr("Electronic"));
  ui->Dial_machine->setTitle(tr("Machine"));
  ui->widget_enc->hide();
  ui->pushButton_showENC->setCheckable(true);
}

DialMainWindow::~DialMainWindow()
{
  delete ui;
}
void DialMainWindow::initDial(QwtDial *dial)
{
  QFontMetrics fm(qApp->font());
  QFont font;
  font.setPixelSize(fm.height()*1.6);
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


void DialMainWindow::on_pushButton_2_clicked()
{
    QFont font;
    font.setPixelSize(ui->horizontalSlider->value());
    qApp->setFont(font);
}

void DialMainWindow::on_pushButton_clicked()
{
  m_timerTest->start();
}
void DialMainWindow::onTimeOut()
{
  static int count;
  ui->Dial_electronic->setValue(count);
  ui->Dial_machine->setValue(count);
  count+=10;
  if(count>360)
    count=0;
}

void DialMainWindow::on_pushButton_showENC_clicked()
{
  if(ui->pushButton_showENC->isChecked())
  {
    ui->widget_enc->show();
//    ui->listWidget->hide();
//    ui->pushButton_3->hide();
  }
  else
  {
    ui->widget_enc->hide();
//    ui->listWidget->show();
//    ui->pushButton_3->show();
  }
//  QPropertyAnimation *ani=new QPropertyAnimation(ui->widget_enc,"width");
//  ani->setStartValue(0);
//  ani->setEndValue(ui->widget_enc->width());
//  ani->setDuration(1000);
//  ani->start();
}
