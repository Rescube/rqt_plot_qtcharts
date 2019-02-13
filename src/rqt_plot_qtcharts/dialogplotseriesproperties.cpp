#include "dialogplotseriesproperties.h"
#include "ui_dialogplotseriesproperties.h"

#include "verticalaxesmanager.h"

#include <QColorDialog>

DialogPlotSeriesProperties::DialogPlotSeriesProperties(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogPlotSeriesProperties)
{
    ui->setupUi(this);
    updateAxesComboBox();
}

DialogPlotSeriesProperties::~DialogPlotSeriesProperties()
{
    delete ui;
}

PlotLineSeries *DialogPlotSeriesProperties::series() const
{
    return m_series;
}

void DialogPlotSeriesProperties::setSeries(PlotLineSeries *series)
{
    ui->lineEditName->setText(series->name());
    ui->lineEditTopic->setText(series->dataSource());
    ui->doubleSpinBoxWidth->setValue(series->width());
    m_series = series;
    m_color = m_series->color();
    ui->toolButtonSelectColor->setStyleSheet(QString("background-color: %1")
                                             .arg(m_color.name()));
    int index = VerticalAxesManager::instance()->axes().indexOf(series->verticalAxis());
    if (index == -1)
        index = 0;
    ui->comboBoxYAxis->setCurrentIndex(index);
}

void DialogPlotSeriesProperties::updateAxesComboBox()
{
    ui->comboBoxYAxis->clear();
    for (auto *axis : VerticalAxesManager::instance()->axes()) {
        ui->comboBoxYAxis->addItem(axis->name(), axis->getUid());
    }
}

void DialogPlotSeriesProperties::on_toolButtonSelectColor_clicked()
{
    QColor newColor = QColorDialog::getColor(m_color,
                           this,
                           tr("Select series color"));
    if (newColor.isValid()) {
        QPen pen = m_series->pen();
        pen.setColor(newColor);
        m_series->setPen(pen);
        ui->toolButtonSelectColor->setStyleSheet(QString("background-color: %1")
                                                 .arg(newColor.name()));
        m_color = newColor;
    }
}

void DialogPlotSeriesProperties::on_DialogPlotSeriesProperties_accepted()
{
    m_series->setColor(m_color);
    m_series->setDataSource(ui->lineEditTopic->text());
    m_series->setName(ui->lineEditName->text());
    m_series->setWidth(ui->doubleSpinBoxWidth->value());
    m_series->setVerticalAxis(VerticalAxesManager::instance()->axes().at(ui->comboBoxYAxis->currentIndex()));
}
