#include "verticalaxesmanager.h"

VerticalAxesManager *VerticalAxesManager::m_instance = nullptr;

VerticalAxesManager *VerticalAxesManager::instance()
{
    if (!m_instance)
        m_instance = new VerticalAxesManager();
    return m_instance;
}

void VerticalAxesManager::addAxis(VerticalAxis *axis)
{
    m_axes.append(axis);
    emit axisAdded(axis);
}

void VerticalAxesManager::removeAxis(VerticalAxis *axis)
{
    if (m_axes.contains(axis)) {
        m_axes.removeAll(axis);
        emit axisRemoved(axis);
    }
}
