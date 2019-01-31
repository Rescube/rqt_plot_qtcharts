#ifndef PLOTLINESERIES_H
#define PLOTLINESERIES_H

#include <QtCharts/QChart>
#include <QtCharts/QChartGlobal>
#include <QtCharts/QLineSeries>

QT_CHARTS_BEGIN_NAMESPACE
class QLineSeries;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class PlotLineSeries : public QLineSeries
{
public:
    PlotLineSeries(QObject *parent = nullptr);
private:
    // topic name
    QString m_dataSource;


};

#endif // PLOTLINESERIES_H
