#ifndef SERIESMANAGER_H
#define SERIESMANAGER_H

#include "plotlineseries.h"

#include <QObject>

class SeriesManager : public QObject
{
    Q_OBJECT
public:
    SeriesManager();
    ~SeriesManager();
    static SeriesManager *instance();

    void clear();

    void addSeries(PlotLineSeries *series);
    void removeSeries(PlotLineSeries *series);

    QList<PlotLineSeries *> seriesList() const;

signals:
    void seriesAdded(PlotLineSeries *series);
    void seriesRemoved(PlotLineSeries *series);

private:
    static SeriesManager *m_instance;
    QList<PlotLineSeries*> m_series;
};

#endif // SERIESMANAGER_H
