#ifndef IMAPPING_H
#define IMAPPING_H

#include <QObject>

class IMapping : public QObject
{
  Q_OBJECT
public:
  explicit IMapping(QObject *parent = 0);
  virtual ~IMapping();

signals:

public slots:
};

#endif // IMAPPING_H
