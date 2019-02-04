#include "verticalaxesmodel.h"

#include "verticalaxesmanager.h"

VerticalAxesModel::VerticalAxesModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    connect(VerticalAxesManager::instance(), &VerticalAxesManager::axisAdded,
            this, &VerticalAxesModel::refresh);
    connect(VerticalAxesManager::instance(), &VerticalAxesManager::axisRemoved,
            this, &VerticalAxesModel::refresh);
}

int VerticalAxesModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return VerticalAxesManager::instance()->axes().count();
}

int VerticalAxesModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return Col_Invalid;
}

QVariant VerticalAxesModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        if (index.column() == Col_Name)
            return VerticalAxesManager::instance()->axes().at(index.row())->name();
    } else if (role == Qt::CheckStateRole) {
        if (index.column() == Col_Visible)
            return VerticalAxesManager::instance()->axes().at(index.row())->isVisible() ? Qt::Checked : Qt::Unchecked;
    }
    return QVariant();
}

bool VerticalAxesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.column() == Col_Visible && role == Qt::CheckStateRole) {
        axis(index)->setVisible(value.toBool());
        return true;
    }
    return false;
}

QVariant VerticalAxesModel::headerData(int section, Qt::Orientation orientation, int role) const
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

Qt::ItemFlags VerticalAxesModel::flags(const QModelIndex &index) const
{
    if (index.column() == Col_Visible)
        return Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

void VerticalAxesModel::refresh()
{
    beginResetModel();
    endResetModel();
}

VerticalAxis *VerticalAxesModel::axis(const QModelIndex &index)
{
    if (index.isValid()) {
        if (index.row() < VerticalAxesManager::instance()->axes().count())
            return VerticalAxesManager::instance()->axes().at(index.row());
    }
    return nullptr;
}
