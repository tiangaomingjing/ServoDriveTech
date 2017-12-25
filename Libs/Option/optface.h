#ifndef OPTFACE_H
#define OPTFACE_H

#include <QObject>
#include "iopt.h"
namespace Ui {
class OptFace;
}
class OptFacePrivate;
class OPTIONSHARED_EXPORT OptFace : public IOpt
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(OptFace)
public:
  explicit OptFace(const QString &optName, QWidget *parent = 0);
  ~OptFace();
  bool optActive();
  void setFaceStyle(const QString &css);
  void setFaceFontSize(int size);

signals:

public slots:
private:
  Ui::OptFace *ui;
};

#endif // OPTFACE_H
