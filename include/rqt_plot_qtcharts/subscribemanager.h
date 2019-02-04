#ifndef SUBSCRIBEMANAGER_H
#define SUBSCRIBEMANAGER_H

#include <QObject>

class SubscribeManager : public QObject
{
    Q_OBJECT
public:
    explicit SubscribeManager(QObject *parent = nullptr);

signals:

public slots:

private:
};

#endif // SUBSCRIBEMANAGER_H
