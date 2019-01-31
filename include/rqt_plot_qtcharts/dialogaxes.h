#ifndef DIALOGAXES_H
#define DIALOGAXES_H

#include "plotchartwidget.h"

#include <QDialog>

namespace Ui {
class DialogAxes;
}

class DialogAxes : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAxes(QWidget *parent = 0);
    ~DialogAxes();

private slots:
    void on_toolButtonAddAxis_clicked();

    void on_toolButtonRemoveAxis_clicked();

private:
    Ui::DialogAxes *ui;
    PlotChartWidget *m_plotChartWidget;
};

#endif // DIALOGAXES_H
