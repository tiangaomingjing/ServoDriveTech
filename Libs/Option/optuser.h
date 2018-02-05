#ifndef OPTUSER_H
#define OPTUSER_H

#include <QObject>
#include <QWidget>
#include <QLayout>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include "iopt.h"
namespace Ui {
class OptUser;
}

class OptUserPrivate;

class OPTIONSHARED_EXPORT OptUser : public IOpt
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(OptUser)
public:
  explicit OptUser(const QString &optName, QWidget *parent = 0);
  ~OptUser();

  void uiInit()Q_DECL_OVERRIDE;

  bool isAdmin() const;
  bool isChecked() const;
protected:
  bool optActive()Q_DECL_OVERRIDE;
  bool readOpt()Q_DECL_OVERRIDE;
  bool writeOpt()Q_DECL_OVERRIDE;
  void respondErrorExecute()Q_DECL_OVERRIDE;
signals:
  void usrChange(bool isAdmin);

public slots:
private:
  Ui::OptUser *ui;
private slots:
  void onActionBtnChecked();
  void onActionLineChange();
private:
};

class UserCheckWidgetPrivate : public QWidget
{
    Q_OBJECT

public:
    explicit UserCheckWidgetPrivate(QWidget *parent = 0);
    ~UserCheckWidgetPrivate();
    void setCheck(bool isChecked);
    bool isChecked();
    QString getPsw();
    void pswClear();
signals:
    void stateChanged();

private:
    QCheckBox *checkBox;
    QLineEdit *lineEdit;
private slots:
    void onStateChanged();
};

#endif // OPTUSER_H
