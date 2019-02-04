#ifndef DIALOGAXISPROPERTIES_H
#define DIALOGAXISPROPERTIES_H

#include "verticalaxis.h"
#include "plotlineseries.h"

#include <QDialog>
#include <QShowEvent>

namespace Ui {
class DialogAxisProperties;
}

class DialogAxisProperties : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAxisProperties(QWidget *parent = 0);
    ~DialogAxisProperties();

    void showEvent(QShowEvent *event);

    PlotLineSeries *series() const;
    void setSeries(PlotLineSeries *series);

    VerticalAxis *axis() const;
    void setAxis(VerticalAxis *axis);

private slots:
    void on_checkBoxAutoScale_toggled(bool checked);
    void on_pushButtonAddSeries_clicked();
    void on_buttonBox_accepted();

private:
    Ui::DialogAxisProperties *ui;
    VerticalAxis *m_axis = nullptr;
};

#endif // DIALOGAXISPROPERTIES_H
