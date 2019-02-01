#include "rqt_plot_qtcharts/plotverticalaxis.h"

PlotVerticalAxis::PlotVerticalAxis(QObject *parent) :
    QValueAxis(parent)
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 12, 0))
    // enable this lovely feature if we have
    this->setLabelsEditable(true);
#endif
}

QString PlotVerticalAxis::label() const
{
    return m_label;
}

void PlotVerticalAxis::setLabel(const QString &label)
{
    m_label = label;
}

QString PlotVerticalAxis::name() const
{
    return m_name;
}

void PlotVerticalAxis::setName(const QString &name)
{
    m_name = name;
}

bool PlotVerticalAxis::autoScale() const
{
    return m_autoScale;
}

void PlotVerticalAxis::setAutoScale(bool value)
{
    m_autoScale = value;
}

Qt::Alignment PlotVerticalAxis::align() const
{
    return m_align;
}

void PlotVerticalAxis::setAlign(const Qt::Alignment &align)
{
    if (m_align != align) {
        m_align = align;
        emit alignChanged(align);
    }
}
