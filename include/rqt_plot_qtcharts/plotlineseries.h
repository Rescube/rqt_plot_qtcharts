#ifndef PLOTLINESERIES_H
#define PLOTLINESERIES_H

#include "rqt_plot_qtcharts/plotverticalaxis.h"

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
    QString dataSource() const;
    void setDataSource(const QString &dataSource);

    QColor color() const;
    void setColor(const QColor &color);

    qreal width() const;
    void setWidth(const qreal &width);

    PlotVerticalAxis *verticalAxis() const;
    void setVerticalAxis(PlotVerticalAxis *verticalAxis);

private:
    // topic name
    QString m_dataSource;
    PlotVerticalAxis *m_verticalAxis = nullptr;
};

#endif // PLOTLINESERIES_H
