#include "rqt_plot_qtcharts/dialogaxes.h"
#include "ui_dialogaxes.h"

#include "rqt_plot_qtcharts/dialogaxisproperties.h"
#include "rqt_plot_qtcharts/plotlineseries.h"

DialogAxes::DialogAxes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAxes)
{
    ui->setupUi(this);
}

DialogAxes::~DialogAxes()
{
    delete ui;
}

void DialogAxes::on_toolButtonAddAxis_clicked()
{
    PlotVerticalAxis *axis = new PlotVerticalAxis();

    DialogAxisProperties apdlg;
    apdlg.setWindowTitle(tr("Add new axis"));
    if (apdlg.exec() == QDialog::Accepted) {
        //m_plotChartWidget->add
        return;
    }
    delete axis;
}

void DialogAxes::on_toolButtonRemoveAxis_clicked()
{

}
