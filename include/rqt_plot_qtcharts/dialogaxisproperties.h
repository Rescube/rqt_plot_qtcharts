#ifndef DIALOGAXISPROPERTIES_H
#define DIALOGAXISPROPERTIES_H

#include "plotverticalaxis.h"

#include <QDialog>

namespace Ui {
class DialogAxisProperties;
}

class DialogAxisProperties : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAxisProperties(QWidget *parent = 0);
    ~DialogAxisProperties();

    PlotLineSeries *series() const;
    void setSeries(PlotLineSeries *series);

private slots:

    void on_checkBoxAutoScale_toggled(bool checked);

private:
    Ui::DialogAxisProperties *ui;
    PlotVerticalAxis *m_axis = nullptr;
};

#endif // DIALOGAXISPROPERTIES_H
