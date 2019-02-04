#include <rqt_plot_qtcharts/rqt_plot_qtcharts_widget.h>
#include "ui_rqt_plot_qtcharts_widget.h"

#include "verticalaxesmanager.h"
#include "dialogplotseriesproperties.h"
#include "randomcolorgenerator.h"
#include "seriesmanager.h"

#include <QIcon>
#include <QUuid>

PlotQtChartsWidget::PlotQtChartsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlotQtChartsWidget)
{
    ui->setupUi(this);

    m_axesDialog = new DialogAxes(this);
    m_subscriber = m_nodeHandle.subscribe("/tiva_arm/PIDoutput", 1, &PlotQtChartsWidget::debugCallback, this);

    m_axisX = new QValueAxis(this);
    m_axisX->setRange(0, 300);
    ui->zoomableChartWidget->chart()->addAxis(m_axisX, Qt::AlignBottom);

    connect(SeriesManager::instance(), &SeriesManager::seriesAdded,
            this, &PlotQtChartsWidget::seriesAdded);
    connect(SeriesManager::instance(), &SeriesManager::seriesRemoved,
            this, &PlotQtChartsWidget::seriesRemoved);
    connect(VerticalAxesManager::instance(), &VerticalAxesManager::axisAdded,
            this, &PlotQtChartsWidget::axisAdded);
    connect(VerticalAxesManager::instance(), &VerticalAxesManager::axisRemoved,
            this, &PlotQtChartsWidget::axisRemoved);
}

PlotQtChartsWidget::~PlotQtChartsWidget()
{
    delete ui;
}

void PlotQtChartsWidget::saveSettings(qt_gui_cpp::Settings &instance_settings) const
{
    instance_settings.setValue("lastTopic", ui->lineEditTopic->text());
    saveAxes(instance_settings);
    saveSeries(instance_settings);
}

void PlotQtChartsWidget::restoreSettings(const qt_gui_cpp::Settings &instance_settings)
{
    ui->lineEditTopic->setText(instance_settings.value("lastTopic", "/").toString());
    restoreAxes(instance_settings);
    restoreSeries(instance_settings);
}


void PlotQtChartsWidget::restoreAxes(const qt_gui_cpp::Settings &instance_settings)
{
    int axisCount = instance_settings.value("axisCount").toInt();
    for (int index = 0; index < axisCount; index++) {
        VerticalAxis *axis = new VerticalAxis(this);
        axis->setName(instance_settings.value(QString("axes/%1/name").arg(index)).toString());
        axis->setLabel(instance_settings.value(QString("axes/%1/label").arg(index)).toString());
        axis->setVisible(instance_settings.value(QString("axes/%1/visible").arg(index), true).toBool());
        Qt::Alignment align = static_cast<Qt::Alignment>(
                    instance_settings.value(QString("axes/%1/align").arg(index), Qt::AlignLeft).toInt());
        axis->setAlign(align);
        axis->setTickCount(instance_settings.value(QString("axes/%1/tickCount").arg(index), 5).toInt());
        axis->setRange(
                    instance_settings.value(QString("axes/%1/min").arg(index), 0).toDouble(),
                    instance_settings.value(QString("axes/%1/max").arg(index), 100).toDouble()
                    );
        axis->setRangeMin(instance_settings.value(QString("axes/%1/min").arg(index), 0).toDouble());
        axis->setRangeMax(instance_settings.value(QString("axes/%1/max").arg(index), 100).toDouble());
        axis->setAutoScale(instance_settings.value(QString("axes/%1/autoScale").arg(index), true).toBool());
        axis->setUid(instance_settings.value(QString("axes/%1/uid").arg(index), true).toString());
        VerticalAxesManager::instance()->addAxis(axis);
    }

    if (VerticalAxesManager::instance()->axes().count() == 0)
        addDefaultVerticalAxis();
}

void PlotQtChartsWidget::saveAxes(qt_gui_cpp::Settings &instance_settings) const
{
    instance_settings.remove("axes");
    instance_settings.setValue("axisCount", VerticalAxesManager::instance()->axes().count());
    int index = 0;
    for (auto *axis : VerticalAxesManager::instance()->axes()) {
        instance_settings.setValue(QString("axes/%1/name").arg(index),
                                   axis->name());
        instance_settings.setValue(QString("axes/%1/label").arg(index),
                                   axis->label());
        instance_settings.setValue(QString("axes/%1/visible").arg(index),
                                   axis->isVisible());
        instance_settings.setValue(QString("axes/%1/tickCount").arg(index),
                                   axis->tickCount());
        instance_settings.setValue(QString("axes/%1/min").arg(index),
                                   axis->rangeMin());
        instance_settings.setValue(QString("axes/%1/max").arg(index),
                                   axis->rangeMax());
        instance_settings.setValue(QString("axes/%1/autoScale").arg(index),
                                   axis->autoScale());
        instance_settings.setValue(QString("axes/%1/align").arg(index),
                                   static_cast<int>(axis->align()));
        index++;
    }
}

void PlotQtChartsWidget::restoreSeries(const qt_gui_cpp::Settings &instance_settings)
{
    int seriesCount = instance_settings.value("seriesCount").toInt();
    for (int index = 0; index < seriesCount; index++) {
        PlotLineSeries *series = new PlotLineSeries(this);
        series->setDataSource(instance_settings.value(QString("series/%1/dataSource").arg(index)).toString());
        series->setWidth(instance_settings.value(QString("series/%1/width").arg(index)).toDouble());
        series->setColor(instance_settings.value(QString("series/%1/color").arg(index)).toString());
        series->setVisible(instance_settings.value(QString("series/%1/visible").arg(index)).toBool());
        series->setName(instance_settings.value(QString("series/%1/name").arg(index)).toString());
        series->setVerticalAxis(nullptr);
        QString axisUid = instance_settings.value(QString("series/%1/axisUid").arg(index)).toString();
        for (VerticalAxis *axis : VerticalAxesManager::instance()->axes()) {
            if (axis->getUid() == axisUid) {
                series->setVerticalAxis(axis);
                break;
            }
        }
        SeriesManager::instance()->addSeries(series);
    }
}

void PlotQtChartsWidget::saveSeries(qt_gui_cpp::Settings &instance_settings) const
{
    instance_settings.remove("series");
    int index = 0;
    instance_settings.setValue("seriesCount", SeriesManager::instance()->seriesList().count());
    for (auto *series : SeriesManager::instance()->seriesList()) {
        instance_settings.setValue(QString("series/%1/dataSource").arg(index),
                                   series->dataSource());
        instance_settings.setValue(QString("series/%1/name").arg(index),
                                   series->name());
        instance_settings.setValue(QString("series/%1/color").arg(index),
                                   series->color());
        instance_settings.setValue(QString("series/%1/width").arg(index),
                                   series->pen().width());
        instance_settings.setValue(QString("series/%1/visible").arg(index),
                                   series->isVisible());
        if (series->verticalAxis()) {
            instance_settings.setValue(QString("series/%1/axisUid").arg(index),
                                       series->verticalAxis()->getUid());
        }
        index++;
    }
}

void PlotQtChartsWidget::on_toolButtonAddTopic_clicked()
{
    auto *newSeries = new PlotLineSeries(this);
    newSeries->setColor(RandomColorGenerator::instance()->get());
    newSeries->setDataSource(ui->lineEditTopic->text());
    newSeries->setName(ui->lineEditTopic->text().mid(ui->lineEditTopic->text().lastIndexOf('/')+1));

    DialogPlotSeriesProperties dlg(this);
    dlg.setSeries(newSeries);
    dlg.setWindowTitle(tr("Add new series"));
    if (dlg.exec()) {
        SeriesManager::instance()->addSeries(newSeries);
        return;
    }
    delete newSeries;
}

void PlotQtChartsWidget::on_toolButtonRemoveTopic_clicked()
{
    for (PlotLineSeries *series : SeriesManager::instance()->seriesList()) {
        if (series->dataSource().startsWith(ui->lineEditTopic->text())) {
            for (QAction *removeAction : ui->toolButtonRemoveTopic->actions()) {
                if (static_cast<SeriesRemoveAction*>(removeAction)->series() == series) {
                    ui->toolButtonRemoveTopic->removeAction(removeAction);
                    delete removeAction;
                    break;
                }
            }
            SeriesManager::instance()->removeSeries(series);
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

void PlotQtChartsWidget::on_toolButtonSeries_clicked()
{
    if (!m_seriesDialog)
        m_seriesDialog = new DialogSeries(this);
    m_seriesDialog->show();
}

void PlotQtChartsWidget::on_toolButtonRecord_toggled(bool checked)
{
}

void PlotQtChartsWidget::on_toolButtonClear_clicked()
{
    SeriesManager::instance()->clear();
}

void PlotQtChartsWidget::seriesAdded(PlotLineSeries *newSeries)
{
    ui->toolButtonRemoveTopic->setEnabled(true);
    SeriesRemoveAction *topicRemoveAction = new SeriesRemoveAction(newSeries, this);
    ui->toolButtonRemoveTopic->addAction(topicRemoveAction);
    connect(topicRemoveAction, &SeriesRemoveAction::triggered,
            [=] {
        SeriesManager::instance()->removeSeries(topicRemoveAction->series());
        ui->toolButtonRemoveTopic->removeAction(topicRemoveAction);
        ui->toolButtonRemoveTopic->setEnabled(ui->toolButtonRemoveTopic->actions().count());
        delete topicRemoveAction;
    });
}

void PlotQtChartsWidget::seriesRemoved(PlotLineSeries *series)
{
    for (QAction *action : ui->toolButtonRemoveTopic->actions()) {
        SeriesRemoveAction *rmAction = static_cast<SeriesRemoveAction*>(action);
        if (rmAction->series() == series)
            ui->toolButtonRemoveTopic->removeAction(action);
        delete action;
    }
}

void PlotQtChartsWidget::axisAdded(VerticalAxis *axis)
{
    ui->zoomableChartWidget->chart()->addAxis(axis, axis->align());
}

void PlotQtChartsWidget::axisRemoved(VerticalAxis *axis)
{
    ui->zoomableChartWidget->chart()->removeAxis(axis);
}

void PlotQtChartsWidget::debugCallback(const rescube_msgs::PIDDebug::ConstPtr &dbg)
{
    for (PlotLineSeries *series : SeriesManager::instance()->seriesList()) {
        if (series->dataSource() == "/tiva_arm/PIDoutput/currentSpeed") {
            series->dataReceived(dbg.get()->currentSpeed);
        }
        if (series->dataSource() == "/tiva_arm/PIDoutput/currentSpeedFiltered")
            series->dataReceived(dbg.get()->currentSpeedFiltered);
        if (series->dataSource() == "/tiva_arm/PIDoutput/speedError")
            series->dataReceived(dbg.get()->speedError);
        if (series->dataSource() == "/tiva_arm/PIDoutput/outputP")
            series->dataReceived(dbg.get()->outputP);
        if (series->dataSource() == "/tiva_arm/PIDoutput/outputI")
            series->dataReceived(dbg.get()->outputI);
        if (series->dataSource() == "/tiva_arm/PIDoutput/outputD")
            series->dataReceived(dbg.get()->outputD);
        if (series->dataSource() == "/tiva_arm/PIDoutput/outputPID")
            series->dataReceived(dbg.get()->outputPID);
        if (series->dataSource() == "/tiva_arm/PIDoutput/outputAfterScale")
            series->dataReceived(dbg.get()->outputAfterScale);
    }
}

void PlotQtChartsWidget::addDefaultVerticalAxis()
{
    VerticalAxis *axis = new VerticalAxis(this);
    axis->setUid(QUuid::createUuid().toString());
    axis->setName(tr("Default Y axis"));
    axis->setLabel(tr("Y"));
    axis->setRange(0, 1000);
    axis->setVisible();
    axis->setAlign(Qt::AlignLeft);
    VerticalAxesManager::instance()->addAxis(axis);
}
