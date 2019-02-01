#ifndef RQT_PLOT_QTCHARTS_WIDGET_H
#define RQT_PLOT_QTCHARTS_WIDGET_H

#include "rqt_plot_qtcharts/plotverticalaxis.h"
#include "rqt_plot_qtcharts/dialogaxes.h"

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

private:
    Ui::PlotQtChartsWidget *ui;
    DialogAxes *m_axesDialog;

    QList<PlotVerticalAxis*> m_verticalAxes;

    QMenu *m_seriesMenu;
};

#endif // RQT_PLOT_QTCHARTS_WIDGET_H
