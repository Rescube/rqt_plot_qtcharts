#include "serieslistmodel.h"

#include "seriesmanager.h"

SeriesListModel::SeriesListModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    connect(SeriesManager::instance(), &SeriesManager::seriesAdded,
            this, &SeriesListModel::refresh);
    connect(SeriesManager::instance(), &SeriesManager::seriesRemoved,
            this, &SeriesListModel::refresh);
}

int SeriesListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return SeriesManager::instance()->seriesList().count();
}

int SeriesListModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return Col_Invalid;
}

QVariant SeriesListModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        if (index.column() == Col_Name)
            return SeriesManager::instance()->seriesList().at(index.row())->name();
    } else if (role == Qt::CheckStateRole) {
        if (index.column() == Col_Visible)
            return SeriesManager::instance()->seriesList().at(index.row())->isVisible() ? Qt::Checked : Qt::Unchecked;
    }
    return QVariant();
}

bool SeriesListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.column() == Col_Visible && role == Qt::CheckStateRole) {
        SeriesManager::instance()->setSeriesVisible(
                    SeriesManager::instance()->seriesList().at(index.row()),
                    value.toBool());
        return true;
    }
    return false;
}

QVariant SeriesListModel::headerData(int section, Qt::Orientation orientation, int role) const
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

Qt::ItemFlags SeriesListModel::flags(const QModelIndex &index) const
{
    if (index.column() == Col_Visible)
        return Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

PlotLineSeries *SeriesListModel::series(const QModelIndex &index)
{
    if (index.row() < SeriesManager::instance()->seriesList().count())
        return SeriesManager::instance()->seriesList().at(index.row());
    return nullptr;
}

void SeriesListModel::refresh()
{
    beginResetModel();
    endResetModel();
}
