#ifndef GTDOUBLESPINBOX_H
#define GTDOUBLESPINBOX_H

#include <QDoubleSpinBox>

class GtDoubleSpinBox : public QDoubleSpinBox
{
  Q_OBJECT
  Q_PROPERTY(QColor defaultColor READ defaultColor WRITE setDefaultColor NOTIFY defaultColorChanged)
  Q_PROPERTY(QColor readyColor READ readyColor WRITE setReadyColor NOTIFY readyColorChanged)
  Q_PROPERTY(QColor errorColor READ errorColor WRITE setErrorColor NOTIFY errorColorChanged)
public:
  explicit GtDoubleSpinBox(QWidget * parent = 0);
  ~GtDoubleSpinBox();

  QColor defaultColor() const;
  void setDefaultColor(const QColor &defaultColor);

  QColor readyColor() const;
  void setReadyColor(const QColor &readyColor);

  QColor errorColor() const;
  void setErrorColor(const QColor &errorColor);

signals:
  void defaultColorChanged();
  void readyColorChanged();
  void errorColorChanged();

public slots:
protected:

private:
  QColor m_defaultColor;
  QColor m_readyColor;
  QColor m_errorColor;
};

#endif // GTDOUBLESPINBOX_H
