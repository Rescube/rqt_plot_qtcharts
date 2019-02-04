#ifndef DIALOGPLOTSERIESPROPERTIES_H
#define DIALOGPLOTSERIESPROPERTIES_H

#include "plotlineseries.h"

#include <QDialog>

namespace Ui {
class DialogPlotSeriesProperties;
}

class DialogPlotSeriesProperties : public QDialog
{
    Q_OBJECT

public:
    DialogPlotSeriesProperties(QWidget *parent = 0);
    ~DialogPlotSeriesProperties();

    PlotLineSeries *series() const;
    void setSeries(PlotLineSeries *series);

    void updateAxesComboBox();

private slots:
    void on_toolButtonSelectColor_clicked();
    void on_DialogPlotSeriesProperties_accepted();

private:
    Ui::DialogPlotSeriesProperties *ui;

    PlotLineSeries *m_series = nullptr;
    QColor m_color = Qt::red;
};

#endif // DIALOGPLOTSERIESPROPERTIES_H
