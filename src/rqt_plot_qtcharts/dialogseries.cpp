#include "dialogseries.h"
#include "ui_dialogseries.h"

#include "seriesmanager.h"

#include <QMenu>

DialogSeries::DialogSeries(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSeries)
{
    ui->setupUi(this);

    m_model = new SeriesListModel(this);
    ui->tableViewSeries->setModel(m_model);

    ui->tableViewSeries->horizontalHeader()->setSectionResizeMode(SeriesListModel::Col_Name, QHeaderView::Stretch);
    ui->tableViewSeries->horizontalHeader()->setSectionResizeMode(SeriesListModel::Col_Visible, QHeaderView::ResizeToContents);
}

DialogSeries::~DialogSeries()
{
    delete ui;
}

void DialogSeries::on_tableViewSeries_doubleClicked(const QModelIndex &index)
{
    if (!m_seriesPropertiesDialog)
        m_seriesPropertiesDialog = new DialogPlotSeriesProperties(this);
    m_seriesPropertiesDialog->setSeries(m_model->series(index));
    m_seriesPropertiesDialog->exec();
}

void DialogSeries::on_tableViewSeries_customContextMenuRequested(const QPoint &pos)
{
    if (ui->tableViewSeries->selectionModel()->selectedRows(0).isEmpty())
        return;
    QMenu contextMenu;
    contextMenu.addAction(tr("Delete"));

    QAction* selectedAction = contextMenu.exec(ui->tableViewSeries->mapToGlobal(pos));
    if (selectedAction != nullptr) {
        SeriesManager::instance()->removeSeries(
                    m_model->series(ui->tableViewSeries->indexAt(pos)));
    }
}
