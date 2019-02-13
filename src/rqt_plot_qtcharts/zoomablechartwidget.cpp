#include "zoomablechartwidget.h"
#include "ui_zoomablechartwidget.h"

#include <QtCharts/QLegendMarker>

QT_CHARTS_USE_NAMESPACE


ZoomableChartWidget::ZoomableChartWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZoomableChartWidget)
{
    ui->setupUi(this);

    QIcon panIcon;
    panIcon.addFile(QStringLiteral(":/icons/pan.png"), QSize(), QIcon::Normal, QIcon::Off);
    ui->comboBoxZoomMode->addItem(panIcon, QString(""), ZoomableChartView::Pan);

    QIcon rectZoomIcon;
    rectZoomIcon.addFile(QStringLiteral(":/icons/rectangle_zoom.png"), QSize(), QIcon::Normal, QIcon::Off);
    ui->comboBoxZoomMode->addItem(rectZoomIcon, QString(""), ZoomableChartView::RectangleZoom);

    QIcon vZoomIcon;
    vZoomIcon.addFile(QStringLiteral(":/icons/vertical_zoom.png"), QSize(), QIcon::Normal, QIcon::Off);
    ui->comboBoxZoomMode->addItem(vZoomIcon, QString(""), ZoomableChartView::VerticalZoom);

    QIcon hZoomIcon;
    hZoomIcon.addFile(QStringLiteral(":/icons/horizontal_zoom.png"), QSize(), QIcon::Normal, QIcon::Off);
    ui->comboBoxZoomMode->addItem(hZoomIcon, QString(""), ZoomableChartView::HorizontalZoom);

    ui->chartView->setZoomMode(ZoomableChartView::Pan);

    m_chart = new QChart();
    ui->chartView->setChart(m_chart);
}

ZoomableChartWidget::~ZoomableChartWidget()
{
    delete m_chart;
    delete ui;
}

void ZoomableChartWidget::on_comboBoxZoomMode_activated(int index)
{
    ui->chartView->setZoomMode(static_cast<ZoomableChartView::ZoomMode>(ui->comboBoxZoomMode->itemData(index).toInt()));
}

void ZoomableChartWidget::legendMarkerClicked()
{
    auto* marker = qobject_cast<QLegendMarker*>(sender());
    Q_ASSERT(marker);

    switch (marker->type()) {
    case QLegendMarker::LegendMarkerTypeXY:
        // Toggle visibility of series
        marker->series()->setVisible(!marker->series()->isVisible());

        // Turn legend marker back to visible, since hiding series also hides the marker
        // and we don't want it to happen now.
        marker->setVisible(true);

        // Dim the marker, if series is not visible
        qreal alpha = marker->series()->isVisible() ? 1.0 : 0.5;
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
        break;
    }
}

QChart *ZoomableChartWidget::chart() const
{
    return m_chart;
}

// FIXME sublclass QChart emit a signal when series is added
void ZoomableChartWidget::connectLegendMarkerEvents()
{
    // Connect all markers to handler
    const auto markers = m_chart->legend()->markers();
    for (auto *marker : markers) {
        // Disconnect possible existing connection to avoid multiple connections
        QObject::disconnect(marker, &QLegendMarker::clicked,
                            this, &ZoomableChartWidget::legendMarkerClicked);
        QObject::connect(marker, &QLegendMarker::clicked,
                         this, &ZoomableChartWidget::legendMarkerClicked);
    }
}

