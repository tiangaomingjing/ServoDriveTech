#include "optface.h"
#include "ui_optface.h"
#include "iopt_p.h"

#include <QDebug>

class OptFacePrivate:public IOptPrivate
{
  Q_DECLARE_PUBLIC(OptFace)
public:
  OptFacePrivate();
  ~OptFacePrivate();
};
OptFacePrivate::OptFacePrivate()
{

}
OptFacePrivate::~OptFacePrivate()
{

}

OptFace::OptFace(const QString &optName, QWidget *parent) :  IOpt(optName,*new OptFacePrivate,parent),
  ui(new Ui::OptFace)
{
  ui->setupUi(this);
}
OptFace::~OptFace()
{
  delete ui;
}
bool OptFace::optActive()
{
  return true;
}

