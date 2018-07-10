#include "motionposition.h"
#include "uimotionposition.h"
#include "imotion_p.h"
#include "sevdevice.h"
#include "gtutils.h"
#include "Option"
#include <qmath.h>

#include <QListWidget>
#include <QDebug>

#define CON_KEYNAME_MOT_NOS         "gSevDrv.sev_obj.cur.mot.Nos_1"
#define CMD_POS_DELAY               "gSevDrv.sev_obj.pos.seq.prm.move_delay_times"
#define CMD_POS_MODE                "gSevDrv.sev_obj.pos.seq.prm.move_mode"
#define CMD_POS_MOV_EN              "gSevDrv.sev_obj.pos.seq.prm.rec_mov_en"
#define CMD_POS_CMDSRC              "gSevDrv.sev_obj.pos.seq.prm.psrc_sel"

class MotionPositionPrivate:public IMotionPrivate
{
    Q_DECLARE_PUBLIC(MotionPosition)
public:
    MotionPositionPrivate(){}
    ~MotionPositionPrivate(){}
protected:
    qint16 m_cmdSrc;
};

MotionPosition::MotionPosition(QListWidget *axisListWidget, SevDevice *sev, const QString &name, QObject *parent):
    IMotion(*(new MotionPositionPrivate),parent)
{
    Q_D(MotionPosition);
    setSevDevice(sev);
    setMotionType(MOTION_TYPE_POS);
    setName(name);
    d->m_axisListWidget = axisListWidget;
    UiMotionPosition *uiPos = new UiMotionPosition(this, 0);
    d->m_ui = uiPos;
    d->m_motionUnFinishVector.clear();
    connect(this, SIGNAL(motionFinish(quint16)), this, SLOT(onMotionFinish(quint16)));
    m_count = 0;
    m_timer.setTimerType(Qt::PreciseTimer);
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));
}

MotionPosition::~MotionPosition()
{
    Q_D(MotionPosition);
    delete d->m_ui;
}

void MotionPosition::movePrepare(quint16 axisInx)
{
    Q_D(MotionPosition);
    int tryCount = 1000;
    int tryUse = 0;
    bool isOn = false;
    do {
        d->m_sev->setAxisServoOn(axisInx, true);
        isOn = d->m_sev->axisServoIsOn(axisInx);
        GTUtils::delayms(1);
        tryUse++;
    } while (!isOn && tryUse < tryCount);

    if (!isOn) {
        return;
    }

    d->m_sev->setCurrentTaskServoMode(axisInx, ComDriver::TASK_MODE_POS_FOL);

    bool isOk;
    quint64 nos = d->m_sev->genCmdRead(CON_KEYNAME_MOT_NOS, axisInx, isOk);
    double scale = nos / qPow(2, 24);

    d->m_cmdSrc = d->m_sev->genCmdRead(CMD_POS_CMDSRC, axisInx, isOk);

    d->m_sev->genCmdWrite(CMD_POS_CMDSRC, 1, axisInx);

    UiPosMotionData* data = UiMotion()->uiDataList().at(axisInx);
    if (data->m_isReci) {
        double maxVel = data->m_reciMaxVel / scale;
        d->m_sev->genCmdWritePlanSpdMax(axisInx, maxVel);

        double acc = data->m_reciAcc;
        d->m_sev->genCmdWritePlanSpdAcc(axisInx, acc);

        double dec = data->m_reciDec;
        d->m_sev->genCmdWritePlanSpdDec(axisInx, dec);

        int pulse = data->m_reciPulse * 65536;
        d->m_sev->cmdSetPosRef(axisInx, pulse);

        double delay = data->m_reciInterval * 8;
        d->m_sev->genCmdWrite(CMD_POS_DELAY, delay, axisInx);
        d->m_sev->genCmdWrite(CMD_POS_MODE, 1, axisInx);
    } else {
        double maxVel = data->m_pointMaxVel / scale;
        d->m_sev->genCmdWritePlanSpdMax(axisInx, maxVel);

        double acc = data->m_pointAcc;
        d->m_sev->genCmdWritePlanSpdAcc(axisInx, acc);

        double dec = data->m_pointDec;
        d->m_sev->genCmdWritePlanSpdDec(axisInx, dec);

        int pulse = data->m_pointPulse * 65536;
        d->m_sev->cmdSetPosRef(axisInx, pulse);

        d->m_sev->genCmdWrite(CMD_POS_MODE, 0, axisInx);
    }

    d->m_motionUnFinishVector.clear();
}

bool MotionPosition::move(quint16 axisInx)
{
    Q_D(MotionPosition);
    if (!d->m_sev->axisServoIsOn(axisInx)) {
        return false;
    }
    m_count = 0;
    m_timer.start(100);
    d->m_motionUnFinishVector.append(axisInx);
    d->m_ui->setEnabled(false);
    //bool isOk;
    d->m_sev->genCmdWrite(CMD_POS_MOV_EN, 1, axisInx);
//    GTUtils::delayms(100);
//    quint64 ret = d->m_sev->genCmdRead(CMD_POS_MOV_EN, axisInx, isOk);
//    qDebug()<<"move ret"<<ret;
    return true;
}

bool MotionPosition::stop(quint16 axisInx)
{
    Q_D(MotionPosition);
    d->m_sev->genCmdWrite(CMD_POS_CMDSRC, d->m_cmdSrc, axisInx);
    d->m_sev->cmdSetPosRef(axisInx, 0);
    d->m_sev->genCmdWrite(CMD_POS_MOV_EN, 0, axisInx);
//    bool isOk;
//    quint64 ret = d->m_sev->genCmdRead(CMD_POS_MOV_EN, axisInx, isOk);
//    qDebug()<<"stop ret"<<ret;
    d->m_ui->setEnabled(true);
    m_timer.stop();
    return true;
}

void MotionPosition::updateAxisUi(quint16 axisInx)
{
    UiMotion()->updataUi(axisInx);
}

void MotionPosition::setMode()
{
    Q_D(MotionPosition);
    for (int i = 0; i < d->m_axisListWidget->count(); i++) {
        if (d->m_axisListWidget->item(i)->isSelected()) {
            d->m_sev->setCurrentTaskServoMode(i, GT::MODE_PT);
        }
    }
}

void MotionPosition::onMotionFinish(quint16 axisInx)
{

}

void MotionPosition::onTimerOut()
{
    Q_D(MotionPosition);
    for (int i = 0; i < d->m_axisListWidget->count(); i++) {
        if (d->m_axisListWidget->item(i)->isSelected()) {
            emit progressValueChanged(i, m_count % 100);
        }
    }
    m_count++;
}

UiMotionPosition * MotionPosition::UiMotion()
{
    Q_D(MotionPosition);
    UiMotionPosition *ui = qobject_cast<UiMotionPosition *>(d->m_ui);
    return ui;
}
