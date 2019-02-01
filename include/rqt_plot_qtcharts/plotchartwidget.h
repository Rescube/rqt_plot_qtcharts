#ifndef PLOTCHARTWIDGET_H
#define PLOTCHARTWIDGET_H

#include "plotlineseries.h"
#include "plotverticalaxis.h"
#include "plotverticalaxesmodel.h"
#include "zoomablechartview.h"

#include <rqt_gui_cpp/plugin.h>

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
    friend class PlotVerticalAxesModel;
    Q_OBJECT
public:
    explicit PlotChartWidget(QWidget *parent = nullptr);
    ~PlotChartWidget();

    void saveSettings(qt_gui_cpp::Settings& instance_settings) const;
    void restoreSettings(const qt_gui_cpp::Settings& instance_settings);

    void addSeries(PlotLineSeries *seriesList);
    void removeSeries(PlotLineSeries *seriesList);
    void addAxis(PlotVerticalAxis *axis);

    QList<PlotVerticalAxis *> verticalAxes() const;
    void connectLegendMarkerEvents();

    QList<PlotLineSeries *> seriesList() const;

private:
    QChart *m_chart;
    ZoomableChartView *m_chartView;
    QValueAxis *m_axisX;

    QList<PlotLineSeries*> m_series;
    QList<PlotVerticalAxis*> m_verticalAxes;

    void saveAxes(qt_gui_cpp::Settings &instance_settings) const;
    void saveSeries(qt_gui_cpp::Settings &instance_settings) const;
    void restoreAxes(const qt_gui_cpp::Settings &instance_settings);
    void restoreSeries(const qt_gui_cpp::Settings &instance_settings);
    void addDefaultAxis();
    void setVisibilityOfMarkerAndSeries(QLegendMarker* marker, bool visible);

private slots:
    void handleMarkerClicked();
};

#endif // PLOTCHARTWIDGET_H
