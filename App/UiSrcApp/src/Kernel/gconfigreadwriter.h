#ifndef GCONFIGREADWRITER_H
#define GCONFIGREADWRITER_H

#include <QObject>

class GlobalConfig;
class GConfigReadWriter : public QObject
{
  Q_OBJECT
public:
  explicit GConfigReadWriter(QObject *parent = 0);
  bool fillConfig(GlobalConfig *config){ Q_UNUSED(config) return true;}
  bool saveConfig(const GlobalConfig *config){Q_UNUSED(config) return true;}
signals:

public slots:
};

#endif // GCONFIGREADWRITER_H
