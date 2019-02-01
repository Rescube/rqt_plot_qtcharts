#ifndef PLOTVERTICALAXIS_H
#define PLOTVERTICALAXIS_H

#include <QtCharts/QValueAxis>

QT_CHARTS_BEGIN_NAMESPACE
class QValueAxis;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class PlotVerticalAxis : public QValueAxis
{
    Q_OBJECT
public:
    PlotVerticalAxis(QObject *parent = nullptr);

    QString label() const;
    void setLabel(const QString &label);

    QString name() const;
    void setName(const QString &name);

    bool autoScale() const;
    void setAutoScale(bool value);

    Qt::Alignment align() const;
    void setAlign(const Qt::Alignment &align);

private:
    QString m_name, m_label;
    bool m_autoScale = false;
    Qt::Alignment m_align;
signals:
    void alignChanged(Qt::Alignment align);
};

#endif // PLOTVERTICALAXIS_H
