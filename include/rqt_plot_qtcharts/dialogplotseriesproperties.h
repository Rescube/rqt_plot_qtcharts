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
    explicit DialogPlotSeriesProperties(QWidget *parent = 0);
    ~DialogPlotSeriesProperties();

    PlotLineSeries *series() const;
    void setSeries(PlotLineSeries *series);

private:
    Ui::DialogPlotSeriesProperties *ui;

    PlotLineSeries *m_series = nullptr;
};

#endif // DIALOGPLOTSERIESPROPERTIES_H
