#ifndef CURVEMANAGER_H
#define CURVEMANAGER_H

#include <QObject>
class ICurve;

class CurveManager : public QObject
{
  Q_OBJECT
public:
  explicit CurveManager(QObject *parent = 0);
  ~CurveManager();

  QList<ICurve *> curveList() const;
  void addCurve(ICurve *curve);
  void removeCurve(ICurve *curve);
  void removeCurve(int inx);
  void clearCurve();

  int varCurveTotalCount();

  QColor color(int totalCount) const;

signals:

public slots:

private:
  QList<ICurve *> m_curveList;
  QList<QColor>m_colorDefault;
};

#endif // CURVEMANAGER_H
