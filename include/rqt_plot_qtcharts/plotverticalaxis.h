#ifndef PLOTVERTICALAXIS_H
#define PLOTVERTICALAXIS_H

#include <QtCharts/QValueAxis>

QT_CHARTS_BEGIN_NAMESPACE
class QValueAxis;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class PlotVerticalAxis : public QValueAxis
{
public:
    PlotVerticalAxis(QObject *parent = nullptr);
};

#endif // PLOTVERTICALAXIS_H
