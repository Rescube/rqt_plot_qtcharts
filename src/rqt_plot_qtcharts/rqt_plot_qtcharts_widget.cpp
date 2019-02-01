#include <rqt_plot_qtcharts/rqt_plot_qtcharts_widget.h>
#include "ui_rqt_plot_qtcharts_widget.h"

#include "rqt_plot_qtcharts/dialogplotseriesproperties.h"
#include "rqt_plot_qtcharts/randomcolorgenerator.h"

PlotQtChartsWidget::PlotQtChartsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlotQtChartsWidget)
{
    ui->setupUi(this);

    m_axesDialog = new DialogAxes(ui->chart, this);
}

PlotQtChartsWidget::~PlotQtChartsWidget()
{
    delete ui;
}

void PlotQtChartsWidget::saveSettings(qt_gui_cpp::Settings &instance_settings) const
{
    ui->chart->saveSettings(instance_settings);
    instance_settings.setValue("lastTopic", ui->lineEditTopic->text());
}

void PlotQtChartsWidget::restoreSettings(const qt_gui_cpp::Settings &instance_settings)
{
    ui->chart->restoreSettings(instance_settings);
    ui->lineEditTopic->setText(instance_settings.value("lastTopic", "/").toString());
    m_axesDialog->refreshAxisList();
}

void PlotQtChartsWidget::on_toolButtonAddTopic_clicked()
{
    auto *newSeries = new PlotLineSeries(this);
    newSeries->setColor(RandomColorGenerator::getInstance()->get());

    DialogPlotSeriesProperties dlg(ui->chart, ui->lineEditTopic->text());
    dlg.setSeries(newSeries);
    dlg.setWindowTitle(tr("Add new series"));
    if (dlg.exec()) {
        ui->chart->addSeries(newSeries);
        ui->toolButtonRemoveTopic->setEnabled(true);
        SeriesRemoveAction *topicRemoveAction = new SeriesRemoveAction(newSeries, this);
        ui->toolButtonRemoveTopic->addAction(topicRemoveAction);
        connect(topicRemoveAction, &SeriesRemoveAction::triggered,
                [=] {
            ui->chart->removeSeries(topicRemoveAction->series());
            ui->toolButtonRemoveTopic->removeAction(topicRemoveAction);
            ui->toolButtonRemoveTopic->setEnabled(ui->toolButtonRemoveTopic->actions().count());
            delete topicRemoveAction;
        });
        return;
    }
    delete newSeries;
}

void PlotQtChartsWidget::on_toolButtonRemoveTopic_clicked()
{
    for (PlotLineSeries *series : ui->chart->seriesList()) {
        if (series->dataSource().startsWith(ui->lineEditTopic->text())) {
            for (QAction *removeAction : ui->toolButtonRemoveTopic->actions()) {
                if (static_cast<SeriesRemoveAction*>(removeAction)->series() == series) {
                    ui->toolButtonRemoveTopic->removeAction(removeAction);
                    delete removeAction;
                    break;
                }
            }
            ui->chart->removeSeries(series);
        }
    }
    ui->toolButtonRemoveTopic->setEnabled(ui->toolButtonRemoveTopic->actions().count());
}

void PlotQtChartsWidget::on_toolButtonSettings_clicked()
{
    m_axesDialog->show();
}

SeriesRemoveAction::SeriesRemoveAction(PlotLineSeries *series, QObject *parent) :
    QAction(series->name(), parent),
    m_series(series)
{

}

PlotLineSeries *SeriesRemoveAction::series() const
{
    return m_series;
}
