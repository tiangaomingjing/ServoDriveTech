#ifndef SCREENSTARTUP_H
#define SCREENSTARTUP_H

#include <QSplashScreen>
class QProgressBar;
class QLabel;
class ScreenStartup : public QSplashScreen
{
  Q_OBJECT
public:
  explicit ScreenStartup(QPixmap& pixmap);

signals:

public slots:
  void onProgressMessage(int barValue,QString msg);
private:
  QProgressBar *pBar;
  QLabel *label;
};

#endif // SCREENSTARTUP_H
