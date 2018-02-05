#include "optface.h"
#include "ui_optface.h"
#include "iopt_p.h"
//#include "qmlstylehelper.h"
#include "stylewidget.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QFont>
#include <QVBoxLayout>
#include <QLabel>
#include <QLabel>
#include <QStyleOption>
#include <QObject>
#include <QPainter>
#include <QDir>
#include <QFileInfoList>
#include <QDoubleSpinBox>

StyleIconWidget::StyleIconWidget(const QString &iconpath,const QString &title,const QString &css,QWidget *parent):QWidget(parent),
  m_css(css),
  m_pressed(false)
{
  QVBoxLayout *vlayout=new QVBoxLayout(this);
  m_icon=new QLabel(this);
  m_icon->setPixmap(QPixmap(iconpath));
  m_icon->setAlignment(Qt::AlignCenter);
  m_title=new QLabel(this);
  m_title->setText(title);
  m_title->setAlignment(Qt::AlignCenter);
  vlayout->addWidget(m_icon);
  vlayout->addWidget(m_title);
  vlayout->setStretch(0,1);
  vlayout->setStretch(1,0);
  QString s="StyleIconWidget:hover{\
      border: 2px solid red;\
      border-radius:5px;\
    }";
  setStyleSheet(s);
}
StyleIconWidget::~StyleIconWidget()
{

}
void StyleIconWidget::setIcon(const QString &iconpath )
{
  m_icon->setPixmap(QPixmap(iconpath));
}
void StyleIconWidget::setIconTitle(const QString &title)
{
  m_title->setText(title);
}

void StyleIconWidget::mouseReleaseEvent(QMouseEvent *)
{
  emit cssChanged(m_css);
  qDebug()<<"emit css changed"<<m_css;
  m_pressed=true;
  update();
}

void StyleIconWidget::paintEvent(QPaintEvent *event)
{
  QStyleOption opt;
  opt.init(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
  if(m_pressed)
  {
    QRect rect;
    rect=this->rect();
    p.fillRect(rect,Qt::gray);
    m_pressed=false;
  }
  QWidget::paintEvent(event);
}


class OptFacePrivate:public IOptPrivate
{
  Q_DECLARE_PUBLIC(OptFace)
public:
  OptFacePrivate();
  ~OptFacePrivate();
  QString m_css;//立即生效的参数，所以不用点应用也保存了
  quint8 m_fontSize;//立即生效的参数，所以不用点应用也保存了
  QString m_lang;
//  QmlStyleHelper *m_qmlHelper;
  StyleWidget m_customStyle;
  QStringList m_editTextStyleSheetList;

};
OptFacePrivate::OptFacePrivate()
{

}
OptFacePrivate::~OptFacePrivate()
{

}

OptFace::OptFace(const QString &optName, QWidget *parent) :  IOpt(optName,*new OptFacePrivate,parent),
  ui(new Ui::OptFace)
{
  Q_D(OptFace);
  ui->setupUi(this);
  readOpt();

//  d->m_qmlHelper=new QmlStyleHelper(d->m_fontSize,d->m_lang,d->m_css,this);

  ui->comboBox->addItem("12",12);
  ui->comboBox->addItem("14",14);
  ui->comboBox->addItem("16",16);
  ui->comboBox->addItem("18",18);
  ui->comboBox->addItem("20",20);
  ui->comboBox->addItem("22",22);
  ui->comboBox->addItem("24",24);
  ui->comboBox->addItem("26",26);
  ui->comboBox->addItem("28",28);
  ui->comboBox->addItem("30",30);
  ui->comboBox->addItem("34",34);
  ui->comboBox->addItem("38",38);
  ui->comboBox->addItem("40",40);

  //初始化样式列表
  QString fileName=d->m_optPath+"style/style.ini";
  QString iconWidgetPath=d->m_optPath+"style/common/gridview/";

  QFile file(fileName);
  if(file.open(QFile::ReadOnly))
  {
    QTextStream in(&file);
    QStringList cssList;
    QString s;
    while (!in.atEnd()) {
      s=in.readLine();
      qDebug()<<s;
      cssList.append(s);
    }
    cssList.removeAll("");
    file.close();

    qDebug()<<"after remove null"<<cssList;
    int count=cssList.count();
    int row = count/2;
    int column=2;
    int cssIndex=0;
    for(int i=0;i<row;i++)
    {
      for(int j=0;j<column;j++)
      {
        QString css=cssList.at(cssIndex);
        StyleIconWidget *siconWidget=new StyleIconWidget(iconWidgetPath+css+".png",css,css,this);
        ui->gridLayout->addWidget(siconWidget,i,j);
        connect(siconWidget,SIGNAL(cssChanged(QString)),this,SLOT(onStyleChanged(QString)));
        cssIndex++;
      }
    }
    if(count!=row*2)
    {
      QString css=cssList.at(cssIndex);
      StyleIconWidget *siconWidget=new StyleIconWidget(iconWidgetPath+css+".png",css,css,this);
      ui->gridLayout->addWidget(siconWidget,row,0);
      connect(siconWidget,SIGNAL(cssChanged(QString)),this,SLOT(onStyleChanged(QString)));
    }
  }

  uiInit();

//  updateEditTextStyleSheetList();

  connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(onCurrentIndexChanged(int)));
  connect(ui->rbtn_ch,SIGNAL(clicked(bool)),this,SLOT(onRadioButtonClicked(bool)));
  connect(ui->rbtn_en,SIGNAL(clicked(bool)),this,SLOT(onRadioButtonClicked(bool)));

}
OptFace::~OptFace()
{
  delete ui;
}
void OptFace::uiInit()
{
  Q_D(OptFace);

  if(d->m_lang=="english")
    ui->rbtn_en->setChecked(true);
  else
    ui->rbtn_ch->setChecked(true);

  for(int i=0;i<ui->comboBox->count();i++)
  {
    if(ui->comboBox->itemData(i)==d->m_fontSize)
    {
      ui->comboBox->setCurrentIndex(i);
      break;
    }
  }
}

bool OptFace::optActive()
{
  //这里面的动作都是立即生效的，所以Ui操作之后就执行了
  Q_D(OptFace);
  if(ui->rbtn_ch->isChecked())
  {
    d->m_lang="chinese";
//    d->m_qmlHelper->setLanguage("chinese");
  }
  else
  {
    d->m_lang="english";
//    d->m_qmlHelper->setLanguage("english");
  }

  setFaceFontSize(ui->comboBox->currentData().toInt());
  setFaceStyle(d->m_css);

  qDebug()<<"opt face execute active ";

  return true;
}
bool OptFace::readOpt()
{
  Q_D(OptFace);
  d->m_css=data("face","css","gray").toString();
  d->m_fontSize=data("face","fontsize",12).toInt();
  d->m_lang=data("face","language","chinese").toString();
  qDebug()<<d->m_name<<"read opt";
  return true;
}
bool OptFace::writeOpt()
{
  Q_D(OptFace);
  saveData("face","css",d->m_css);
  saveData("face","fontsize",d->m_fontSize);
  saveData("face","language",d->m_lang);
  return true;
}
void OptFace::respondErrorExecute()
{

}

void OptFace::setFaceStyle(const QString &css)
{
  Q_D(OptFace);
  d->m_css=css;

  QString filename=d->m_optPath+"style/"+css+"/"+css+".css";

  qDebug()<<"TEST_OUT CSS filePath "<<filename;
  QFile file(filename);
  if(file.open(QFile::ReadOnly))
  {
    QTextStream in(&file);

    QString qss = in.readAll();
    qApp->setStyleSheet(qss);

    updateEditTextStyleSheetList();

    file.close();


    //    d->m_qmlHelper->setCss(css);
    //    d->m_qmlHelper->setFontSize(d->m_fontSize);
  }
  else
    qDebug()<<"open file :"<<filename<<"error";
  emit faceCssChanged(css);
}

void OptFace::setFaceFontSize(int size)
{
  Q_D(OptFace);
  d->m_fontSize=size;
  QFont font=qApp->font();
  font.setPixelSize(size);
  qApp->setFont(font);
}

int OptFace::fontSize() const
{
  Q_D(const OptFace);
  return d->m_fontSize;
}

QString OptFace::css() const
{
  Q_D(const OptFace);
  return d->m_css;
}

QString OptFace::language() const
{
  Q_D(const OptFace);
  return d->m_lang;
}

StyleWidget *OptFace::customStyleWidget()
{
  Q_D(OptFace);
  return &d->m_customStyle;
}

void OptFace::setEditTextStatus(QDoubleSpinBox *box,EditTextStatus sta)
{
  Q_D(OptFace);
  int index=(int)sta;
  if(index<d->m_editTextStyleSheetList.count())
  {
    box->setStyleSheet(d->m_editTextStyleSheetList.at(index));
    qDebug()<<"box->setStyleSheet"<<d->m_editTextStyleSheetList.at(index);
  }
}

//QmlStyleHelper *OptFace::qmlStyleHelper() const
//{
//  Q_D(const OptFace);
//  return d->m_qmlHelper;
//}

void OptFace::onRadioButtonClicked(bool checked)
{
  Q_UNUSED(checked);
  setModify(true);
  qDebug()<<"rbtn clicked";
}
void OptFace::onCurrentIndexChanged(int index)
{
  qDebug()<<"current index changed "<<index;
  setModify(true);
}
void OptFace::onStyleChanged(QString css)
{
  setFaceFontSize(ui->comboBox->currentData().toInt());
  setFaceStyle(css);
}
void OptFace::updateEditTextStyleSheetList()
{
  Q_D(OptFace);
  d->m_editTextStyleSheetList.clear();
  int r,g,b,br,bg,bb;
  //Default
  FILL_RGB(d->m_customStyle.dsBoxTextDefColor(),r,g,b);
  FILL_RGB(d->m_customStyle.dsBoxBackgroundDefColor(),br,bg,bb);
  QString str=QString("QDoubleSpinBox{color:rgb(%1,%2,%3);background-color:rgb(%4,%5,%6);}").arg(r).arg(g).arg(b).arg(br).arg(bg).arg(bb);
  d->m_editTextStyleSheetList.append(str);
  qDebug()<<"====================\ndefault style"<<str;

  //Ready
  FILL_RGB(d->m_customStyle.dsBoxTextDefColor(),r,g,b);
  FILL_RGB(d->m_customStyle.dsBoxBackgroundReadyColor(),br,bg,bb);
  str=QString("QDoubleSpinBox{color:rgb(%1,%2,%3);background-color:rgb(%4,%5,%6);}").arg(r).arg(g).arg(b).arg(br).arg(bg).arg(bb);
  d->m_editTextStyleSheetList.append(str);
  qDebug()<<"ready style"<<str;

  //Editting
  FILL_RGB(d->m_customStyle.dsBoxTextEditColor(),r,g,b);
  FILL_RGB(d->m_customStyle.dsBoxBackgroundDefColor(),br,bg,bb);
  str=QString("QDoubleSpinBox{color:rgb(%1,%2,%3);background-color:rgb(%4,%5,%6);}").arg(r).arg(g).arg(b).arg(br).arg(bg).arg(bb);
  d->m_editTextStyleSheetList.append(str);
  qDebug()<<"editting style"<<str;

  //Error
  FILL_RGB(d->m_customStyle.dsBoxTextDefColor(),r,g,b);
  FILL_RGB(d->m_customStyle.dsBoxBackgroundErrorColor(),br,bg,bb);
  str=QString("QDoubleSpinBox{color:rgb(%1,%2,%3);background-color:rgb(%4,%5,%6);}").arg(r).arg(g).arg(b).arg(br).arg(bg).arg(bb);
  d->m_editTextStyleSheetList.append(str);
  qDebug()<<"error style"<<str<<"\n=========================\n";
}
