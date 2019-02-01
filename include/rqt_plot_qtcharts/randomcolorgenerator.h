#ifndef RANDOMCOLORGENERATOR_H
#define RANDOMCOLORGENERATOR_H

#include <QColor>
#include <QVector>

class RandomColorGenerator
{
public:
    QColor get();
    static RandomColorGenerator *getInstance();
private:
    QVector<QColor> m_colorList;
    int m_index = 0;
    static RandomColorGenerator* m_instance;
};

#endif // RANDOMCOLORGENERATOR_H
