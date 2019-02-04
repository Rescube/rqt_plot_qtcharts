#ifndef DIALOGSERIES_H
#define DIALOGSERIES_H

#include "dialogplotseriesproperties.h"
#include "serieslistmodel.h"

#include <QDialog>

namespace Ui {
class DialogSeries;
}

class DialogSeries : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSeries(QWidget *parent = 0);
    ~DialogSeries();

private slots:
    void on_tableViewSeries_doubleClicked(const QModelIndex &index);

    void on_tableViewSeries_customContextMenuRequested(const QPoint &pos);

private:
    Ui::DialogSeries *ui;
    SeriesListModel *m_model;
    DialogPlotSeriesProperties *m_seriesPropertiesDialog = nullptr;
};

#endif // DIALOGSERIES_H
