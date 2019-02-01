#include <rqt_plot_qtcharts/rqt_plot_qtcharts.h>

#include <pluginlib/class_list_macros.h>
#include <ros/master.h>

namespace rqt_plot_qtcharts {


PlotQtCharts::PlotQtCharts() :
    rqt_gui_cpp::Plugin()
{
    setObjectName("PlotQtCharts");
}

void PlotQtCharts::initPlugin(qt_gui_cpp::PluginContext &context)
{
    m_widget = new PlotQtChartsWidget();
    context.addWidget(m_widget);
}

void PlotQtCharts::shutdownPlugin()
{

}

void PlotQtCharts::saveSettings(qt_gui_cpp::Settings &plugin_settings, qt_gui_cpp::Settings &instance_settings) const
{
    Q_UNUSED(plugin_settings);
    if (m_widget) {
        m_widget->saveSettings(instance_settings);
    }
}

void PlotQtCharts::restoreSettings(const qt_gui_cpp::Settings &plugin_settings, const qt_gui_cpp::Settings &instance_settings)
{
    Q_UNUSED(plugin_settings);
    if (m_widget) {
        m_widget->restoreSettings(instance_settings);
    }
}

} // end namespace

PLUGINLIB_EXPORT_CLASS(rqt_plot_qtcharts::PlotQtCharts, rqt_gui_cpp::Plugin)
