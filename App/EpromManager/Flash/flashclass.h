#ifndef FLASHCLASS_H
#define FLASHCLASS_H
#include <QTreeWidget>
#include <QString>

class JsonReader;

class FlashClass : public QObject
{
    Q_OBJECT
public:
    FlashClass();
    void flash(int netId, QString hexPath, QString xmlPath, int dspNum, QObject *proBar);
signals:
    void changeBarCount(int value);
    void sendWarnMsg(QString msg);
private:
    static void updateProgessBarWhenRestoreClicked(void *arg, qint16 *value);
    void delayms(quint16 ms);
    bool uBoot(QString ldrPath, JsonReader net, QObject *proBar);
    bool downloadHex(QObject *proBar);
private:
    QTreeWidget* mp_funcExtension;
    static int m_dspNum;
    static int m_step;
    static int m_progessValue;
    QString m_hexPath;
    QString m_xmlPath;
    int m_netId;
    qint16 m_netRnStation;
private slots:
    void onXmlPrmToServo(int value);
};

#endif // FLASHCLASS_H
