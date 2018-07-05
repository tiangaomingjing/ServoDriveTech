#ifndef LINKSOCKET_H
#define LINKSOCKET_H

#include <QObject>
#include "sdtglobaldef.h"
#include "icom.h"

GT_USE_NAMESPACE
namespace ComDriver
{
  class ICom;
}

class SevDevicePrivate;
class QTreeWidgetItem;
class GeneralCmd;
class CmdManager;

class LinkSocket : public QObject
{
  Q_OBJECT
public:
   explicit LinkSocket(SevDevicePrivate *sev,QObject *parent = 0);
  ~LinkSocket();

  bool connect(void (*processCallBack)(void *argv, short *value), void *uiProcessBar);
  void disConnect();
  QString socketName()const;
  quint8 socketTypeId()const;
  bool isConnected() const;
  void setTryWriteCount(quint8 tryWriteCount);

  bool readPageItemFlash(int axis,QTreeWidgetItem *item);
  bool writePageItemFlash(int axis,QTreeWidgetItem *item);

  bool readAdvItemFlash(int axisInx, QTreeWidgetItem *item);
  bool writeAdvItemFlash(int axisInx, QTreeWidgetItem *item);
  bool readAdvItemRam(int axisInx, QTreeWidgetItem *item);
  bool readAdvItemRam(quint16 axisInx, quint16 offset, quint16 base, int bytesNum , double &result);
  bool writeAdvItemRam(int axisInx, QTreeWidgetItem *item);

  bool startPlot(const ComDriver::PlotControlPrm &ctrPrm);
  bool stopPlot(const ComDriver::PlotControlPrm &ctrPrm);
  bool getPlotData(const ComDriver::PlotControlPrm &ctrPrm,ComDriver::CurveList &curveList);


  //通用RAM读写操作
  quint64 genCmdRead(const QString &cmdReadName,qint16 axisIndex,bool &isOk);
  bool genCmdWrite(const QString &cmdWriteName,quint64 value,qint16 axisIndex);
  qint16 genReadErrorCode();
  bool containsCmd(const QString &cmdName);

  bool readXml(quint8 axis, const QStringList &fileNameList, QList<int> fileTypeList, int file_num, void (*processCallBack)(void *, short *), void *ptrv, short &progress);
  bool writeXml(quint8 axis, const QStringList &fileNameList, QList<int> fileTypeList, int file_num, void (*processCallBack)(void *, short *), void *ptrv, short &progress);

  ComDriver::ICom *comObject() const;

  bool adjust(void (*processCallBack)(void *argv, short *value), void *uiProcessBar);

  bool clearAlarm(quint16 axisInx);

  bool writePrmItemFlash(int axis, QTreeWidgetItem *item);
  bool readPrmItemFlash(int axis, QTreeWidgetItem *item);
  bool axisServoIsOn(quint16 axisInx);
  void setAxisServoOn(quint16 axisInx,bool enable);

  int currentTaskServoMode(quint16 axisInx);
  void setCurrentTaskServoMode(quint16 axisInx, int mode);
protected:

private:

signals:

public slots:

private:
  friend class SevDevice;
  SevDevicePrivate *q_ptr;
  bool m_isConnected;
  ComDriver::ICom *m_com;
  quint8 m_tryWriteCount;
  GeneralCmd *m_genCmd;
  CmdManager *m_cmdManager;
};

#endif // LINKSOCKET_H
