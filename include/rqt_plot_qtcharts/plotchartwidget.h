#ifndef PLOTCHARTWIDGET_H
#define PLOTCHARTWIDGET_H

#include "plotlineseries.h"
#include "plotverticalaxis.h"
#include "zoomablechartview.h"

#include <QWidget>

#include <QtCharts/QChart>
#include <QtCharts/QChartGlobal>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

QT_CHARTS_BEGIN_NAMESPACE
class QLineSeries;
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE


class PlotChartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlotChartWidget(QWidget *parent = nullptr);
    ~PlotChartWidget();

    void saveSettings(qt_gui_cpp::Settings& instance_settings) const;
    void restoreSettings(const qt_gui_cpp::Settings& instance_settings);
signals:

public slots:
private:
     QChart *m_chart;
     ZoomableChartView *m_chartView;
     QValueAxis *m_axisX;

     QList<PlotLineSeries*> m_series;
     QList<PlotVerticalAxis*> m_verticalAxes;
};

#endif // PLOTCHARTWIDGET_H
