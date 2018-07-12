#ifndef MOTIONPOSITION_H
#define MOTIONPOSITION_H

#include "motionposition_global.h"
#include "imotion.h"

#include <QTimer>

class MotionPositionPrivate;
class UiMotionPosition;

class MOTIONPOSITIONSHARED_EXPORT MotionPosition : public IMotion
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(MotionPosition)

public:
    explicit MotionPosition(QListWidget *axisListWidget, SevDevice *sev, const QString &name = "position", QObject *parent = 0);
    ~MotionPosition();

    void movePrepare(quint16 axisInx) Q_DECL_OVERRIDE;
    bool move(quint16 axisInx) Q_DECL_OVERRIDE;
    bool stop(quint16 axisInx) Q_DECL_OVERRIDE;
    void updateAxisUi(quint16 axisInx) Q_DECL_OVERRIDE;
    void setMode() Q_DECL_OVERRIDE;
    UiMotionPosition * UiMotion();
private slots:
    void onMotionFinish(quint16 axisInx);
    void onTimerOut();

private:

private:
    QTimer m_timer;
    int m_count;
};

#endif // MOTIONPOSITION_H
