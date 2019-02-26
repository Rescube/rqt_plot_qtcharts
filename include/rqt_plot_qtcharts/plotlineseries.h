#ifndef PLOTLINESERIES_H
#define PLOTLINESERIES_H

#include "verticalaxis.h"

#include <QtCharts/QChart>
#include <QtCharts/QChartGlobal>
#include <QtCharts/QLineSeries>

QT_CHARTS_BEGIN_NAMESPACE
class QLineSeries;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class PlotLineSeries : public QLineSeries
{
    Q_OBJECT
public:
    PlotLineSeries(QObject *parent = nullptr);
    QString dataSource() const;
    void setDataSource(const QString &dataSource);

    QColor color() const;
    void setColor(const QColor &color);

    qreal width() const;
    void setWidth(const qreal &width);

    VerticalAxis *verticalAxis() const;
    void setVerticalAxis(VerticalAxis *verticalAxis);

    void dataReceived(qreal y);
    void clear();

    qreal scale() const;
    void setScale(const qreal &scale);

private:
    // topic name
    QString m_dataSource;
    VerticalAxis *m_verticalAxis = nullptr;
    qreal m_xIndex = 0;
    qreal m_scale = 1.0;
signals:
    void axisChanged();
    void visiblityChanged(bool visible);
};

#endif // PLOTLINESERIES_H

