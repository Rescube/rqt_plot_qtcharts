#include "dialogaxisproperties.h"
#include "ui_dialogaxisproperties.h"

DialogAxisProperties::DialogAxisProperties(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAxisProperties)
{
    ui->setupUi(this);
    ui->comboBoxAlignment->setItemData(0, Qt::AlignLeft);
    ui->comboBoxAlignment->setItemData(1, Qt::AlignRight);
}

DialogAxisProperties::~DialogAxisProperties()
{
    delete ui;
}

void DialogAxisProperties::showEvent(QShowEvent *event)
{
    ui->lineEditAxisName->setFocus();
    QDialog::showEvent(event);
}


void DialogAxisProperties::on_checkBoxAutoScale_toggled(bool checked)
{
    ui->doubleSpinBoxRangeMin->setEnabled(!checked);
    ui->doubleSpinBoxRangeMax->setEnabled(!checked);

    if (checked) {
        // TODO set the current min max of the axis to the spinBoxes
    }
}

VerticalAxis *DialogAxisProperties::axis() const
{
    return m_axis;
}

void DialogAxisProperties::setAxis(VerticalAxis *axis)
{
    m_axis = axis;

    ui->lineEditAxisLabel->setText(m_axis->label());
    ui->lineEditAxisName->setText(m_axis->name());

    ui->spinBoxTickCount->setValue(m_axis->tickCount());
    ui->doubleSpinBoxRangeMin->setValue(m_axis->rangeMin());
    ui->doubleSpinBoxRangeMax->setValue(m_axis->rangeMax());
    ui->checkBoxAxisLabelVisible->setChecked(m_axis->isVisible());

    if (m_axis->align() == Qt::AlignRight) {
        ui->comboBoxAlignment->setCurrentIndex(1);
    } else {
        ui->comboBoxAlignment->setCurrentIndex(0);
    }
}

void DialogAxisProperties::on_pushButtonAddSeries_clicked()
{

}

void DialogAxisProperties::on_buttonBox_accepted()
{
    m_axis->setName(ui->lineEditAxisName->text());
    m_axis->setLabel(ui->lineEditAxisLabel->text());
    m_axis->setAutoScale(ui->checkBoxAutoScale->isChecked());
    m_axis->setTickCount(ui->spinBoxTickCount->value());
    m_axis->setRangeMin(ui->doubleSpinBoxRangeMin->value());
    m_axis->setRangeMax(ui->doubleSpinBoxRangeMax->value());
    if (!ui->checkBoxAutoScale->isChecked()) {
        m_axis->setRange(ui->doubleSpinBoxRangeMin->value(),
                         ui->doubleSpinBoxRangeMax->value());
    }
    m_axis->setAlign(static_cast<Qt::Alignment>(ui->comboBoxAlignment->currentData().toInt()));
}
