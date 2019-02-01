#include "rqt_plot_qtcharts/dialogaxes.h"
#include "ui_dialogaxes.h"

#include "rqt_plot_qtcharts/dialogaxisproperties.h"
#include "rqt_plot_qtcharts/plotlineseries.h"

DialogAxes::DialogAxes(PlotChartWidget *plotWidget, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAxes),
    m_plotChartWidget(plotWidget)
{
    ui->setupUi(this);

    m_model = new PlotVerticalAxesModel(plotWidget, this);
    ui->tableViewAxesList->setModel(m_model);
}

DialogAxes::~DialogAxes()
{
    delete ui;
}

void DialogAxes::refreshAxisList()
{
    m_model->refresh();
    ui->tableViewAxesList->horizontalHeader()->setSectionResizeMode(PlotVerticalAxesModel::Col_Name, QHeaderView::Stretch);
    ui->tableViewAxesList->horizontalHeader()->setSectionResizeMode(PlotVerticalAxesModel::Col_Visible, QHeaderView::ResizeToContents);
}

void DialogAxes::on_toolButtonAddAxis_clicked()
{
    PlotVerticalAxis *axis = new PlotVerticalAxis();
    DialogAxisProperties apdlg;
    apdlg.setAxis(axis);
    apdlg.setWindowTitle(tr("Add new axis"));
    if (apdlg.exec() == QDialog::Accepted) {
        m_plotChartWidget->addAxis(axis);
        return;
    }
    delete axis;
}

void DialogAxes::on_toolButtonRemoveAxis_clicked()
{

}

void DialogAxes::on_tableViewAxesList_doubleClicked(const QModelIndex &index)
{
    DialogAxisProperties apdlg;
    apdlg.setWindowTitle(tr("Edit %1 axis").arg(m_model->axis(index)->name()));
    apdlg.setAxis(m_model->axis(index));
    if (apdlg.exec() == QDialog::Accepted) {
        refreshAxisList();
    }
}
