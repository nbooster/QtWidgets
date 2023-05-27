#include "customqwtplot.h"
#include "customqwtmagnifier.h"
#include "customqwtplotpanner.h"
#include "digitalsignalviewerwidget.h"

#include <qevent.h>
#include <qwt_legend.h>
#include <qwt_legend_label.h>
#include <qwt_plot_grid.h>

CustomQwtPlot::CustomQwtPlot(const QwtText &title, const DigitalSignal &signal,
                             QList<double> *plotsTicks, QList<double> *allTicks, QWidget *parent)
    : QwtPlot(title, parent)
{
    if (!signal.data.size())
        return;

    setTitle("");
    enableAxis(QwtPlot::xBottom, false);
    enableAxis(QwtPlot::yLeft, false);
    setCanvasBackground(QColor(50, 50, 50));
    setAutoReplot();

    (void)new CustomQwtPlotPanner(canvas());

    (void)new CustomQwtPlotMagnifier(canvas());

    canvas()->installEventFilter(this);

    auto curve = new QwtPlotCurve(title);
    curve->setStyle(QwtPlotCurve::Steps);
    curve->setCurveAttribute(QwtPlotCurve::Inverted);
    curve->setRenderHint(QwtPlotItem::RenderAntialiased, true);
    curve->setPen(QColor(static_cast<DigitalSignalViewerWidget *>(parent)->nextColor()),
                  unselectedCurvePenSize);

    _plotsTicks = plotsTicks;
    _allTicks = allTicks;

    QPolygonF points;
    auto prev = signal.data[0].second;
    _plotsTicks->append(signal.data[0].first);
    for (const auto &[x, y] : signal.data)
    {
        points << QPointF(x, y);

        if (y != prev)
        {
            _plotsTicks->append(x);
            prev = y;
        }
    }
    _plotsTicks->append(signal.data.back().first);
    curve->setSamples(points);
    curve->attach(this);

    const auto [min, max] = std::minmax_element(_plotsTicks->begin(), _plotsTicks->end());

    _minX = *min;
    _maxX = *max;
    _prevLowerBound = _minX;
    _prevUpperBound = _maxX;

    setAxisScale(QwtPlot::xBottom, _minX, _maxX);

    QList<double> rebaseXTicks;
    double rebaseStep = xAxisRebaseStep;
    auto base = _minX + rebaseStep;
    while (base < _maxX)
    {
        rebaseXTicks.append(base);
        base += rebaseStep;
    }

    _allTicks->clear();
    *_allTicks += *_plotsTicks + rebaseXTicks;

    auto xaxisdiv = axisScaleDiv(QwtPlot::xBottom);
    xaxisdiv.setTicks(QwtScaleDiv::MajorTick, *_allTicks);
    xaxisdiv.setTicks(QwtScaleDiv::MediumTick, {});
    xaxisdiv.setTicks(QwtScaleDiv::MinorTick, {});
    setAxisScaleDiv(QwtPlot::xBottom, xaxisdiv);
}

void CustomQwtPlot::setLastX(double x) { _lastX = x; }

void CustomQwtPlot::setPrevBounds(double plb, double pub)
{
    _prevLowerBound = plb;
    _prevUpperBound = pub;
}

void CustomQwtPlot::setMinMax(double min, double max)
{
    _minX = min;
    _maxX = max;
}

void CustomQwtPlot::setLegend(LegendLabel *legend) { _legend = legend; }

LegendLabel *CustomQwtPlot::legend() { return _legend; }

void CustomQwtPlot::mousePressEvent(QMouseEvent *const event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit updateLastX(event->x());
        canvas()->setCursor(Qt::ClosedHandCursor);
        auto curve = static_cast<QwtPlotCurve *>(itemList()[0]);
        if (curve->pen().width() == unselectedCurvePenSize)
            curve->setPen(curve->pen().color(), selectedCurvePenSize);
        else
            curve->setPen(curve->pen().color(), unselectedCurvePenSize);
        emit clickCurve(curve);
    }
}

void CustomQwtPlot::mouseReleaseEvent(QMouseEvent *const event)
{
    if (event->button() == Qt::LeftButton)
        canvas()->setCursor(Qt::CrossCursor);
}

void CustomQwtPlot::mouseMoveEvent(QMouseEvent *const event)
{
    emit updateLastX(event->x());
    auto xaxisdiv = axisScaleDiv(QwtPlot::xBottom);
    xaxisdiv.setTicks(QwtScaleDiv::MajorTick, *_allTicks);
    xaxisdiv.setTicks(QwtScaleDiv::MediumTick, {});
    xaxisdiv.setTicks(QwtScaleDiv::MinorTick, {});
    const auto deltaXUpper = axisScaleDiv(QwtPlot::xBottom).upperBound() - _prevUpperBound;
    const auto deltaXLower = axisScaleDiv(QwtPlot::xBottom).lowerBound() - _prevLowerBound;
    if (axisScaleDiv(QwtPlot::xBottom).lowerBound() <= _minX)
    {
        xaxisdiv.setLowerBound(_minX);
        xaxisdiv.setUpperBound(axisScaleDiv(QwtPlot::xBottom).upperBound() - deltaXUpper);
    }
    else if (axisScaleDiv(QwtPlot::xBottom).upperBound() >= _maxX)
    {
        xaxisdiv.setLowerBound(axisScaleDiv(QwtPlot::xBottom).lowerBound() - deltaXLower);
        xaxisdiv.setUpperBound(_maxX);
    }

    _prevUpperBound = xaxisdiv.upperBound();
    _prevLowerBound = xaxisdiv.lowerBound();
    emit updatePrevBounds(_prevLowerBound, _prevUpperBound);
    emit updateAxisDiv(xaxisdiv);
}

void CustomQwtPlot::wheelEvent(QWheelEvent *const event)
{
    auto scaleDivX = axisScaleDiv(QwtPlot::xBottom);
    auto xaxisdiv = axisScaleDiv(QwtPlot::xBottom);
    xaxisdiv.setTicks(QwtScaleDiv::MajorTick, *_allTicks);
    xaxisdiv.setTicks(QwtScaleDiv::MediumTick, {});
    xaxisdiv.setTicks(QwtScaleDiv::MinorTick, {});
    if (event->angleDelta().y() > 0) // Zoom In
    {
        if (_prevLowerBound <= _minX && scaleDivX.lowerBound() > _minX)
        {
            _prevLowerBound = _minX;
            _prevUpperBound = scaleDivX.upperBound();
            xaxisdiv.setLowerBound(_minX);
            xaxisdiv.setUpperBound(scaleDivX.upperBound());
        }
        else if (_prevUpperBound >= _maxX && scaleDivX.upperBound() < _maxX)
        {
            _prevUpperBound = _maxX;
            _prevLowerBound = scaleDivX.lowerBound();
            xaxisdiv.setLowerBound(scaleDivX.lowerBound());
            xaxisdiv.setUpperBound(_maxX);
        }
    }
    else
    {
        _prevUpperBound = scaleDivX.upperBound();
        _prevLowerBound = scaleDivX.lowerBound();
        bool lowCond = _prevLowerBound <= _minX;
        bool upperCond = _prevUpperBound >= _maxX;
        if (lowCond && upperCond)
        {
            xaxisdiv.setLowerBound(_minX);
            xaxisdiv.setUpperBound(_maxX);
        }
        else if (lowCond)
        {
            xaxisdiv.setLowerBound(_minX);
            xaxisdiv.setUpperBound(_prevUpperBound);
        }
        else if (upperCond)
        {
            xaxisdiv.setLowerBound(_prevLowerBound);
            xaxisdiv.setUpperBound(_maxX);
        }
    }
    emit updatePrevBounds(_prevLowerBound, _prevUpperBound);
    emit updateAxisDiv(xaxisdiv);
}
