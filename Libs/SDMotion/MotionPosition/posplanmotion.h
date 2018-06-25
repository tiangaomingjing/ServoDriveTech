#ifndef POSPLANMOTION_H
#define POSPLANMOTION_H

#include <QObject>
#include <QTimer>

class SevDevice;
class UiPosMotionData;

class PosPlanMotion : public QObject
{
    Q_OBJECT
public:
    explicit PosPlanMotion(quint16 axisInx, SevDevice *dev, UiPosMotionData *data, QObject *parent = 0);
    ~PosPlanMotion();
    QTimer *timer();
    void movePrepare();
    void move();
    void stop();

signals:
    void motionFinish(quint16 axisInx);
    void progressValueChanged(quint16 axisInx,int value);

public slots:
private slots:
    void onTimerOut();

private:
    QTimer m_timer;
    SevDevice *m_sev;
    UiPosMotionData *m_data;
    quint16 m_axisInx;
};

#endif // POSPLANMOTION_H
