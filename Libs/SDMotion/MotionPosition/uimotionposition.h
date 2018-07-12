#ifndef UIMOTIONPOSITION_H
#define UIMOTIONPOSITION_H

#include "motionposition_global.h"

#include <QWidget>

namespace Ui {
class UiMotionPosition;
}

class MotionPosition;
class SevDevice;

class UiPosMotionData
{

public:
    typedef enum{
        RUN_STA_INIT = 0,
        RUN_STA_CHECK_ON = 1,
        RUN_STA_RUNNING = 2,
        RUN_STA_STOPING = 3,
        RUN_STA_STOP_FINISH = 4
    }MotionRunSta;
    UiPosMotionData():
        m_isReci(false),
        m_pointAcc(1300),
        m_pointDec(1300),
        m_pointMaxVel(1000),
        m_pointPulse(327680),
        m_reciAcc(1300),
        m_reciDec(1300),
        m_reciInterval(1000),
        m_reciMaxVel(1000),
        m_reciPulse(327680),
        m_reciTimes(0)
    {}
    ~UiPosMotionData(){}
    bool m_isReci;
    double m_pointAcc;
    double m_pointDec;
    double m_pointMaxVel;
    int m_pointPulse;

    double m_reciAcc;
    double m_reciDec;
    double m_reciMaxVel;
    double m_reciInterval;
    int m_reciPulse;
    int m_reciTimes;

    MotionRunSta m_motionSta;
};

class MOTIONPOSITIONSHARED_EXPORT UiMotionPosition : public QWidget
{
    Q_OBJECT

public:
    explicit UiMotionPosition(MotionPosition *mp, QWidget *parent = 0);
    ~UiMotionPosition();
    void updataUi(int axisInx);
    QList<UiPosMotionData*> uiDataList();
protected:
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void onCheckBoxReciClicked(bool checked);
    void onCssChanged(const QString &css);
    void onSpinBoxValueChanged(int value);
    void onDoubleSpinBoxValueChanged(double value);
    //void onTimerTimeOut();

private:
    void setupIcons(const QString &css);
private:
    Ui::UiMotionPosition *ui;
    int m_axisCount;
    QList<UiPosMotionData*> m_uiDataList;
    MotionPosition *q_ptr;
    //QTimer* m_timer;
};

#endif // UIMOTIONPOSITION_H
