#include <rqt_plot_qtcharts/rqt_plot_qtcharts_widget.h>
#include "ui_rqt_plot_qtcharts_widget.h"

PlotQtChartsWidget::PlotQtChartsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlotQtChartsWidget)
{
    ui->setupUi(this);

    m_axesDialog = new DialogAxes(this);
}

PlotQtChartsWidget::~PlotQtChartsWidget()
{
    delete ui;
}

void PlotQtChartsWidget::saveSettings(qt_gui_cpp::Settings &instance_settings) const
{
    ui->chart->saveSettings(instance_settings);
}

void PlotQtChartsWidget::restoreSettings(const qt_gui_cpp::Settings &instance_settings)
{
    ui->chart->restoreSettings(instance_settings);
}

void PlotQtChartsWidget::on_toolButtonAddTopic_clicked()
{

}

void PlotQtChartsWidget::on_toolButtonRemoveTopic_clicked()
{

}

void PlotQtChartsWidget::on_toolButtonSettings_clicked()
{
    m_axesDialog->show();
}
