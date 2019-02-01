#include "rqt_plot_qtcharts/randomcolorgenerator.h"

#include <qmath.h>
RandomColorGenerator* RandomColorGenerator::m_instance = nullptr;

QColor RandomColorGenerator::get()
{
    if (m_colorList.isEmpty()) {
        double h = 0;
        double tmp;
        double golden_ratio = 0.618033988749895;
        float currentHue = 0.0;
        for (int i = 0; i < 20; i++) {
            m_colorList.push_back( QColor::fromHslF(currentHue, 1.0, 0.5) );
            currentHue += 0.618033988749895f;
            currentHue = modf(currentHue, &tmp);
        }
        m_index = 0;
        return m_colorList.first();
    }
    m_index++;
    return m_colorList.at(m_index);
}

RandomColorGenerator *RandomColorGenerator::getInstance()
{
    if (!m_instance)
        m_instance = new RandomColorGenerator();
    return m_instance;
}
