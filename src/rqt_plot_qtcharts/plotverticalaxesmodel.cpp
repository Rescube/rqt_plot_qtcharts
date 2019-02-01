#include "rqt_plot_qtcharts/plotverticalaxesmodel.h"

PlotVerticalAxesModel::PlotVerticalAxesModel(PlotChartWidget *widget, QObject *parent) :
    QAbstractTableModel(parent),
    m_chartWidget(widget)
{

}

int PlotVerticalAxesModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_chartWidget->m_verticalAxes.count();
}

int PlotVerticalAxesModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return Col_Invalid;
}

QVariant PlotVerticalAxesModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        if (index.column() == Col_Name)
            return m_chartWidget->m_verticalAxes.at(index.row())->name();
    } else if (role == Qt::CheckStateRole) {
        if (index.column() == Col_Visible)
            return m_chartWidget->m_verticalAxes.at(index.row())->isVisible() ? Qt::Checked : Qt::Unchecked;
    }
    return QVariant();
}

bool PlotVerticalAxesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.column() == Col_Visible && role == Qt::CheckStateRole) {
        axis(index)->setVisible(value.toBool());
        return true;
    }
    return false;
}

QVariant PlotVerticalAxesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
            case 0:
                return tr("Name");
            case 1:
                return tr("Visible");
            }
        }
    }
    return QVariant();
}

Qt::ItemFlags PlotVerticalAxesModel::flags(const QModelIndex &index) const
{
    if (index.column() == Col_Visible)
        return Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsEditable;

    return Qt::ItemIsEnabled;
}

void PlotVerticalAxesModel::refresh()
{
    beginResetModel();
    endResetModel();
}

PlotVerticalAxis *PlotVerticalAxesModel::axis(const QModelIndex &index)
{
    if (index.isValid()) {
        if (index.row() < m_chartWidget->m_verticalAxes.count())
            return m_chartWidget->m_verticalAxes.at(index.row());
    }
    return nullptr;
}
