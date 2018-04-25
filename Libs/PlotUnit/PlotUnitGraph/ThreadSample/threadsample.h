#ifndef THREADSAMPLE_H
#define THREADSAMPLE_H

#include <QObject>
#include <QThread>

class ThreadSample : public QThread
{
  Q_OBJECT
public:
  explicit ThreadSample(QObject *parent = 0);

signals:

public slots:
};

#endif // THREADSAMPLE_H
