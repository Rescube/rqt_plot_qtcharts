#include "seriesmanager.h"

SeriesManager *SeriesManager::m_instance = nullptr;

SeriesManager::SeriesManager()
{

}

SeriesManager::~SeriesManager()
{
    if (m_instance) {
        delete m_instance;
        m_instance = nullptr;
    }
}

SeriesManager *SeriesManager::instance()
{
    if (!m_instance)
        m_instance = new SeriesManager();
    return m_instance;
}

void SeriesManager::clear()
{
    for (PlotLineSeries *series : m_series) {
        series->clear();
    }
}

void SeriesManager::addSeries(PlotLineSeries *series)
{
    m_series.append(series);
    emit seriesAdded(series);
}

void SeriesManager::removeSeries(PlotLineSeries *series)
{
    m_series.removeAll(series);
    emit seriesRemoved(series);
}

QList<PlotLineSeries *> SeriesManager::seriesList() const
{
    return m_series;
}
