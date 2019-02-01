#ifndef DIALOGAXES_H
#define DIALOGAXES_H

#include "rqt_plot_qtcharts/plotverticalaxesmodel.h"

#include <QDialog>

namespace Ui {
class DialogAxes;
}

class DialogAxes : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAxes(PlotChartWidget *plotWidget, QWidget *parent = 0);
    ~DialogAxes();
    void refreshAxisList();

private slots:
    void on_toolButtonAddAxis_clicked();
    void on_toolButtonRemoveAxis_clicked();
    void on_tableViewAxesList_doubleClicked(const QModelIndex &index);

private:
    Ui::DialogAxes *ui;
    PlotVerticalAxesModel *m_model;
    PlotChartWidget *m_plotChartWidget;
};

#endif // DIALOGAXES_H
