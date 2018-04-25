#ifndef IGRAPHENCODER_H
#define IGRAPHENCODER_H

#include <QWidget>
#include "iuiwidget_global.h"
#include "igraph.h"

class IGraphEncoderPrivate;
class IUiWidget;

class IUIWIDGETSHARED_EXPORT IGraphEncoder : public IGraph
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(IGraphEncoder)
public:
//  explicit IGraphEncoder(QWidget *parent = 0);
  virtual ~IGraphEncoder();
  void startUpdateTimer(bool enabled);

protected:
  virtual void setUiVersionName()Q_DECL_OVERRIDE =0;
  virtual void setCustomVisitActive(IUiWidget*uiWidget)Q_DECL_OVERRIDE =0;
  virtual void setupDataMappings()=0;

  virtual qint32 readPos(const QString &key);
  virtual qint32 readPosInput(const QString &key);
  virtual qint32 readPosOffset(const QString &key);
  virtual quint16 readPPN(const QString &key);
  virtual quint16 readSeqDir(const QString &key);
  virtual quint16 readEncInfo(const QString &key);
  virtual quint16 readErrLost(const QString &key);
  virtual quint32 getLineNumber(){return 0;}
  virtual void createSupportEncoderItem(){}

protected slots:
  virtual void onUpdateTimeOut()=0;

signals:

public slots:
protected:
  IGraphEncoder(IGraphEncoderPrivate &dd, QWidget *parent=0);
};

#endif // IGRAPHENCODER_H
