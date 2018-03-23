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

CombinedWindow::CombinedWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CombinedWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
    m_isMax = false;
    m_mousePressed = false;
    m_location = this->geometry();
    ui->widget_frameWidget->installEventFilter(this);

    connect(ui->btn_Close, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->btn_Max, SIGNAL(clicked()), this, SLOT(onActionMaxClicked()));
    connect(ui->btn_Min, SIGNAL(clicked()), this, SLOT(onActionMinClicked()));
    setWidgetIcon();
    OptFace *optface=dynamic_cast<OptFace *>(OptContainer::instance()->optItem("optface"));
    if(optface!=NULL)
      connect(optface,SIGNAL(faceCssChanged(QString)),this,SLOT(onOptFaceCssChanged(QString)));
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
    if (m_isMax) {
        this->setGeometry(m_location);
        ui->btn_Max->setIcon(QIcon(iconPath + ICON_TOPWIDGET_MAX));
    } else {
        m_location = this->geometry();
        this->setGeometry(qApp->desktop()->availableGeometry());
        ui->btn_Max->setIcon(QIcon(iconPath + ICON_TOPWIDGET_RESTORE));
    }
    m_isMax = !m_isMax;
}

void CombinedWindow::closeEvent(QCloseEvent *event) {
    int ret = QMessageBox::question(this, tr("Close"), tr("Do you want to close the application?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if (ret == QMessageBox::Yes) {
        m_bottomWindow->setParent(0);
        m_bottomWindow->close();
        event->accept();
    } else {
        event->ignore();
    }
}

void CombinedWindow::showMaximized()
{
  m_isMax=true;
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
}
