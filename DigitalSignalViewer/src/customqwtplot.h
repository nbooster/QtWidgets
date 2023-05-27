#pragma once

#include "digitalsignal.h"
#include "legendlabel.h"

#include <qwt_plot.h>
#include <qwt_plot_curve.h>

static ushort selectedCurvePenSize = 6;
static ushort unselectedCurvePenSize = 4;
static ushort xAxisRebaseStep = 2000;

class CustomQwtPlot;
class DigitalSignalViewerWidget;

class CustomQwtPlot : public QwtPlot
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(CustomQwtPlot)

public:
    explicit CustomQwtPlot(const QwtText &title, const DigitalSignal &signal,
                           QList<double> *plotsTicks, QList<double> *allTicks,
                           QWidget *parent = nullptr);
    ~CustomQwtPlot() = default;
    void setMinMax(double min, double max);
    void setPrevBounds(double plb, double pub);
    void setLastX(double x);
    void setLegend(LegendLabel *);
    LegendLabel *legend();

signals:
    void updateMinMax(double min, double max);
    void updatePrevBounds(double plb, double pub);
    void updateAxisDiv(QwtScaleDiv);
    void updateLastX(double);
    void clickCurve(QwtPlotCurve *);

protected:
    void mouseMoveEvent(QMouseEvent *const);
    void mousePressEvent(QMouseEvent *const);
    void mouseReleaseEvent(QMouseEvent *const);
    void wheelEvent(QWheelEvent *const);

private:
    double _minX;
    double _maxX;
    double _prevUpperBound;
    double _prevLowerBound;
    int _lastX;
    LegendLabel *_legend = nullptr;
    QList<double> *_plotsTicks = nullptr;
    QList<double> *_allTicks = nullptr;
};
