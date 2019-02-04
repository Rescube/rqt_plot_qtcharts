#ifndef VERTICALAXESMANAGER_H
#define VERTICALAXESMANAGER_H

#include "verticalaxis.h"

#include <QObject>

class VerticalAxesManager : public QObject
{
    Q_OBJECT
public:
    static VerticalAxesManager *instance();

    QList<VerticalAxis*> axes() const {return m_axes;}
    void addAxis(VerticalAxis *axis);
    void removeAxis(VerticalAxis *axis);

signals:
    void axisAdded(VerticalAxis *axis);
    void axisRemoved(VerticalAxis *axis);

private:
    static VerticalAxesManager *m_instance;
    QList <VerticalAxis*> m_axes;
};

#endif // VERTICALAXESMANAGER_H
