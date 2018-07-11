#include "uimotionposition.h"
#include "ui_uimotionposition.h"
#include "motionposition.h"
#include "sevdevice.h"
#include "Option"
#include "gtutils.h"

#include <QListWidget>
#include <QKeyEvent>
#include <QDebug>

#define PIC_NAME_VPOINT          "plot_vPoint.png"
#define PIC_NAME_VRECI           "plot_vReci.png"

UiMotionPosition::UiMotionPosition(MotionPosition *mp, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UiMotionPosition),
    q_ptr(mp)
    //m_timer(new QTimer(this))
{
    ui->setupUi(this);
    ui->stackedWidget_Point->setCurrentIndex(0);
    m_axisCount = mp->sevDevice()->axisNum();

    ui->comboBox_pointAcc->addItem("deg/ms^2");
    ui->comboBox_pointDec->addItem("deg/ms^2");
    ui->comboBox_pointMaxVel->addItem("rpm");
    ui->comboBox_pointPulse->addItem("rounds");

    ui->comboBox_reciAcc->addItem("deg/ms^2");
    ui->comboBox_reciDec->addItem("deg/ms^2");
    ui->comboBox_reciMaxVel->addItem("rpm");
    ui->comboBox_reciPulse->addItem("rounds");
    ui->comboBox_reciInterval->addItem("ms");
    //ui->comboBox_reciTimes->addItem("");

    for (int i = 0; i < m_axisCount; i++) {
        UiPosMotionData* data = new UiPosMotionData;
        m_uiDataList.append(data);
    }

    ui->doubleSpinBox_PointAcc->setValue(7.14);
    ui->doubleSpinBox_PointDec->setValue(7.14);
    ui->doubleSpinBox_PointMaxVel->setValue(1000);
    ui->doubleSpinBox_PointPulse->setValue(5);

    ui->doubleSpinBox_ReciAcc->setValue(7.14);
    ui->doubleSpinBox_ReciDec->setValue(7.14);
    ui->doubleSpinBox_ReciInterval->setValue(1000);
    ui->doubleSpinBox_ReciMaxVel->setValue(1000);
    ui->doubleSpinBox_ReciPulse->setValue(5);
    ui->spinBox_ReciTimes->setValue(0);

    ui->doubleSpinBox_PointAcc->installEventFilter(this);
    ui->doubleSpinBox_PointDec->installEventFilter(this);
    ui->doubleSpinBox_PointMaxVel->installEventFilter(this);
    ui->doubleSpinBox_PointPulse->installEventFilter(this);

    ui->doubleSpinBox_ReciAcc->installEventFilter(this);
    ui->doubleSpinBox_ReciDec->installEventFilter(this);
    ui->doubleSpinBox_ReciInterval->installEventFilter(this);
    ui->doubleSpinBox_ReciMaxVel->installEventFilter(this);
    ui->doubleSpinBox_ReciPulse->installEventFilter(this);
    ui->spinBox_ReciTimes->installEventFilter(this);

    OptFace *face = dynamic_cast<OptFace *>(OptContainer::instance()->optItem("optface"));
    connect(face, SIGNAL(faceCssChanged(QString)), this, SLOT(onCssChanged(QString)));
    setupIcons(face->css());
    connect(ui->checkBox_PositionMotion, SIGNAL(clicked(bool)), this, SLOT(onCheckBoxReciClicked(bool)));
    connect(ui->doubleSpinBox_PointAcc,SIGNAL(valueChanged(double)),this,SLOT(onDoubleSpinBoxValueChanged(double)));
    connect(ui->doubleSpinBox_PointDec,SIGNAL(valueChanged(double)),this,SLOT(onDoubleSpinBoxValueChanged(double)));
    connect(ui->doubleSpinBox_PointMaxVel,SIGNAL(valueChanged(double)),this,SLOT(onDoubleSpinBoxValueChanged(double)));
    connect(ui->doubleSpinBox_PointPulse,SIGNAL(valueChanged(double)),this,SLOT(onDoubleSpinBoxValueChanged(double)));
    connect(ui->doubleSpinBox_ReciAcc,SIGNAL(valueChanged(double)),this,SLOT(onDoubleSpinBoxValueChanged(double)));
    connect(ui->doubleSpinBox_ReciDec,SIGNAL(valueChanged(double)),this,SLOT(onDoubleSpinBoxValueChanged(double)));
    connect(ui->doubleSpinBox_ReciInterval,SIGNAL(valueChanged(double)),this,SLOT(onDoubleSpinBoxValueChanged(double)));
    connect(ui->doubleSpinBox_ReciMaxVel,SIGNAL(valueChanged(double)),this,SLOT(onDoubleSpinBoxValueChanged(double)));
    connect(ui->doubleSpinBox_ReciPulse,SIGNAL(valueChanged(double)),this,SLOT(onDoubleSpinBoxValueChanged(double)));
    connect(ui->spinBox_ReciTimes,SIGNAL(valueChanged(int)),this,SLOT(onSpinBoxValueChanged(int)));
    //connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimerTimeOut()));
}

UiMotionPosition::~UiMotionPosition()
{
    delete ui;
}

void UiMotionPosition::updataUi(int axisInx)
{
    UiPosMotionData* data = m_uiDataList.at(axisInx);
    if (data->m_isReci) {
        ui->checkBox_PositionMotion->setChecked(true);
        ui->stackedWidget_Point->setCurrentIndex(1);
        ui->doubleSpinBox_ReciAcc->setValue(data->m_reciAcc);
        ui->doubleSpinBox_ReciDec->setValue(data->m_reciDec);
        ui->doubleSpinBox_ReciInterval->setValue(data->m_reciInterval);
        ui->doubleSpinBox_ReciMaxVel->setValue(data->m_reciMaxVel);
        ui->doubleSpinBox_ReciPulse->setValue(data->m_reciPulse);
        ui->spinBox_ReciTimes->setValue(data->m_reciTimes);

        ui->doubleSpinBox_ReciAcc->setStyleSheet("color:black");
        ui->doubleSpinBox_ReciDec->setStyleSheet("color:black");
        ui->doubleSpinBox_ReciInterval->setStyleSheet("color:black");
        ui->doubleSpinBox_ReciMaxVel->setStyleSheet("color:black");
        ui->doubleSpinBox_ReciPulse->setStyleSheet("color:black");
        ui->spinBox_ReciTimes->setStyleSheet("color:black");
    } else {
        ui->checkBox_PositionMotion->setChecked(false);
        ui->stackedWidget_Point->setCurrentIndex(0);
        ui->doubleSpinBox_PointAcc->setValue(data->m_pointAcc);
        ui->doubleSpinBox_PointDec->setValue(data->m_pointDec);
        ui->doubleSpinBox_PointMaxVel->setValue(data->m_pointMaxVel);
        ui->doubleSpinBox_PointPulse->setValue(data->m_pointPulse);

        ui->doubleSpinBox_PointAcc->setStyleSheet("color:black");
        ui->doubleSpinBox_PointDec->setStyleSheet("color:black");
        ui->doubleSpinBox_PointMaxVel->setStyleSheet("color:black");
        ui->doubleSpinBox_PointPulse->setStyleSheet("color:black");
    }
    if (data->m_motionSta == UiPosMotionData::RUN_STA_RUNNING) {
        setEnabled(false);
    } else {
        setEnabled(true);
    }
}

QList<UiPosMotionData *> UiMotionPosition::uiDataList()
{
    return m_uiDataList;
}

void UiMotionPosition::onSpinBoxValueChanged(int value)
{
    Q_UNUSED(value);
    QSpinBox *box = qobject_cast<QSpinBox *>(sender());
    box->setStyleSheet("color:red");
}

void UiMotionPosition::onDoubleSpinBoxValueChanged(double value)
{
    Q_UNUSED(value);
    QDoubleSpinBox *box = qobject_cast<QDoubleSpinBox *>(sender());
    box->setStyleSheet("color:red");
}

//void UiMotionPosition::onTimerTimeOut()
//{

//}

bool UiMotionPosition::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        qDebug()<<"key"<<keyEvent->key();
        if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
            //QSpinBox *sbox = dynamic_cast<QSpinBox *>(obj);
            //qDebug()<<"value "<<sbox->value();
            if (ui->stackedWidget_Point->currentIndex() == 0) {
                ui->doubleSpinBox_PointAcc->setStyleSheet("color:black");
                ui->doubleSpinBox_PointDec->setStyleSheet("color:black");
                ui->doubleSpinBox_PointMaxVel->setStyleSheet("color:black");
                ui->doubleSpinBox_PointPulse->setStyleSheet("color:black");

                for (int i = 0; i < q_ptr->axisListWidget()->count(); i++) {
                    if (q_ptr->axisListWidget()->item(i)->isSelected()) {
                        m_uiDataList.at(i)->m_pointAcc = ui->doubleSpinBox_PointAcc->value() / 360.0 * 65536;
                        m_uiDataList.at(i)->m_pointDec = ui->doubleSpinBox_PointDec->value() / 360.0 * 65536;
                        m_uiDataList.at(i)->m_pointMaxVel = ui->doubleSpinBox_PointMaxVel->value();
                        m_uiDataList.at(i)->m_pointPulse = ui->doubleSpinBox_PointPulse->value() * 65536;
                    }
                }
            } else if (ui->stackedWidget_Point->currentIndex() == 1) {
                ui->doubleSpinBox_ReciAcc->setStyleSheet("color:black");
                ui->doubleSpinBox_ReciDec->setStyleSheet("color:black");
                ui->doubleSpinBox_ReciInterval->setStyleSheet("color:black");
                ui->doubleSpinBox_ReciMaxVel->setStyleSheet("color:black");
                ui->doubleSpinBox_ReciPulse->setStyleSheet("color:black");
                ui->spinBox_ReciTimes->setStyleSheet("color:black");

                for (int i = 0; i < q_ptr->axisListWidget()->count(); i++) {
                    if (q_ptr->axisListWidget()->item(i)->isSelected()) {
                        m_uiDataList.at(i)->m_reciAcc = ui->doubleSpinBox_ReciAcc->value() / 360.0 * 65536;
                        m_uiDataList.at(i)->m_reciDec = ui->doubleSpinBox_ReciDec->value() / 360.0 * 65536;
                        m_uiDataList.at(i)->m_reciMaxVel = ui->doubleSpinBox_ReciMaxVel->value();
                        m_uiDataList.at(i)->m_reciInterval = ui->doubleSpinBox_ReciInterval->value();
                        m_uiDataList.at(i)->m_reciPulse = ui->doubleSpinBox_ReciPulse->value() * 65536;
                        m_uiDataList.at(i)->m_reciTimes = ui->spinBox_ReciTimes->value();
                    }
                }
            }
            return true;
        }
    }
    return QWidget::eventFilter(obj, event);
}

void UiMotionPosition::onCheckBoxReciClicked(bool checked)
{
    if(checked) {
        ui->stackedWidget_Point->setCurrentIndex(1);
    } else {
        ui->stackedWidget_Point->setCurrentIndex(0);
    }
    qDebug()<<q_ptr->axisListWidget()->count();
    for (int i = 0; i < q_ptr->axisListWidget()->count(); i++) {
        if (q_ptr->axisListWidget()->item(i)->isSelected()) {
            m_uiDataList.at(i)->m_isReci = checked ;
        }
    }
}

void UiMotionPosition::onCssChanged(const QString &css)
{
    setupIcons(css);
}

void UiMotionPosition::setupIcons(const QString &css)
{
    QString iconPath = GTUtils::customPath() + "option/style/" + css + "/icon/";

    ui->label_PointMotion->setScaledContents(true);
    ui->label_ReciMotion->setScaledContents(true);
    ui->label_PointMotion->setPixmap(QPixmap(iconPath + PIC_NAME_VPOINT));
    ui->label_ReciMotion->setPixmap(QPixmap(iconPath + PIC_NAME_VRECI));
}
