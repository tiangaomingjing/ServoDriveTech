#ifndef MODECTLPANEL_H
#define MODECTLPANEL_H

#include <QWidget>
class QCheckBox;
class QComboBox;

class UiCheckCombo:public QWidget
{
  Q_OBJECT
public:
  explicit UiCheckCombo(quint16 axis,QWidget *parent);
  ~UiCheckCombo();

  QSize sizeHint();
signals:
  void checkChanged(bool checked);
  void modeChanged(int mode);
private:
  friend class ModeCtlPanel;
  quint16 m_axisNum;
  QCheckBox *m_checkBox;
  QComboBox *m_comboBox;
};

class ModeCtlPanel : public QWidget
{
  Q_OBJECT
public:
  explicit ModeCtlPanel(QWidget *parent = 0);
  explicit ModeCtlPanel(quint16 axisCount,QWidget *parent = 0);
  ~ModeCtlPanel();

  void setAxisCount(quint16 axis);
  quint16 axisCount() const;
  bool isChecked(quint16 axis);
  int mode(quint16 axis);
  void setChecked(quint16 axis, bool checked);
  void setMode(quint16 axis,int mode);

protected:
  void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
  void keyReleaseEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

signals:
  void checkChanged(quint16 axis,int mode);
  void modeChanged(quint16 axis,int mode);

public slots:
private slots:
  void onCheckChanged(bool checked);
  void onModeChanged(int mode);
private:
  void clearUiCheckComboList();
private:
  bool m_keyCtlIsPressed;
  quint16 m_axisCount;
  QList<UiCheckCombo *> m_uiCheckComboList;
};

#endif // MODECTLPANEL_H
