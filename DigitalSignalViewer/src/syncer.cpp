#include "syncer.h"

#include <qwt_scale_widget.h>

Syncer::Syncer(QWidget *parent) : QWidget(parent) {}

void Syncer::addPlot(CustomQwtPlot *plot)
{
    _plots.push_back(plot);
    connect(plot, &CustomQwtPlot::updateAxisDiv, this, &Syncer::updatedAxisDiv);
    connect(plot, &CustomQwtPlot::updateLastX, this, &Syncer::updatedLastX);
    connect(plot, &CustomQwtPlot::updatePrevBounds, this, &Syncer::updatedPrevBounds);
    connect(plot, &CustomQwtPlot::updateMinMax, this, &Syncer::updatedMinMax);
}

void Syncer::updatedMinMax(double min, double max)
{
    for (auto plot : _plots)
    {
        plot->setMinMax(min, max);
    }
}

void Syncer::updatedPrevBounds(double plb, double pub)
{
    for (auto plot : _plots)
    {
        plot->setPrevBounds(plb, pub);
    }
}

void Syncer::updatedLastX(double lastx)
{
    for (auto plot : _plots)
    {
        plot->setLastX(lastx);
    }
}

void Syncer::updatedAxisDiv(QwtScaleDiv div)
{
    for (auto plot : _plots)
    {
        plot->setAxisScaleDiv(QwtPlot::xBottom, div);
    }
}
