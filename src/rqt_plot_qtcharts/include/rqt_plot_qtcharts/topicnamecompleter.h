#ifndef TOPICNAMECOMPLETER_H
#define TOPICNAMECOMPLETER_H

#include <ros/master.h>

#include <QAbstractListModel>

class TopicNameCompleterModel : public QAbstractListModel
{
public:
    TopicNameCompleterModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
};

#endif // TOPICNAMECOMPLETER_H
