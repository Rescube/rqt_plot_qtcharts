#ifndef PLOTVERTICALAXESMODEL_H
#define PLOTVERTICALAXESMODEL_H

#include "verticalaxis.h"

#include <QAbstractTableModel>

class PlotChartWidget;

class VerticalAxesModel : public QAbstractTableModel
{
    Q_OBJECT
public:

    enum Columns {
        Col_Name,
        Col_Visible,
        Col_Invalid
    };

    VerticalAxesModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const;
    VerticalAxis *axis(const QModelIndex & index);

public slots:
    void refresh();
};

#endif // PLOTVERTICALAXESMODEL_H
