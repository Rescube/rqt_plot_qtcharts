#include "plotlineseries.h"

#include <QDebug>
#include <QPen>

QT_CHARTS_USE_NAMESPACE

PlotLineSeries::PlotLineSeries(QObject *parent) :
    QLineSeries(parent)
{
    setUseOpenGL(true);
}

QString PlotLineSeries::dataSource() const
{
    return m_dataSource;
}

void PlotLineSeries::setDataSource(const QString &dataSource)
{
    m_dataSource = dataSource;
}

QColor PlotLineSeries::color() const
{
    return pen().color();
}

void PlotLineSeries::setColor(const QColor &color)
{
    QPen pen = this->pen();
    pen.setColor(color);
    setPen(pen);
}

qreal PlotLineSeries::width() const
{
    return pen().width();
}

void PlotLineSeries::setWidth(const qreal &width)
{
    QPen pen = this->pen();
    pen.setWidth(width);
    setPen(pen);
}

VerticalAxis *PlotLineSeries::verticalAxis() const
{
    return m_verticalAxis;
}

void PlotLineSeries::setVerticalAxis(VerticalAxis *verticalAxis)
{
    if (m_verticalAxis != verticalAxis) {
        m_verticalAxis = verticalAxis;
        emit axisChanged();
    }
}

void PlotLineSeries::dataReceived(qreal y)
{
    append(m_xIndex, y);
    m_xIndex++;

    if (m_verticalAxis)
        m_verticalAxis->seriesPointAdded(y);
}

void PlotLineSeries::clear()
{
    m_xIndex = 0;
    QLineSeries::clear();
    append(QPointF(0,0));

    if (m_verticalAxis)
        m_verticalAxis->resetRange();
}
