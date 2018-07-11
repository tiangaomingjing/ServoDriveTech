#ifndef AXISMODEWIDGET_H
#define AXISMODEWIDGET_H

#include <QWidget>
class QCheckBox;
class QComboBox;
class AxisModeWidget : public QWidget
{
  Q_OBJECT
public:
  typedef enum{
    MODE_IDLE,
    MODE_IPA,
    MODE_MPI,
    MODE_COL,
    MODE_CCL,
    MODE_VCL,
    MODE_OVL,
    MODE_CVL,
    MODE_FIX,
    MODE_POF,
    MODE_DBS,
    MODE_CCF
  }ServoMode;
  explicit AxisModeWidget(quint16 axis,QWidget *parent = 0);
  ~AxisModeWidget();

  bool checked() const;
  void setChecked(bool checked);

  quint16 axisNum() const;
  void setAxisNum(const quint16 axisNum);

  quint8 mode() const;
  void setMode(const quint8 mode);

protected:
  void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
  void keyReleaseEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

signals:
  void modeChanged(quint16 axis,int mode);
  void clearOthers(quint16 aixs);

public slots:
private slots:
  void onCheckBoxClicked(bool checked);
  void onComboBoxCurrentIndexChanged(int index);
private:
  quint16 m_axisNum;
  bool m_keyCtlIsPress;
  QCheckBox *m_checkBox;
  QComboBox *m_comboBox;
};

#endif // AXISMODEWIDGET_H
