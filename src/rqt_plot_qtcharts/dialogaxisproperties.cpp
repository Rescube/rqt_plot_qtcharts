#include "rqt_plot_qtcharts/dialogaxisproperties.h"
#include "ui_dialogaxisproperties.h"

DialogAxisProperties::DialogAxisProperties(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAxisProperties)
{
    ui->setupUi(this);
}

DialogAxisProperties::~DialogAxisProperties()
{
    delete ui;
}


void DialogAxisProperties::on_checkBoxAutoScale_toggled(bool checked)
{
    ui->doubleSpinBoxRangeMin->setEnabled(!checked);
    ui->doubleSpinBoxRangeMax->setEnabled(!checked);

    if (checked) {
        // TODO set the current min max of the axis to the spinBoxes
    }
}

