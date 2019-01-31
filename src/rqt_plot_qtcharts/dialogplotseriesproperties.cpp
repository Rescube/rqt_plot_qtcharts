#include "rqt_plot_qtcharts/dialogplotseriesproperties.h"
#include "ui_dialogplotseriesproperties.h"

DialogPlotSeriesProperties::DialogPlotSeriesProperties(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogPlotSeriesProperties)
{
    ui->setupUi(this);
}

DialogPlotSeriesProperties::~DialogPlotSeriesProperties()
{
    delete ui;
}

PlotLineSeries *DialogPlotSeriesProperties::series() const
{
    return m_series;
}

void DialogPlotSeriesProperties::setSeries(PlotLineSeries *series)
{
    m_series = series;
}
