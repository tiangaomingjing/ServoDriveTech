#ifndef OPTFACE_H
#define OPTFACE_H

#include <QObject>
#include "iopt.h"
namespace Ui {
class OptFace;
}
class OptFacePrivate;
class QLabel;

class StyleIconWidget:public QWidget
{
  Q_OBJECT
public:
  explicit StyleIconWidget(const QString &iconpath,const QString &title,const QString &css,QWidget *parent);
  ~StyleIconWidget();
  void setIcon(const QString &iconpath );
  void setIconTitle(const QString &title);

signals:
  void cssChanged(QString css);
protected:

  void mouseReleaseEvent(QMouseEvent *);

  void paintEvent(QPaintEvent *event);

private:
  QLabel *m_icon;
  QLabel *m_title;
  QString m_css;
  bool m_pressed;

};
class QSettings;
//class QmlStyleHelper;
class StyleWidget;
class QDoubleSpinBox;
class OPTIONSHARED_EXPORT OptFace : public IOpt
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(OptFace)
public:
  typedef enum{
    EDIT_TEXT_STATUS_DEFAULT,
    EDIT_TEXT_STATUS_READY,
    EDIT_TEXT_STATUS_EDITTING,
    EDIT_TEXT_STATUS_ERROR
  }EditTextStatus;

  explicit OptFace(const QString &optName, QWidget *parent = 0);
  ~OptFace();

  void uiInit()Q_DECL_OVERRIDE;
  void setFaceStyle(const QString &css);
  void setFaceFontSize(int size);
  int fontSize() const;
  QString css() const;
  QString language() const;
//  QmlStyleHelper *qmlStyleHelper() const;
  StyleWidget *customStyleWidget();
  void setEditTextStatus(QDoubleSpinBox *box,EditTextStatus sta);

  QString nickName()Q_DECL_OVERRIDE;
protected:
  bool optActive()Q_DECL_OVERRIDE;
  bool readOpt()Q_DECL_OVERRIDE;
  bool writeOpt()Q_DECL_OVERRIDE;
  void respondErrorExecute()Q_DECL_OVERRIDE;

signals:
  void faceCssChanged(const QString &css);

private slots:
  void onRadioButtonClicked(bool checked);
  void onCurrentIndexChanged(int index);
  void onStyleChanged(QString css);
  void updateEditTextStyleSheetList();

private:
  Ui::OptFace *ui;
};

#endif // OPTFACE_H
