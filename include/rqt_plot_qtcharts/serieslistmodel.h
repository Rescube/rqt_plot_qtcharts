#ifndef SERIESLISTMODEL_H
#define SERIESLISTMODEL_H

#include "plotlineseries.h"

#include <QAbstractTableModel>

class SeriesListModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum Columns {
        Col_Name,
        Col_Visible,
        Col_Invalid
    };

    SeriesListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const;

    PlotLineSeries *series(const QModelIndex& index);

public slots:
    void refresh();
};

#endif // SERIESLISTMODEL_H
