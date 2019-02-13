#ifndef PLOTVERTICALAXIS_H
#define PLOTVERTICALAXIS_H

#include <QtCharts/QValueAxis>

QT_CHARTS_BEGIN_NAMESPACE
class QValueAxis;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class VerticalAxis : public QValueAxis
{
    Q_OBJECT
public:
    VerticalAxis(QObject *parent = nullptr);

    QString label() const;
    void setLabel(const QString &label);

    QString name() const;
    void setName(const QString &name);

    bool autoScale() const;
    void setAutoScale(bool value);

    Qt::Alignment align() const;
    void setAlign(const Qt::Alignment &align);

    QString getUid() const;
    void setUid(const QString &value);

    void resetRange();

    qreal rangeMin() const;
    void setRangeMin(const qreal &rangeMin);

    qreal rangeMax() const;
    void setRangeMax(const qreal &rangeMax);

    void seriesPointAdded(const qreal y);

    bool getInstantApplyAutoScale() const;
    void setInstantApplyAutoScale(bool instantApplyAutoScale);

    void applyAutoScale();

private:
    QString m_name, m_label;
    bool m_autoScale = false;
    bool m_instantApplyAutoScale = true;
    Qt::Alignment m_align;
    QString m_uid;

    qreal m_rangeMin = 0, m_rangeMax = 100.0;
    qreal m_seriesMin, m_seriesMax;
signals:
    void alignChanged(Qt::Alignment align);
};

#endif // PLOTVERTICALAXIS_H
