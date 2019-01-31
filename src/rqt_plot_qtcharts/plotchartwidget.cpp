#include "rqt_plot_qtcharts/plotchartwidget.h"

#include <rqt_gui_cpp/plugin.h>

#include <QVBoxLayout>

QT_CHARTS_USE_NAMESPACE

PlotChartWidget::PlotChartWidget(QWidget *parent) : QWidget(parent)
{
    m_chart = new QChart();
    m_chartView = new ZoomableChartView(m_chart);

    m_axisX = new QValueAxis(this);
    m_axisX->setRange(0, 1000);
    m_axisX->setLabelFormat("%g");
    m_chartView->chart()->setAxisX(m_axisX);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_chartView);
    setLayout(mainLayout);
}

PlotChartWidget::~PlotChartWidget()
{
    for (PlotVerticalAxis *axis : m_verticalAxes)
        m_chart->removeAxis(axis);
    delete m_chart;
}

void PlotChartWidget::saveSettings(qt_gui_cpp::Settings &instance_settings) const
{
    instance_settings.setValue("seriesCount", m_series.count());
}

void PlotChartWidget::restoreSettings(const qt_gui_cpp::Settings &instance_settings)
{
    int seriesCount = instance_settings.value("seriesCount");
    while (seriesCount) {
        seriesCount--;

        PlotLineSeries *series = new PlotLineSeries(this);
        m_chart->addSeries(series);
        //series->setColor(QColor::fr);
    }
}
