#ifndef DIALOGAXES_H
#define DIALOGAXES_H

#include "verticalaxesmodel.h"

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
    void refreshAxisList();

private slots:
    void on_toolButtonAddAxis_clicked();
    void on_toolButtonRemoveAxis_clicked();
    void on_tableViewAxesList_doubleClicked(const QModelIndex &index);

    void on_tableViewAxesList_customContextMenuRequested(const QPoint &pos);

private:
    Ui::DialogAxes *ui;
    VerticalAxesModel *m_model;
};

#endif // DIALOGAXES_H
