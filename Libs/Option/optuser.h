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

  bool isAdmin() const;

protected:
  bool optActive()Q_DECL_OVERRIDE;
  bool readOpt(QSettings *settings)Q_DECL_OVERRIDE;
  bool writeOpt(QSettings *settings)Q_DECL_OVERRIDE;
signals:
  void usrChange(bool isAdmin);

public slots:
private:
  Ui::OptUser *ui;
};

#endif // OPTUSER_H
