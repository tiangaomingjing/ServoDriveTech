#include "combinedwindow.h"
#include "gtutils.h"
#include "Option"
#include "appiconname.h"
#include "ui_combinedwindow.h"
#include <QVBoxLayout>
#include <QWidget>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QMessageBox>
#include <QCloseEvent>
#include <QDebug>
#include <QPainter>
#include <QDesktopWidget>
#include <QSize>
#include <QSizeGrip>

CombinedWindow::CombinedWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CombinedWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
    m_isMax = false;
    m_mousePressed = false;
    m_desktop = QApplication::desktop();
    m_size = this->size();
    ui->widget_frameWidget->installEventFilter(this);
//    m_sizeGrip = new QSizeGrip(this);
//    m_sizeGrip->setFixedSize(m_sizeGrip->sizeHint());

    connect(ui->btn_Close, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->btn_Max, SIGNAL(clicked()), this, SLOT(onActionMaxClicked()));
    connect(ui->btn_Min, SIGNAL(clicked()), this, SLOT(onActionMinClicked()));
    setWidgetIcon();
    OptFace *optface=dynamic_cast<OptFace *>(OptContainer::instance()->optItem("optface"));
    if(optface!=NULL)
      connect(optface,SIGNAL(faceCssChanged(QString)),this,SLOT(onOptFaceCssChanged(QString)));

    ui->btn_icon->setIconSize(QSize(30,30));
    ui->btn_icon->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->btn_icon->setText(tr("GOOGOLTECH"));
    ui->horizontalLayout_3->setSpacing(30);
    ui->label_combinedInfo->setText("");
    ui->label_title->setText(tr("SDT"));
    ui->label_combinedInfo->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
}

CombinedWindow::~CombinedWindow()
{
    delete ui;
}

void CombinedWindow::insertWindow(QMainWindow *w) {
    m_bottomWindow = w;
    ui->verticalLayout_2->addWidget(m_bottomWindow);
}

void CombinedWindow::onActionMaxClicked() {
    OptFace *face = dynamic_cast<OptFace *>(OptContainer::instance()->optItem("optface"));
    QString iconPath = GTUtils::customPath()+"/option/style/"+face->css()+"/icon/";
    qDebug()<<m_isMax;
    if (m_isMax) {
//        this->resize(m_size);
        ui->btn_Max->setIcon(QIcon(iconPath + ICON_TOPWIDGET_MAX));
//        int current_screen = m_desktop->screenNumber(this);
//        qDebug()<<"restore screen"<<current_screen;
//        int x = (m_desktop->screen(current_screen)->width() - m_size.width()) / 2;
//        int y = (m_desktop->screen(current_screen)->height() - m_size.height()) / 2;
//        for (int i = 0; i < current_screen; i++) {
//            x = x + m_desktop->screen(i)->width();
//        }
//        this->move(x, y);
//        m_sizeGrip->show();
        QMainWindow::showNormal();
    } else {
//        m_size = this->size();
//        int current_screen = m_desktop->screenNumber(this);
//        qDebug()<<"max screen"<<current_screen;
//        this->setGeometry(m_desktop->availableGeometry(current_screen));
//        m_sizeGrip->hide();
        ui->btn_Max->setIcon(QIcon(iconPath + ICON_TOPWIDGET_RESTORE));
        QMainWindow::showMaximized();
    }
    m_isMax = !m_isMax;
}

void CombinedWindow::closeEvent(QCloseEvent *event) {
    int ret = QMessageBox::question(this, tr("Close"), tr("Do you want to close the application?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if (ret == QMessageBox::Yes) {
        this->hide();
        m_bottomWindow->setParent(0);
        m_bottomWindow->close();
        event->accept();
    } else {
        event->ignore();
    }
}

void CombinedWindow::showMaximized()
{
  m_isMax = true;
  QMainWindow::showMaximized();
}

//void CombinedWindow::paintEvent(QPaintEvent *event)
//{
//    QPainter painter(this);
//        painter.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
//        painter.setBrush(QBrush(Qt::red));
//        painter.setPen(Qt::transparent);
//        QRect rect = this->rect();
//        rect.setWidth(rect.width() - 1);
//        rect.setHeight(rect.height() - 1);
//        painter.drawRoundedRect(rect, 15, 15);
//}

void CombinedWindow::onActionMinClicked() {
    this->showMinimized();
}

bool CombinedWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonDblClick) {
        onActionMaxClicked();
        return true;
    }
    return QObject::eventFilter(obj, event);
}

void CombinedWindow::mouseMoveEvent(QMouseEvent *e)
{
    if (m_mousePressed && (e->buttons() && Qt::LeftButton) && !m_isMax) {
        this->move(e->globalPos() - m_mousePoint);
        e->accept();
    }
}

void CombinedWindow::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        m_mousePressed = true;
        m_mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void CombinedWindow::mouseReleaseEvent(QMouseEvent *)
{
    m_mousePressed = false;
}

void CombinedWindow::onOptFaceCssChanged(const QString &css)
{
  setWidgetIcon();
  qDebug()<<"setWidgetIcon"<<css;
}

void CombinedWindow::onTitleChanged(const QString &title)
{
  ui->label_combinedInfo->setText(title);
}

void CombinedWindow::setWidgetIcon() {
    OptFace *face = dynamic_cast<OptFace *>(OptContainer::instance()->optItem("optface"));
    QString iconPath = GTUtils::customPath()+"/option/style/"+face->css()+"/icon/";
    ui->btn_Close->setIcon(QIcon(iconPath + ICON_TOPWIDGET_CLOSE));
    ui->btn_Min->setIcon(QIcon(iconPath + ICON_TOPWIDGET_MIN));
    if (m_isMax) {
        ui->btn_Max->setIcon(QIcon(iconPath + ICON_TOPWIDGET_MAX));
    } else {
        ui->btn_Max->setIcon(QIcon(iconPath + ICON_TOPWIDGET_RESTORE));
    }

    ui->btn_icon->setIcon(QIcon(iconPath + ICON_GOOGOL));
}
