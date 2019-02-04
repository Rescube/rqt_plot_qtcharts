#ifndef ZOOMABLECHARTWIDGET_H
#define ZOOMABLECHARTWIDGET_H

#include <QRubberBand>
#include <QWidget>

#include <QtCharts/QChart>

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

private slots:
    void on_comboBoxZoomMode_activated(int index);
    void legendMarkerClicked();

private:
    Ui::ZoomableChartWidget *ui;
    QChart *m_chart = nullptr;
};

#endif // ZOOMABLECHARTWIDGET_H
