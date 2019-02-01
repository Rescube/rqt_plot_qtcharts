#include "rqt_plot_qtcharts/plotchartwidget.h"

#include <rqt_gui_cpp/plugin.h>

#include <QTime>
#include <QVBoxLayout>

#include <QtCharts/QLegendMarker>

QT_CHARTS_USE_NAMESPACE

PlotChartWidget::PlotChartWidget(QWidget *parent) : QWidget(parent)
{
    m_chart = new QChart();
    m_chartView = new ZoomableChartView(m_chart);

    m_axisX = new QValueAxis(this);
    m_axisX->setRange(0, 1000);
    m_axisX->setLabelFormat("%g");
    m_chartView->chart()->setAxisX(m_axisX);

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_chartView);
    setLayout(mainLayout);
}

PlotChartWidget::~PlotChartWidget()
{
    for (auto *axis : m_verticalAxes)
        m_chart->removeAxis(axis);
    delete m_chart;
}

void PlotChartWidget::saveSettings(qt_gui_cpp::Settings &instance_settings) const
{
    saveAxes(instance_settings);
    //saveSeries(instance_settings);
}

void PlotChartWidget::restoreSettings(const qt_gui_cpp::Settings &instance_settings)
{
    restoreAxes(instance_settings);
    //restoreSeries(instance_settings);
}

void PlotChartWidget::addSeries(PlotLineSeries *series)
{
    qsrand(QTime::currentTime().msec());
    for (int i = 0; i<100; i++) {
        series->append(QPointF(i,  qrand() % 400));
    }

    m_series.append(series);
    m_chart->addSeries(series);
    m_chart->setAxisY(series->verticalAxis(), series);
    connectLegendMarkerEvents();
}

void PlotChartWidget::removeSeries(PlotLineSeries *series)
{
    m_series.removeAll(series);
    m_chart->removeSeries(series);
}

void PlotChartWidget::addAxis(PlotVerticalAxis *axis)
{
    m_verticalAxes.append(axis);
    m_chart->addAxis(axis, axis->align());
    connect(axis, &PlotVerticalAxis::alignChanged,
            [axis, this]()
    {
        m_chart->removeAxis(axis);
        m_chart->addAxis(axis, axis->align());
    });
}

QList<PlotVerticalAxis *> PlotChartWidget::verticalAxes() const
{
    return m_verticalAxes;
}

void PlotChartWidget::connectLegendMarkerEvents()
{
    // Connect all markers to handler
    const auto markers = m_chart->legend()->markers();
    for (auto *marker : markers) {
        // Disconnect possible existing connection to avoid multiple connections
        QObject::disconnect(marker, &QLegendMarker::clicked,
                            this, &PlotChartWidget::handleMarkerClicked);
        QObject::connect(marker, &QLegendMarker::clicked, this, &PlotChartWidget::handleMarkerClicked);
    }
}

QList<PlotLineSeries *> PlotChartWidget::seriesList() const
{
    return m_series;
}

void PlotChartWidget::addDefaultAxis()
{
    PlotVerticalAxis *axis = new PlotVerticalAxis(this);
    axis->setName(tr("Default Y axis"));
    axis->setLabel(tr("Y"));
    axis->setRange(0, 1000);
    axis->setVisible();
    axis->setAlign(Qt::AlignLeft);
    addAxis(axis);
}

void PlotChartWidget::handleMarkerClicked()
{
    QLegendMarker* marker = qobject_cast<QLegendMarker*> (sender());
    Q_ASSERT(marker);

    switch (marker->type()) {
    case QLegendMarker::LegendMarkerTypeXY:
        // Toggle visibility of series
        setVisibilityOfMarkerAndSeries(marker, !marker->series()->isVisible());
        break;
    }
}

void PlotChartWidget::setVisibilityOfMarkerAndSeries(QLegendMarker* marker, bool visible)
{
    // Toggle visibility of series
    marker->series()->setVisible(visible);

    // Turn legend marker back to visible, since hiding series also hides the marker
    // and we don't want it to happen now.
    marker->setVisible(true);

    // Dim the marker, if series is not visible
    qreal alpha = 1.0;

    if (!marker->series()->isVisible()) {
        alpha = 0.5;
    }

    QColor color;
    QBrush brush = marker->labelBrush();
    color = brush.color();
    color.setAlphaF(alpha);
    brush.setColor(color);
    marker->setLabelBrush(brush);

    brush = marker->brush();
    color = brush.color();
    color.setAlphaF(alpha);
    brush.setColor(color);
    marker->setBrush(brush);

    QPen pen = marker->pen();
    color = pen.color();
    color.setAlphaF(alpha);
    pen.setColor(color);
    marker->setPen(pen);
}

void PlotChartWidget::restoreAxes(const qt_gui_cpp::Settings &instance_settings)
{
    int axisCount = instance_settings.value("axisCount").toInt();
    for (int index = 0; index < axisCount; index++) {
        PlotVerticalAxis *axis = new PlotVerticalAxis(this);
        axis->setName(instance_settings.value(QString("axes.%1.name").arg(index)).toString());
        axis->setLabel(instance_settings.value(QString("axes.%1.label").arg(index)).toString());
        axis->setVisible(instance_settings.value(QString("axes.%1.visible").arg(index), true).toBool());
        Qt::Alignment align = static_cast<Qt::Alignment>(
                    instance_settings.value(QString("axes.%1.align").arg(index), Qt::AlignLeft).toInt());
        axis->setAlign(align);
        axis->setTickCount(instance_settings.value(QString("axes.%1.tickCount").arg(index), 5).toInt());
        axis->setRange(
                    instance_settings.value(QString("axes.%1.min").arg(index), 0).toDouble(),
                    instance_settings.value(QString("axes.%1.max").arg(index), 1000).toDouble()
                    );
        axis->setAutoScale(instance_settings.value(QString("axes.%1.autoScale").arg(index), true).toBool());
        addAxis(axis);
    }

    if (m_verticalAxes.count() == 0)
        addDefaultAxis();
    connectLegendMarkerEvents();
}

void PlotChartWidget::saveAxes(qt_gui_cpp::Settings &instance_settings) const
{
    instance_settings.setValue("axisCount", m_verticalAxes.count());
    int index = 0;
    for (auto *axis : m_verticalAxes) {
        instance_settings.setValue(QString("axes.%1.name").arg(index),
                                   axis->name());
        instance_settings.setValue(QString("axes.%1.label").arg(index),
                                   axis->label());
        instance_settings.setValue(QString("axes.%1.visible").arg(index),
                                   axis->isVisible());
        instance_settings.setValue(QString("axes.%1.tickCount").arg(index),
                                   axis->tickCount());
        instance_settings.setValue(QString("axes.%1.min").arg(index),
                                   axis->min());
        instance_settings.setValue(QString("axes.%1.max").arg(index),
                                   axis->max());
        instance_settings.setValue(QString("axes.%1.autoScale").arg(index),
                                   axis->autoScale());
        instance_settings.setValue(QString("axes.%1.align").arg(index),
                                   static_cast<int>(axis->align()));
        index++;
    }
}

void PlotChartWidget::restoreSeries(const qt_gui_cpp::Settings &instance_settings)
{
    int seriesCount = instance_settings.value("seriesCount").toInt();
    for (int index = 0; index < seriesCount; index++) {
        PlotLineSeries *series = new PlotLineSeries(this);
        m_chart->addSeries(series);
        series->setDataSource(instance_settings.value(QString("series.%1.dataSource").arg(index)).toString());
    }
}

void PlotChartWidget::saveSeries(qt_gui_cpp::Settings &instance_settings) const
{
    int index = 0;
    instance_settings.setValue("seriesCount", m_series.count());
    for (auto *series : m_series) {
        instance_settings.setValue(QString("series.%1.dataSource").arg(index),
                                   series->dataSource());
        instance_settings.setValue(QString("series.%1.color").arg(index),
                                   series->color());
        instance_settings.setValue(QString("series.%1.width").arg(index),
                                   series->pen().width());
        index++;
    }
}

