#ifndef DIALOGPLOTSERIESPROPERTIES_H
#define DIALOGPLOTSERIESPROPERTIES_H

#include "plotlineseries.h"

#include <QCloseEvent>
#include <QDialog>

#include <rqt_gui_cpp/plugin.h>

namespace Ui {
class DialogPlotSeriesProperties;
}

class DialogPlotSeriesProperties : public QDialog
{
    Q_OBJECT

public:
    DialogPlotSeriesProperties(QWidget *parent = 0);
    ~DialogPlotSeriesProperties();

    void saveSettings(qt_gui_cpp::Settings& instance_settings) const;
    void restoreSettings(const qt_gui_cpp::Settings& instance_settings);

    PlotLineSeries *series() const;
    void setSeries(PlotLineSeries *series);

    void updateAxesComboBox();

    QByteArray geometry() const;
    void setGeometry(const QByteArray &geometry);

private slots:
    void on_toolButtonSelectColor_clicked();
    void on_DialogPlotSeriesProperties_accepted();

private:
    Ui::DialogPlotSeriesProperties *ui;

    PlotLineSeries *m_series = nullptr;
    QColor m_color = Qt::red;
    QByteArray m_geometry;
};

#endif // DIALOGPLOTSERIESPROPERTIES_H
