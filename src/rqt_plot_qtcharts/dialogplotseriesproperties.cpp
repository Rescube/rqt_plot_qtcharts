#include "rqt_plot_qtcharts/dialogplotseriesproperties.h"
#include "ui_dialogplotseriesproperties.h"

#include <QColorDialog>

DialogPlotSeriesProperties::DialogPlotSeriesProperties(PlotChartWidget *chart, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogPlotSeriesProperties),
    m_plotChartWidget(chart)
{
    ui->setupUi(this);
    updateAxesComboBox();
}

DialogPlotSeriesProperties::DialogPlotSeriesProperties(PlotChartWidget *chart, const QString &topicName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogPlotSeriesProperties),
    m_plotChartWidget(chart)
{
    ui->setupUi(this);
    ui->lineEditTopic->setText(topicName);
    ui->lineEditName->setText(topicName.mid(topicName.lastIndexOf('/')+1));
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
    m_series = series;
    m_color = m_series->color();
    ui->toolButtonSelectColor->setStyleSheet(QString("background-color: %1")
                                             .arg(m_color.name()));
}

void DialogPlotSeriesProperties::updateAxesComboBox()
{
    ui->comboBoxYAxis->clear();
    for (auto *axis : m_plotChartWidget->verticalAxes()) {
        ui->comboBoxYAxis->addItem(axis->name());
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
    m_series->setVerticalAxis(m_plotChartWidget->verticalAxes().at(ui->comboBoxYAxis->currentIndex()));
}
