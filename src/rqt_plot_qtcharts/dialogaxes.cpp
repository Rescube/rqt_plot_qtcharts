#include "dialogaxes.h"
#include "ui_dialogaxes.h"

#include "dialogaxisproperties.h"
#include "plotlineseries.h"
#include "seriesmanager.h"
#include "verticalaxesmanager.h"

#include <QMenu>
#include <QUuid>

DialogAxes::DialogAxes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAxes)
{
    ui->setupUi(this);

    m_model = new VerticalAxesModel(this);
    ui->tableViewAxesList->setModel(m_model);
    ui->tableViewAxesList->horizontalHeader()->setSectionResizeMode(VerticalAxesModel::Col_Name, QHeaderView::Stretch);
    ui->tableViewAxesList->horizontalHeader()->setSectionResizeMode(VerticalAxesModel::Col_Visible, QHeaderView::ResizeToContents);
}

DialogAxes::~DialogAxes()
{
    delete ui;
}

void DialogAxes::refreshAxisList()
{
    m_model->refresh();
    ui->tableViewAxesList->horizontalHeader()->setSectionResizeMode(VerticalAxesModel::Col_Name, QHeaderView::Stretch);
    ui->tableViewAxesList->horizontalHeader()->setSectionResizeMode(VerticalAxesModel::Col_Visible, QHeaderView::ResizeToContents);
}

void DialogAxes::on_toolButtonAddAxis_clicked()
{
    VerticalAxis *axis = new VerticalAxis();
    axis->setUid(QUuid::createUuid().toString());
    DialogAxisProperties apdlg;
    apdlg.setAxis(axis);
    apdlg.setWindowTitle(tr("Add new axis"));
    if (apdlg.exec() == QDialog::Accepted) {
        VerticalAxesManager::instance()->addAxis(axis);
        return;
    }
    delete axis;
}

void DialogAxes::on_toolButtonRemoveAxis_clicked()
{
    if (ui->tableViewAxesList->selectionModel()->selectedRows(0).isEmpty())
        return;

    for (const QModelIndex & index : ui->tableViewAxesList->selectionModel()->selectedRows(0)) {
        VerticalAxesManager::instance()->removeAxis(m_model->axis(index));
    }
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

void DialogAxes::on_tableViewAxesList_customContextMenuRequested(const QPoint &pos)
{
    if (ui->tableViewAxesList->selectionModel()->selectedRows(0).isEmpty())
        return;
    QMenu contextMenu;
    contextMenu.addAction(tr("Delete"));

    QAction* selectedAction = contextMenu.exec(ui->tableViewAxesList->mapToGlobal(pos));
    if (selectedAction != nullptr) {
        VerticalAxesManager::instance()->removeAxis(
                    m_model->axis(ui->tableViewAxesList->indexAt(pos)));
    }
}
