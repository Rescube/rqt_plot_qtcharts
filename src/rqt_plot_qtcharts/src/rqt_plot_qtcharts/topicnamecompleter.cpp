#include "include/rqt_plot_qtcharts/topicnamecompleter.h"

TopicNameCompleterModel::TopicNameCompleterModel(QObject *parent) :
    QAbstractListModel(parent)
{

}

int TopicNameCompleterModel::rowCount(const QModelIndex &parent) const
{
    // TODO
    return 0;
}

QVariant TopicNameCompleterModel::data(const QModelIndex &index, int role) const
{
    return QVariant();
}
