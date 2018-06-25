#ifndef UIMOTIONPOSITION_H
#define UIMOTIONPOSITION_H

#include <QWidget>

namespace Ui {
class UiMotionPosition;
}

class MotionPosition;

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
        m_isReci(false)
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

class UiMotionPosition : public QWidget
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

private:
    void setupIcons(const QString &css);
private:
    Ui::UiMotionPosition *ui;
    int m_axisCount;
    QList<UiPosMotionData*> m_uiDataList;
    MotionPosition *q_ptr;
};

#endif // UIMOTIONPOSITION_H
