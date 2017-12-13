#ifndef CHANGFRAMADDR_H
#define CHANGFRAMADDR_H

#include <QObject>

class ChangFramAddr : public QObject
{
  Q_OBJECT
public:
  explicit ChangFramAddr(QObject *parent = 0);
  static void changeTreeAddr(const QString &fileName,int ofst);

signals:

public slots:
};

#endif // CHANGFRAMADDR_H
