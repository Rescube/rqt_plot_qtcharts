#ifndef ZOOMABLECHARTWIDGET_H
#define ZOOMABLECHARTWIDGET_H

#include <QRubberBand>
#include <QWidget>

#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class ZoomableChartWidget;
}

class ZoomableChartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ZoomableChartWidget(QWidget *parent = 0);
    ~ZoomableChartWidget();
    void connectLegendMarkerEvents();

    QChart *chart() const;
public slots:
    void setSeriesVisible(QAbstractSeries *series, bool visible = true);

private slots:
    void on_comboBoxZoomMode_activated(int index);
    void legendMarkerClicked();

private:
    Ui::ZoomableChartWidget *ui;
    QChart *m_chart = nullptr;
};

#endif // ZOOMABLECHARTWIDGET_H
