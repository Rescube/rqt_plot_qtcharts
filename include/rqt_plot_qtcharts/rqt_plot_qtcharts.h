#ifndef PLOTQTCHARTS_H
#define PLOTQTCHARTS_H

#include <rqt_gui_cpp/plugin.h>
#include <std_msgs/String.h>

#include <rqt_plot_qtcharts/rqt_plot_qtcharts_widget.h>

namespace rqt_plot_qtcharts {

class PlotQtCharts : public rqt_gui_cpp::Plugin
{
public:
    PlotQtCharts();

    void initPlugin(qt_gui_cpp::PluginContext& context) override;
    void shutdownPlugin() override;

    void saveSettings(qt_gui_cpp::Settings& plugin_settings,
                      qt_gui_cpp::Settings& instance_settings) const override;
    void restoreSettings(const qt_gui_cpp::Settings& plugin_settings,
                         const qt_gui_cpp::Settings& instance_settings) override;

private:
    PlotQtChartsWidget *m_widget = nullptr;
};

}

#endif // PLOTQTCHARTS_H
