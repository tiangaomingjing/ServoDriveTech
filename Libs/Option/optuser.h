#ifndef OPTUSER_H
#define OPTUSER_H

#include <QObject>
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

protected:
  bool optActive()Q_DECL_OVERRIDE;
  bool readOpt()Q_DECL_OVERRIDE;
  bool writeOpt()Q_DECL_OVERRIDE;
  void respondErrorExecute()Q_DECL_OVERRIDE;
signals:
  void usrChange(bool isAdmin, bool isChecked);

public slots:
private:
  Ui::OptUser *ui;
private slots:
  void onActionBtnChecked();
};

#endif // OPTUSER_H
