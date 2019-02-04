#include "verticalaxis.h"

VerticalAxis::VerticalAxis(QObject *parent) :
    QValueAxis(parent)
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 12, 0))
    // enable this lovely feature if we have
    this->setLabelsEditable(true);
#endif
}

QString VerticalAxis::label() const
{
    return m_label;
}

void VerticalAxis::setLabel(const QString &label)
{
    m_label = label;
}

QString VerticalAxis::name() const
{
    return m_name;
}

void VerticalAxis::setName(const QString &name)
{
    m_name = name;
}

bool VerticalAxis::autoScale() const
{
    return m_autoScale;
}

void VerticalAxis::setAutoScale(bool value)
{
    m_autoScale = value;
}

Qt::Alignment VerticalAxis::align() const
{
    return m_align;
}

void VerticalAxis::setAlign(const Qt::Alignment &align)
{
    if (m_align != align) {
        m_align = align;
        emit alignChanged(align);
    }
}

QString VerticalAxis::getUid() const
{
    return m_uid;
}

void VerticalAxis::setUid(const QString &value)
{
    m_uid = value;
}

void VerticalAxis::resetRange()
{
    setRange(m_rangeMin, m_rangeMax);
}

qreal VerticalAxis::rangeMin() const
{
    return m_rangeMin;
}

void VerticalAxis::setRangeMin(const qreal &rangeMin)
{
    m_rangeMin = rangeMin;
}

qreal VerticalAxis::rangeMax() const
{
    return m_rangeMax;
}

void VerticalAxis::setRangeMax(const qreal &rangeMax)
{
    m_rangeMax = rangeMax;
}
