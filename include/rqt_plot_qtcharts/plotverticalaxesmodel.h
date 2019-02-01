#ifndef PLOTVERTICALAXESMODEL_H
#define PLOTVERTICALAXESMODEL_H

#include "plotchartwidget.h"

#include <QAbstractTableModel>

class PlotChartWidget;

class PlotVerticalAxesModel : public QAbstractTableModel
{
public:

    enum Columns {
        Col_Name,
        Col_Visible,
        Col_Invalid
    };

    PlotVerticalAxesModel(PlotChartWidget *widget, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const;

    void refresh();
    PlotVerticalAxis *axis(const QModelIndex & index);

private:
    PlotChartWidget *m_chartWidget;
};

#endif // PLOTVERTICALAXESMODEL_H
