#ifndef RQT_PLOT_QTCHARTS_WIDGET_H
#define RQT_PLOT_QTCHARTS_WIDGET_H

#include "rqt_plot_qtcharts/plotverticalaxis.h"
#include "rqt_plot_qtcharts/dialogaxes.h"

#include <ros/master.h>


#include <QWidget>

namespace Ui {
class PlotQtChartsWidget;
}

class PlotQtChartsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PlotQtChartsWidget(QWidget *parent = nullptr);
    ~PlotQtChartsWidget();

    void saveSettings(qt_gui_cpp::Settings& plugin_settings, qt_gui_cpp::Settings& instance_settings) const override;
    void restoreSettings(const qt_gui_cpp::Settings& plugin_settings, const qt_gui_cpp::Settings& instance_settings) override;

private slots:
    void on_toolButtonAddTopic_clicked();
    void on_toolButtonRemoveTopic_clicked();
    void on_toolButtonSettings_clicked();

private:
    Ui::PlotQtChartsWidget *ui;
    DialogAxes *m_axesDialog;

    QList<PlotVerticalAxis*> m_verticalAxes;
};

#endif // RQT_PLOT_QTCHARTS_WIDGET_H
