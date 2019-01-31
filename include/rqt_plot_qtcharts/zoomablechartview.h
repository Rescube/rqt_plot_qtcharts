#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QtCharts/QChartView>
#include <QtWidgets/QRubberBand>

QT_CHARTS_USE_NAMESPACE

//![1]
class ZoomableChartView : public QChartView
//![1]
{
public:
    ZoomableChartView(QChart *chart, QWidget *parent = 0);

    void zoomX(qreal factor, qreal xcenter);
    void zoomX(qreal factor);

//![2]
protected:
    bool viewportEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);
//![2]


private:

    bool m_isTouching;
    QPointF m_lastMousePos;
};

#endif
