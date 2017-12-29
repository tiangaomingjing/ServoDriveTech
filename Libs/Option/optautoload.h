#ifndef OPTAUTOLOAD_H
#define OPTAUTOLOAD_H

#include <QObject>
#include "iopt.h"
namespace Ui {
class OptAutoLoad;
}
class OptAutoLoadPrivate;
class QSettings;

class OPTIONSHARED_EXPORT OptAutoLoad : public IOpt
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(OptAutoLoad)
public:
  explicit OptAutoLoad(const QString &optName,QWidget *parent = 0);
  ~OptAutoLoad();

  void uiInit()Q_DECL_OVERRIDE;

protected:
  bool optActive()Q_DECL_OVERRIDE;
  bool readOpt()Q_DECL_OVERRIDE;
  bool writeOpt()Q_DECL_OVERRIDE;
  void respondErrorExecute()Q_DECL_OVERRIDE;

private slots:
  void onCheckedBoxClicked();
  void onRespondErrorExe();

signals:

public slots:
private:
  Ui::OptAutoLoad *ui;
};

#endif // OPTAUTOLOAD_H
