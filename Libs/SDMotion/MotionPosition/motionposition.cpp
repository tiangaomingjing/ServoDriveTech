#include "motionposition.h"
#include "uimotionposition.h"
#include "imotion_p.h"
#include "sevdevice.h"
#include "gtutils.h"
#include "Option"
#include <qmath.h>

#define CON_KEYNAME_MOT_NOS         "gSevDrv.sev_obj.cur.mot.Nos_1"
#define CMD_POS_MAXSPD              "gSevDrv.sev_obj.pos.mkr.prm.maxspd"
#define CMD_POS_ACC                 "gSevDrv.sev_obj.pos.mkr.prm.accrate"
#define CMD_POS_DEC                 "gSevDrv.sev_obj.pos.mkr.prm.decrate"
#define CMD_POS_DELAY               "gSevDrv.sev_obj.pos.seq.prm.move_delay_times"
#define CMD_POS_MODE                "gSevDrv.sev_obj.pos.seq.prm.move_mode"
#define CMD_POS_MOV_EN              "gSevDrv.sev_obj.pos.seq.prm.rec_mov_en"

class MotionPositionPrivate:public IMotionPrivate
{
    Q_DECLARE_PUBLIC(MotionPosition)
public:
    MotionPositionPrivate(){}
    ~MotionPositionPrivate(){}
protected:

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

    UiPosMotionData* data = UiMotion()->uiDataList().at(axisInx);
    if (data->m_isReci) {
        double maxVel = data->m_reciMaxVel / scale;
        d->m_sev->genCmdWrite(CMD_POS_MAXSPD, maxVel, axisInx);

        double acc = data->m_reciAcc;
        d->m_sev->genCmdWrite(CMD_POS_ACC, acc, axisInx);

        double dec = data->m_reciDec;
        d->m_sev->genCmdWrite(CMD_POS_DEC, dec, axisInx);

        int pulse = data->m_reciPulse;
        d->m_sev->cmdSetPosRef(axisInx, pulse);

        double delay = data->m_reciInterval;
        d->m_sev->genCmdWrite(CMD_POS_DELAY, delay, axisInx);
        d->m_sev->genCmdWrite(CMD_POS_MODE, 1, axisInx);
    } else {
        double maxVel = data->m_pointMaxVel / scale;
        d->m_sev->genCmdWrite(CMD_POS_MAXSPD, maxVel, axisInx);

        double acc = data->m_pointAcc;
        d->m_sev->genCmdWrite(CMD_POS_ACC, acc, axisInx);

        double dec = data->m_pointDec;
        d->m_sev->genCmdWrite(CMD_POS_DEC, dec, axisInx);

        int pulse = data->m_pointPulse;
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
    d->m_motionUnFinishVector.append(axisInx);
    d->m_ui->setEnabled(false);
    d->m_sev->genCmdWrite(CMD_POS_MOV_EN, 1, axisInx);
    return true;
}

bool MotionPosition::stop(quint16 axisInx)
{
    Q_D(MotionPosition);
    d->m_sev->genCmdWrite(CMD_POS_MOV_EN, 0, axisInx);
    d->m_ui->setEnabled(true);
    return true;
}

void MotionPosition::updateAxisUi(quint16 axisInx)
{
    UiMotion()->updataUi(axisInx);
}

void MotionPosition::onMotionFinish(quint16 axisInx)
{

}

UiMotionPosition * MotionPosition::UiMotion()
{
    Q_D(MotionPosition);
    UiMotionPosition *ui = qobject_cast<UiMotionPosition *>(d->m_ui);
    return ui;
}
