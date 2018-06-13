#ifndef IUIWIDGET_H
#define IUIWIDGET_H

#include "iuiwidget_global.h"
#include "iuiwidgetgdef.h"
#include <QWidget>


class IUiWidgetPrivate;
class QStackedWidget;
class QVBoxLayout;
class SevDevice;
class QTreeWidget;
class QTreeWidgetItem;

class UiIndexs
{
public:
  quint32 devInx;
  qint16 axisInx;
  qint16 pageInx;
};

class IUIWIDGETSHARED_EXPORT IUiWidget:public QWidget
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(IUiWidget)

public:
//  explicit IUiWidget(QWidget *parent = 0);
  virtual ~IUiWidget();

  virtual bool init(SevDevice*device);
  virtual void addTreeWidget(QTreeWidget* tree);
  void setUiIndexs(const UiIndexs &indexs);
  UiIndexs uiIndexs() const;
  virtual bool readPageFLASH();//根据地址读
  virtual bool writePageFLASH();//响应界面save 功能
  virtual bool readGenPageRAM();//通用指令读
  virtual bool writeGenPageRAM();//通用指令写
  virtual void setUiActive(bool actived);
  virtual void accept(QWidget*w);

  virtual bool hasConfigFunc();
  virtual bool hasSaveFunc();

  SevDevice* device();

protected:
  virtual QStackedWidget *getUiStackedWidget(void)=0;
  virtual QVBoxLayout *getVBoxLayout(void)=0;
  virtual void setDefaultUi()=0;
  virtual void setCurrentUiIndex(quint8 index);//设置当前两页中显示的页
  virtual void setContextAction();

  void createActionSwitchView();
  bool parametersNeedChecked();

signals:
  void sglMainErrorInfo(int axis,QString msg);
  void uiActiveChanged(bool active);//send to ui graph to update data or do other things

  //to device
  void sglReadPageFlash(int axis ,QTreeWidget *pTree);
  void sglWritePageFlash(int axis ,QTreeWidget *pTree);

protected slots:
  virtual void onTreeItemClickedEdit(QTreeWidgetItem *item,int column);
  void onSwitchView(bool isList);
  virtual void onActionReadRAM();
  virtual void onActionReadFLASH();
  virtual void onDspReset();
protected:
  IUiWidget(IUiWidgetPrivate&dd, QWidget *parent=0);
  IUiWidgetPrivate *d_ptr;
};

#endif // IUIWIDGET_H
