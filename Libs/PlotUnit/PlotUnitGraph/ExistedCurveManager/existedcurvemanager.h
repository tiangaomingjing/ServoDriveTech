#ifndef EXISTEDCURVEMANAGER_H
#define EXISTEDCURVEMANAGER_H
#include "gtplot.h"
#include "icurve.h"

#include <QObject>

class QTableWidget;
class QLayout;
class ExistedCurveManagerPrivate;

class ExistedCurveManager : public QObject
{
    Q_OBJECT
public:
    explicit ExistedCurveManager(const QList<ICurve*> &curveList, QObject *parent = 0);
    ~ExistedCurveManager();
    void insertTable(QVBoxLayout* layout, int index);
    void insertPlot(QVBoxLayout* layout, int index);
    void removeTable(QVBoxLayout* layout);
    void removePlot(QVBoxLayout* layout);
    void addCurvesToTable();
    void getTableColor(const QColor &showColor, const QColor &backShowColor, const QColor &hideColor, const QColor &backHideColor);
private:

signals:
    void sendItemEnetered(QTableWidgetItem* item);
    void sendNewPos(const QPointF &point);
public slots:
    void onBtnMeaHClicked(bool checked);
    void onBtnMeaVClicked(bool checked);
    void onBtnFitClicked();
    void onBtnCurveShowAllClicked();
private slots:
    void onCurveTableItemClicked(QTableWidgetItem* item);
    void onCurveTableItemDoubleClicked(QTableWidgetItem* item);
private:
    void initUi();
    void insertCurveRow(ICurve* curve, QCPGraph *graph);
    void setUiStatusCurveTableWidgetOnOff(int row, bool on);
private:
    ExistedCurveManagerPrivate* dd;
};

#endif // EXISTEDCURVEMANAGER_H
