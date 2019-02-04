#ifndef RQT_PLOT_QTCHARTS_WIDGET_H
#define RQT_PLOT_QTCHARTS_WIDGET_H

#include "verticalaxis.h"
#include "dialogaxes.h"
#include "dialogseries.h"

#include <rescube_msgs/PIDDebug.h>

#include <ros/node_handle.h>
#include <ros/subscriber.h>

#include <rqt_gui_cpp/plugin.h>

#include <QAction>
#include <QWidget>

namespace Ui {
class PlotQtChartsWidget;
}

class SeriesRemoveAction : public QAction
{
    Q_OBJECT
public:
    SeriesRemoveAction(PlotLineSeries *series, QObject *parent = nullptr);

    PlotLineSeries *series() const;

private:
    PlotLineSeries *m_series;
};

class PlotQtChartsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PlotQtChartsWidget(QWidget *parent = nullptr);
    ~PlotQtChartsWidget();

    void saveSettings(qt_gui_cpp::Settings& instance_settings) const;
    void restoreSettings(const qt_gui_cpp::Settings& instance_settings);

private slots:
    void on_toolButtonAddTopic_clicked();
    void on_toolButtonRemoveTopic_clicked();
    void on_toolButtonSettings_clicked();
    void on_toolButtonSeries_clicked();
    void on_toolButtonRecord_toggled(bool checked);
    void on_toolButtonClear_clicked();

    void seriesAdded(PlotLineSeries *newSeries);
    void seriesRemoved(PlotLineSeries *series);

    void axisAdded(VerticalAxis *axis);
    void axisRemoved(VerticalAxis *axis);

private:
    Ui::PlotQtChartsWidget *ui;
    DialogAxes *m_axesDialog = nullptr;
    DialogSeries *m_seriesDialog = nullptr;

    QValueAxis *m_axisX = nullptr;

    ros::Subscriber m_subscriber;
    ros::NodeHandle m_nodeHandle;

    void saveAxes(qt_gui_cpp::Settings &instance_settings) const;
    void saveSeries(qt_gui_cpp::Settings &instance_settings) const;
    void restoreAxes(const qt_gui_cpp::Settings &instance_settings);
    void restoreSeries(const qt_gui_cpp::Settings &instance_settings);

    void debugCallback(const rescube_msgs::PIDDebug::ConstPtr &dbg);

    void addDefaultVerticalAxis();
};

#endif // RQT_PLOT_QTCHARTS_WIDGET_H
