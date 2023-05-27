#include "customqwtmagnifier.h"
#include "customqwtplot.h"
#include <qcoreevent.h>
#include <qevent.h>

CustomQwtPlotMagnifier::CustomQwtPlotMagnifier(QWidget *canvas) : QwtPlotMagnifier(canvas)
{
    setMouseButton(Qt::NoButton);
    setAxisEnabled(QwtPlot::yLeft, false);
    setWheelFactor(1 / wheelFactor());
}
